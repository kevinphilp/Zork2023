/*! Main file for Bag, editing master, testing magit **/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "kputils.h"
#include "banned.h"
#include "bag.h"

static int node_id = 0;

/*! create_list:
  @brief      Function to create a new double linked list.
  @details    List is created empty with NULL links to head and tail.
  The size counter is set to zero.
  @note       Optionally add a note too.
  @param[in]  void
  @param[out]  struct list_t*
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

/*! push_head:
  @brief      Function adds data to a new node at head.
  @details    Data attached as a void pointer to head and the size counter is incremented. If list is empty head and tail point to new node. If not empty new node next points to head and new node previous points to NULL. List head set to new node.
  @note       Optionally add a note too.
  @param[in]  struct list_t* list, void* data
  @param[out]  void
  @return     Nothing.
*/
void push_head(struct list_t* list, void* data) {
    struct node_t *new_node = malloc(sizeof(struct node_t));
    if (!new_node) {
        printf("Problem allocating node.");
        exit(0);
    }
    new_node->node_id = node_id++;
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
    new_node->node_id = node_id++;
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

void* remove_by_id(struct list_t *list, int del_id) {
    if (list->size == 0) {  // Empty list
        return(NULL);
    } else {
        struct node_t *current_node = list->head;
        while (current_node != NULL) {
            if (current_node->node_id == del_id) {  // List one node only
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

void* get_by_id(struct list_t *list, int get_id) {
    if (list->size == 0) {  // Empty list
        return(NULL);
    } else {
        struct node_t *current_node = list->head;
        while (current_node != NULL) {
            if (current_node->node_id == get_id) {
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

/*! find_element:
  @brief      Function to search a linked list usng a custom match function.
  @details    Function accepts void pointers to data blocks.
  @note       Optionally add a note too.
  @param[in]  void *data, struct list_t *list, int(*fn)(void *a, void *b)
  @param[out]
  @return     void* - to data block or to NULL if not found.
*/

void* find_element( void *data, struct list_t *list, int(*fn)(void *a, void *b) ) {
    if (list) {
        struct node_t *current_node = list->head;
        while (current_node != NULL) {
            if (fn(data, current_node->data) == 0) {
                return(current_node->data);
            }
            current_node = current_node->next;
        }
    }
    return(NULL);
}



