#ifndef BAG_H
#define BAG_H

struct node_t {
    int node_id;
    void* data;
    struct node_t *next;
    struct node_t *prev;
};

struct list_t {
    int size;
    struct node_t *head;
    struct node_t *tail;
};

struct list_t* create_list(void);
void push_head(struct list_t* list, void* data);
void push_tail(struct list_t* list, void* data);
void* pop_head(struct list_t *list);
void* pop_tail(struct list_t *list);
void delete_list(struct list_t *list);
void empty_list(struct list_t *list);
void* get_by_id(struct list_t *list, int node_id);
void* remove_by_id(struct list_t *list, int node_id);
int find_element( void *data, struct list_t *list, int(*fn)(void *a, void *b) );

#endif
