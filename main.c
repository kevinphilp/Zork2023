/*! Main file for Bag, editing master, testing magit **/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "kputils.h"
#include "banned.h"

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
<<<<<<< Updated upstream

    // HERO
    strlcpy(objects[HERO].noun, "me", 12); 
    strlcpy(objects[HERO].adjective, "brave", 12); 
    strlcpy(objects[HERO].unique_name, "hero", 12);
    strlcpy(objects[HERO].description, "A brave young man.", 12); 
    objects[HERO].is_a = PERSON;
    objects[HERO].person.can_carry = true;
    strlcpy(objects[HERO].person.name, "Freddy", 12);

=======

    // HERO
    strlcpy(objects[HERO].noun, "me", 12); 
    strlcpy(objects[HERO].adjective, "brave", 12); 
    strlcpy(objects[HERO].unique_name, "hero", 12);
    strlcpy(objects[HERO].description, "A brave young man.", 12); 
    objects[HERO].is_a = PERSON;
    objects[HERO].person.can_carry = true;
    strlcpy(objects[HERO].person.name, "Freddy", 12);

>>>>>>> Stashed changes
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
        printf("%s, ", (struct object_s*)(iter)->data->noun);
        
    }
    


    for (enum object_e counter=HERO; counter<=END_OBJ; counter++) {
        delete_list(objects[counter].bag);
    }   
    if (objects != NULL) {
        free(objects);
        objects = NULL;
    }
    new_list->size = 0;
    new_list->head = NULL;
    new_list->tail = NULL;
    return new_list;
}

void push_head(struct list_t* list, void* data) {
    struct node_t *new_node = malloc(sizeof(struct node_t));
    if (!new_node) {
        printf("Problem allocating node.");
        exit(0);
    }
    new_node->id = node_id++;
    new_node->data = data;
    if (list->head == NULL) {  // List is empty
        list->head = new_node;
        list->tail = new_node;
    } else {
        new_node->next = list->head;
        new_node->prev = NULL;
        list->head->prev = new_node;
        list->head = new_node;
    }
    list->size++;
}

void push_tail(struct list_t* list, void* data) {
    struct node_t *new_node = malloc(sizeof(struct node_t));
    if (!new_node) {
        printf("Problem allocating node.");  //Change to perror
        exit(0);
    }
    new_node->id = node_id++;
    new_node->data = data;
    if (list->head == NULL) {   // List is empty
        list->head = new_node;
        list->tail = new_node;
    } else {
        new_node->prev = list->tail;
        new_node->next = NULL;
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->size++;
}

void* pop_head(struct list_t *list) {
    struct node_t *new_head = NULL;
    void *ret_data;
    if (list->head == NULL) {  // Empty list, return NULL
        return(NULL);
    }
    ret_data = list->head->data;
    if (list->size == 1) {  // One element list
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
    } else {
        new_head = list->head->next;
        free(new_head->prev);
        new_head->prev = NULL;
        list->head = new_head;
    }
    list->size--;
    return(ret_data);
}

void* pop_tail(struct list_t *list) {
    struct node_t *new_tail = NULL;
    void *ret_data;
    if (list->tail == NULL) {  // Empty list, return NULL
        return(NULL);
    }
    ret_data = list->tail->data;
    if (list->size == 1) {  // One element list
        free(list->tail);
        list->head = NULL;
        list->tail = NULL;
    } else {
        new_tail = list->tail->prev;
        free(new_tail->next);
        new_tail->next = NULL;
        list->tail = new_tail;
    }
    list->size--;
    return(ret_data);
}

void* remove_by_id(struct list_t *list, int id) {
    if (list->size == 0) {  // Empty list
        return(NULL);
    } else {
        struct node_t *current_node = list->head;
        while (current_node != NULL) {
            if (current_node->id == id) {  // List one node only
                if (list->size == 1) {
                    list->head = NULL;
                    list->tail = NULL;
                } else {
                    if (current_node->prev == NULL) {  // Nothing previous
                        list->head = current_node->next;
                        current_node->next->prev = NULL;
                    } else {
                        current_node->prev->next = current_node->next;
                    }
                    if (current_node->next == NULL) {  // Nothing next
                        list->tail = current_node->prev;
                        current_node->prev->next = NULL;
                    } else {
                        current_node->next->prev = current_node->prev;
                    }
                }
                void* ret_data = current_node->data;
                free(current_node);
                current_node = NULL;
                list->size--;
                return(ret_data);
            }
            current_node = current_node->next;
        }
        return(NULL);
    }
}

void* get_by_id(struct list_t *list, int id) {
    if (list->size == 0) {  // Empty list
        return(NULL);
    } else {
        struct node_t *current_node = list->head;
        while (current_node != NULL) {
            if (current_node->id == id) {
                return(current_node->data);
            }
        }
        return(NULL);
    }
}

void delete_list(struct list_t *list) {
    if (list) {
        struct node_t *current_node = list->head;
        while (current_node != NULL) {
            struct node_t *next_node = current_node->next;
            free(current_node);
            current_node = next_node;
        }
        free(list);
    }
}

void empty_list(struct list_t *list) {
    if (list) {
        struct node_t *current_node = list->head;
        while (current_node != NULL) {
            struct node_t *next_node = current_node->next;
            free(current_node);
            current_node = next_node;
        }
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
    }
}
