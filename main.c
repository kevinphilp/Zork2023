/*! Main file for Bag, should go **/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "kputils.h"
#include "banned.h"

/*! \page mainpage Introduction */

/*! struct node_t */
struct node_t {
    int id;
    void* data;
    struct node_t *next;
    struct node_t *prev;
};

struct list_t {
    int size;
    struct node_t *head;
    struct node_t *tail;
};

static int node_id = 0;

struct list_t* create_list();
void push_head(struct list_t* list, void* data);
void push_tail(struct list_t* list, void* data);
void* pop_head(struct list_t *list);
void* pop_tail(struct list_t *list);
void delete_list(struct list_t *list);
void empty_list(struct list_t *list);
void* get_by_id(struct list_t *list, int id);
void* remove_by_id(struct list_t *list, int id);

int main() {
    // create a new list
    struct list_t *int_list = create_list();
    char x[12] = "aaa";
    char y[12] ="bbb";
    char z[12] = "cccc";
    push_tail(int_list, (void*)&z);
    push_tail(int_list, (void*)&y);
    push_head(int_list, (void*)&x);
    push_tail(int_list, (void*)&z);
    push_tail(int_list, (void*)&y);
    push_head(int_list, (void*)&x);
    push_head(int_list, (void*)"asdf");
    printf("Initial size -- %d\n", int_list->size);
    printf("Remove by id 0 - %s\n", (char*)remove_by_id(int_list, 0));
    printf("Remove by id 5 - %s\n", (char*)remove_by_id(int_list, 5));
    printf("Remove by id 2 - %s\n", (char*)remove_by_id(int_list, 2));
    struct node_t *int_ptr = int_list->head;
    while (int_ptr != NULL) {
        printf("%d - %s\n", int_ptr->id, (char*)int_ptr->data);
        int_ptr = int_ptr->next;
    }
    int_ptr = int_list->tail;
    while (int_ptr != NULL) {
        printf("%d - %s\n", int_ptr->id, (char*)int_ptr->data);
        int_ptr = int_ptr->prev;
    }

    printf("Final size -- %d\n", int_list->size);
    delete_list(int_list);
}

/*! Function definition:
  @brief      Function to create a new double linked list.
  @details    List is created empty with NULL links to head and tail.
  The size counter is set to zero.
  @note       Optionally add a note too.
  @param[in]  void
  @return     List pointer
  - type struct *list_t
             - Some text
*/

struct list_t* create_list(void) {
    struct list_t *new_list = NULL;
    new_list = malloc(sizeof(struct list_t));
    if (!new_list) {
        printf("Problem allocating list.");
        exit(0);
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
