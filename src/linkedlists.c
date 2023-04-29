#include <stdio.h>
#include <stdlib.h>

struct Node
{
    struct Node* next;
    struct Node* prev;
    struct Node* head;
    void* data;
    unsigned int index;
    int id;
};

typedef struct Node* Node;

Node alloc_node(void* dataptr, int id)
{
    Node n = malloc(sizeof(struct Node));
    n->data = dataptr;
    n->id = id;
    n->index = 0;
    n->next = 0;
    n->prev = 0;
    return n;
}

void link(Node a, Node b)
{
    a->next = b;
    b->prev = a;
    b->head = a->head;
    b->index = a->index + 1;
}

Node get_tail(Node l)
{
    
    while (l->next)
    {
        l = l->next;
    }
    return l;
}

Node get_node(Node l, unsigned int index)
{
    
    while ((l->index != index) && l) 
    {
        
        if (l->index > index)
        {
            l = l->prev;
        }
        else
        {
            l = l->next;
        }
    }
    return l;
}

Node append_node(Node tail, Node a)
{
    tail = get_tail(tail);
    link(tail, a);
    return a;
}

Node remove_node(Node l, unsigned int index)
{
    Node r = get_node(l, index);
    
    link(r->prev, r->next);
    
    Node i = r->next;

    unsigned int ni = index;

    while (i) {
        i->index = ni;
        ni++;
        i = i->next;
    }
    return r;
}