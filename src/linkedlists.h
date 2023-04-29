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

Node alloc_node(void* dataptr, int id);
void link(Node a, Node b);
Node get_tail(Node l);
Node get_node(Node l, unsigned int index);
Node append_node(Node tail, Node a);
Node remove_node(Node l, unsigned int index);