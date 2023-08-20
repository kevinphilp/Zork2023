/*!  Main file for Bag, editing master, testing magit **/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "kputils.h"
#include "banned.h"
#include "bag.h"

enum type_e {ITEM, LOCATION, PERSON};

enum object_e {HERO = 0, GRUMIO, KITCHEN,
    WOODENBOX, REDBALL, KNIFE, HELPNOTE,
    ROPE, END_OBJ};

struct object_s {
    enum object_e object_id;
    char noun[12], adjective[12], unique_name[24], description[256];
    struct list_t *bag;
    enum type_e is_a;
    union {
        struct {
            int weight, capacity;
        } item;
        struct {
            bool lit;
        } location;
        struct {
            bool can_carry;
            char name[12];
            enum object_e location;
        } person;
    };
};

// enum type_e {ITEM, LOCATION, PERSON};
void dump_objects(
    struct object_s* in_objects,
    enum object_e start,
    enum object_e end) {
    puts("People:");
    for (enum object_e counter=start; counter < end; counter++) {
        if (in_objects[counter].is_a == PERSON) {
            printf("id: %d, %s is a %d",
                   in_objects[counter].object_id,
                   in_objects[counter].unique_name,
                   in_objects[counter].is_a);
            puts("");
        }
    }
    puts("Locations:");
    for (enum object_e counter=start; counter < end; counter++) {
        if (in_objects[counter].is_a == LOCATION) {
            printf("id: %d, %s is a %d\n",
                   in_objects[counter].object_id,
                   in_objects[counter].unique_name,
                   in_objects[counter].is_a);
            printf("Is lit: %s",
                   in_objects[counter].location.lit ?
                   "True" : "False");
            puts("");
        }
    }
    puts("Items:");
    for (enum object_e counter=start; counter < end; counter++) {
        if (in_objects[counter].is_a == ITEM) {
            printf("id: %d, %s is a %d\n",
                   in_objects[counter].object_id,
                   in_objects[counter].unique_name,
                   in_objects[counter].is_a);
            printf("Weighs: %d, Capacity: %d\n",
                   in_objects[counter].item.weight,
                   in_objects[counter].item.capacity);
            puts("");
        }
    }
    }

void transfer_object(
    struct list_t* remove_list,
    struct list_t* push_list,
    int node_id,
    struct object_s* object) {
    push_head(push_list, object);
    remove_by_id(remove_list, node_id);
}

int compare_unique_name(void *item1, void *item2) {  
    return( strcicmp(
                ((struct object_s*)item2)->unique_name,
                ((struct object_s*)item1)->unique_name
                ));
}

int main(void) {

    struct object_s *objects;
    objects = malloc((END_OBJ+1) * sizeof(struct object_s));
    if (objects == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }
    for (enum object_e counter=HERO; counter <= END_OBJ; counter++) {
        objects[counter].bag = create_list();
    }
    
    // HERO 0
    objects[HERO].object_id = HERO;
    strlcpy(objects[HERO].noun, "me", 12);
    strlcpy(objects[HERO].adjective, "brave", 12);
    strlcpy(objects[HERO].unique_name, "hero", 12);
    strlcpy(objects[HERO].description, "A brave young man.", 12);
    objects[HERO].is_a = PERSON;
    objects[HERO].person.location = KITCHEN;
    objects[HERO].person.can_carry = true;
    strlcpy(objects[HERO].person.name, "Freddy", 12);
    // GRUMIO 1
    objects[GRUMIO].object_id = GRUMIO;
    strlcpy(objects[GRUMIO].noun, "grumio", 12);
    strlcpy(objects[GRUMIO].adjective, "grumpy", 12);
    strlcpy(objects[GRUMIO].unique_name, "grumio", 12);
    strlcpy(objects[GRUMIO].description, "A grumpy slave.", 12);
    objects[GRUMIO].is_a = PERSON;
    objects[HERO].person.location = KITCHEN;
    objects[GRUMIO].person.can_carry = true;
    strlcpy(objects[GRUMIO].person.name, "Grumio", 12);
    // KITCHEN 2
    objects[KITCHEN].object_id = KITCHEN;
    strlcpy(objects[KITCHEN].noun, "kitchen", 12);
    strlcpy(objects[KITCHEN].adjective, "damp", 12);
    strlcpy(objects[KITCHEN].unique_name, "dampkitchen", 12);
    strlcpy(objects[KITCHEN].description, "A damp kitchen.", 12);
    objects[KITCHEN].is_a = LOCATION;
    objects[KITCHEN].location.lit = false;
    // WOODENBOX 3
    objects[WOODENBOX].object_id = WOODENBOX;
    strlcpy(objects[WOODENBOX].noun, "box", 12);
    strlcpy(objects[WOODENBOX].adjective, "wooden", 12);
    strlcpy(objects[WOODENBOX].unique_name, "woodenbox", 12);
    strlcpy(objects[WOODENBOX].description,
            "I can put something in here.", 256);
    objects[WOODENBOX].is_a = ITEM;
    objects[WOODENBOX].item.weight = 5;
    objects[WOODENBOX].item.capacity = 25;
    // REDBALL 4
    objects[REDBALL].object_id = REDBALL;
    strlcpy(objects[REDBALL].noun, "ball", 12);
    strlcpy(objects[REDBALL].adjective, "red", 12);
    strlcpy(objects[REDBALL].unique_name, "redball", 12);
    strlcpy(objects[REDBALL].description, "Its bouncy.", 256);
    objects[REDBALL].is_a = ITEM;
    objects[REDBALL].item.weight = 2;
    objects[REDBALL].item.capacity = 0;
    // KNIFE 5
    objects[KNIFE].object_id = KNIFE;
    strlcpy(objects[KNIFE].noun, "knife", 12);
    strlcpy(objects[KNIFE].adjective, "sharp", 12);
    strlcpy(objects[KNIFE].unique_name, "knife", 12);
    strlcpy(objects[KNIFE].description, "A sharp knife.", 256);
    objects[KNIFE].is_a = ITEM;
    objects[KNIFE].item.weight = 2;
    objects[KNIFE].item.capacity = 0;
    // HELPNOTE 6
    objects[HELPNOTE].object_id = HELPNOTE;
    strlcpy(objects[HELPNOTE].noun, "note", 12);
    strlcpy(objects[HELPNOTE].adjective, "help", 12);
    strlcpy(objects[HELPNOTE].unique_name, "helpnote", 12);
    strlcpy(objects[HELPNOTE].description, "Q is quit.", 256);
    objects[HELPNOTE].is_a = ITEM;
    objects[HELPNOTE].item.weight = 1;
    objects[HELPNOTE].item.capacity = 0;
    // ROPE 7
    objects[ROPE].object_id = ROPE;
    strlcpy(objects[ROPE].noun, "rope", 12);
    strlcpy(objects[ROPE].adjective, "long", 12);
    strlcpy(objects[ROPE].unique_name, "rope", 12);
    strlcpy(objects[ROPE].description, "Useful for climbing.", 256);
    objects[ROPE].is_a = ITEM;
    objects[ROPE].item.weight = 4;
    objects[ROPE].item.capacity = 0;
    push_head(objects[HERO].bag, (void*)&objects[ROPE]);
    push_head(objects[HERO].bag, (void*)&objects[HELPNOTE]);

    // dump_objects(objects, HERO, END_OBJ);


    struct object_s *found_node = find_element( (void*)&objects[ROPE], objects[HERO].bag, compare_unique_name );

    if (found_node != NULL) {
        printf("\n - Found on Hero - %s \n", found_node->unique_name);
    } else {
        printf("\n - Not found on Hero - \n");
    }

    struct node_t *iter = objects[HERO].bag->head;
    printf("You have the following items: ");
    while (iter != NULL) {
        printf(" %s,", (char*)((struct object_s*)(iter->data))->unique_name);
        iter = iter->next;
    }
    puts("");
    iter = objects[HERO].bag->head;
    printf("Pass rope to Grumio:\n");
    while (iter != NULL) {
        if ( strcicmp(
                 (char*)((struct object_s*)(iter->data))->unique_name,
                 "rope") == 0 ) {
            int obj_id = (int)((struct object_s*)(iter->data))->object_id;
            printf("\n - Object %d, Node %d - ", obj_id, iter->node_id);
            transfer_object(
                objects[HERO].bag,
                objects[GRUMIO].bag,
                iter->node_id,
                (struct object_s*)(iter->data));
            break;
        } else {
            iter = iter->next;
        }
    }
    iter = objects[HERO].bag->head;
    printf("You have the following items:\n");
    while (iter != NULL) {
        printf(" %s,", (char*)((struct object_s*)(iter->data))->unique_name);
        iter = iter->next;
    }
    puts("");
    iter = objects[GRUMIO].bag->head;
    printf("Grumio has the following items:\n");
    while (iter != NULL) {
        printf(" %s,", (char*)((struct object_s*)(iter->data))->unique_name);
        iter = iter->next;
    }
    puts("");
    for (enum object_e counter=HERO;
         counter <= END_OBJ; counter++) {
        delete_list(objects[counter].bag);
    }
    if (objects != NULL) {
        free(objects);
        objects = NULL;
    }
}
