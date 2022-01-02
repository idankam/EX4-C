#ifndef NODES_HEADERS
#define NODES_HEADERS

typedef struct GRAPH_NODE_ *pnode;;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;

typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
    int priority;
    int visited;
} node, *pnode;

pnode getNode(pnode *head, int id);
void create_edges_of_node(pnode *node);
void set_edges(pnode *head, pnode new_node);

#endif