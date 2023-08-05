/*! Main file for Bag, editing master, testing magit **/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "kputils.h"
#include "banned.h"
#include "bag.h"

enum type_e {ITEM, LOCATION, PERSON};

enum object_e {HERO=0, GRUMIO, WOODENBOX, REDBALL, KNIFE, HELPNOTE, ROPE, END_OBJ};

struct object_s {
    int id;
    char noun[12], adjective[12], unique_name[24], description[256];
    struct list_t *bag;
    enum type_e is_a;
    union {
        struct {
            int weight, capacity;
        } item;
        struct {
            int location;
        } location;
        struct {
            bool can_carry;
            char name[12];
        } person;
    };
};

int main(void) {

    struct object_s *objects;
    objects = malloc((END_OBJ+1) * sizeof(struct object_s));
    if (objects == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }

    for (enum object_e counter=HERO; counter<=END_OBJ; counter++) {
        objects[counter].bag = create_list();
    }

    // HERO
    strlcpy(objects[HERO].noun, "me", 12); 
    strlcpy(objects[HERO].adjective, "brave", 12); 
    strlcpy(objects[HERO].unique_name, "hero", 12);
    strlcpy(objects[HERO].description, "A brave young man.", 12); 
    objects[HERO].is_a = PERSON;
    objects[HERO].person.can_carry = true;
    strlcpy(objects[HERO].person.name, "Freddy", 12);

    // HERO
    strlcpy(objects[HERO].noun, "me", 12); 
    strlcpy(objects[HERO].adjective, "brave", 12); 
    strlcpy(objects[HERO].unique_name, "hero", 12);
    strlcpy(objects[HERO].description, "A brave young man.", 12); 
    objects[HERO].is_a = PERSON;
    objects[HERO].person.can_carry = true;
    strlcpy(objects[HERO].person.name, "Freddy", 12);

    // GRUMIO
    strlcpy(objects[GRUMIO].noun, "grumio", 12); 
    strlcpy(objects[GRUMIO].adjective, "grumpy", 12); 
    strlcpy(objects[GRUMIO].unique_name, "grumio", 12);
    strlcpy(objects[GRUMIO].description, "A grumpy slave.", 12); 
    objects[GRUMIO].is_a = PERSON;
    objects[GRUMIO].person.can_carry = true;
    strlcpy(objects[GRUMIO].person.name, "Grumio", 12);

    // WOODENBOX
    strlcpy(objects[WOODENBOX].noun, "box", 12); 
    strlcpy(objects[WOODENBOX].adjective, "wooden", 12); 
    strlcpy(objects[WOODENBOX].unique_name, "woodenbox", 12);
    strlcpy(objects[WOODENBOX].description, "I can put something in here.", 256); 
    objects[WOODENBOX].is_a = ITEM;
    objects[WOODENBOX].item.weight = 5;
    objects[WOODENBOX].item.capacity = 25;

    // REDBALL
    strlcpy(objects[REDBALL].noun, "ball", 12); 
    strlcpy(objects[REDBALL].adjective, "red", 12); 
    strlcpy(objects[REDBALL].unique_name, "redball", 12);
    strlcpy(objects[REDBALL].description, "Its bouncy.", 256); 
    objects[REDBALL].is_a = ITEM;
    objects[REDBALL].item.weight = 2;
    objects[REDBALL].item.capacity = 0;

    // KNIFE
    strlcpy(objects[KNIFE].noun, "knife", 12); 
    strlcpy(objects[KNIFE].adjective, "sharp", 12); 
    strlcpy(objects[KNIFE].unique_name, "knife", 12);
    strlcpy(objects[KNIFE].description, "A sharp knife.", 256); 
    objects[KNIFE].is_a = ITEM;
    objects[KNIFE].item.weight = 2;
    objects[KNIFE].item.capacity = 0;

    // HELPNOTE
    strlcpy(objects[HELPNOTE].noun, "note", 12); 
    strlcpy(objects[HELPNOTE].adjective, "help", 12); 
    strlcpy(objects[HELPNOTE].unique_name, "helpnote", 12);
    strlcpy(objects[HELPNOTE].description, "Q is quit.", 256); 
    objects[HELPNOTE].is_a = ITEM;
    objects[HELPNOTE].item.weight = 1;
    objects[HELPNOTE].item.capacity = 0;

    // ROPE
    strlcpy(objects[ROPE].noun, "rope", 12); 
    strlcpy(objects[ROPE].adjective, "long", 12); 
    strlcpy(objects[ROPE].unique_name, "rope", 12);
    strlcpy(objects[ROPE].description, "Useful for climbing.", 256); 
    objects[ROPE].is_a = ITEM;
    objects[ROPE].item.weight = 4;
    objects[ROPE].item.capacity = 0;

    push_head(objects[HERO].bag, (void*)&objects[ROPE]);
    push_head(objects[HERO].bag, (void*)&objects[HELPNOTE]);

    struct node_t *iter = objects[HERO].bag->head;
    printf("You have the following items: ");
    while (iter != NULL) {
        printf("%s, ", (char*)((struct object_s*)(iter->data))->noun);
        iter = iter->next;
        
    }
    
    for (enum object_e counter=HERO; counter<=END_OBJ; counter++) {
        delete_list(objects[counter].bag);
    }   
    if (objects != NULL) {
        free(objects);
        objects = NULL;
    }
}
