/*! Main file for Bag, editing master, testing magit **/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "kputils.h"
#include "banned.h"
#include "bag.h"

struct person_t {
    int id;
    char name[12]; 
    struct list_t *bag;
};

struct object_t {
    int id;
    char name[12]; 
    struct list_t *bag;
};

int main() {

    struct object_t *objects;
    objects = malloc(3 * sizeof(struct object_t));

    if (objects == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }

    objects[0].bag = create_list();
    objects[1].bag = create_list();
    objects[2].bag = create_list();

    strlcpy( objects[0].name, "C Programming", 12);
    
        
    char x[12] = "aaa";
    char y[12] ="bbb";
    char z[12] = "cccc";
    push_tail(objects[1].bag, (void*)&z);
    push_tail(objects[1].bag, (void*)&y);
    push_head(objects[1].bag, (void*)&x);
    push_tail(objects[1].bag, (void*)&z);
    push_tail(objects[1].bag, (void*)&y);
    push_head(objects[1].bag, (void*)&x);
    push_head(objects[1].bag, (void*)"asdf");
    printf("Initial size -- %d\n", objects[1].bag->size);
    printf("Remove by id 0 - %s\n", (char*)remove_by_id(objects[1].bag, 0));
    printf("Remove by id 5 - %s\n", (char*)remove_by_id(objects[1].bag, 5));
    printf("Remove by id 2 - %s\n", (char*)remove_by_id(objects[1].bag, 2));
    struct node_t *int_ptr = objects[1].bag->head;
    while (int_ptr != NULL) {
        printf("%d - %s\n", int_ptr->id, (char*)int_ptr->data);
        int_ptr = int_ptr->next;
    }
    int_ptr = objects[1].bag->tail;
    while (int_ptr != NULL) {
        printf("%d - %s\n", int_ptr->id, (char*)int_ptr->data);
        int_ptr = int_ptr->prev;
    }

    printf("Final size -- %d\n", objects[1].bag->size);
    delete_list(objects[0].bag);
    delete_list(objects[1].bag);
    delete_list(objects[2].bag);

    if (objects != NULL) {
        free(objects);
    }
    
}

