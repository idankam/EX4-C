#include <stdio.h>
#include <stdlib.h>
#include "nodes_headers.h"

void set_edges(pnode *head, pnode node, int isOldNode){
    node->edges = NULL;
    if (isOldNode == 0)
    {
        node->next = NULL;
    }
    pedge currentEdge = NULL;
    
    int is_dig_flag;
    int dst;
    if (scanf("%d", &dst)){
        is_dig_flag = 1;
    }
    else{
        dst = (int)getchar();
        is_dig_flag = 0;
    }
    getchar();
    
    while(is_dig_flag) {
        
        int weight;
        scanf("%d", &weight);
        
        getchar();
        pedge newEdge = NULL;
        newEdge = (pedge)malloc(sizeof(edge));
        if(newEdge == NULL) {
            printf("Not enough memory!");
            exit(0);
        }

        newEdge->endpoint = getNode(head, dst);
        newEdge->weight = weight;
        newEdge->next = NULL;
        
        if(node->edges == NULL) {
            node->edges = newEdge;
            currentEdge = newEdge;
        }
        else {
            
            currentEdge->next = newEdge;
            currentEdge = currentEdge->next;

        }
        
        
        if (scanf("%d", &dst)){
            is_dig_flag = 1;
        }
        else{
            dst = (int)getchar();
            is_dig_flag = 0;
        }
        getchar();

    }

    ungetc(' ', stdin);
    ungetc(dst, stdin);
}

pnode getNode(pnode *head, int id) {
    if(head == NULL) {
        return NULL;
    }
    pnode currentNode = *head;
    while(currentNode != NULL && currentNode->node_num != id) {
        currentNode = currentNode->next;
    }
    return currentNode;
}


void create_edges_of_node(pnode *head) {
    
    int node_id;
    scanf("%d", &node_id);
    getchar();
    pnode node = getNode(head, node_id);

    node->edges = NULL;
    pedge currentEdge = NULL;

    int is_dig_flag;
    int dst;
    if (scanf("%d", &dst)){
        is_dig_flag = 1;
    }
    else{
        dst = (int)getchar();
        is_dig_flag = 0;
    }

    getchar();

    while(is_dig_flag) {
        
        int weight;
        scanf("%d", &weight);
        getchar();
        pedge newEdge = (pedge)malloc(sizeof(edge));
        if(newEdge == NULL) {
            printf("Not enough memory!");
            exit(0);
        }
        newEdge->endpoint = getNode(head, dst);
        newEdge->weight = weight; 
        newEdge->next = NULL;
        if(node->edges == NULL) { 
            node->edges = newEdge;
            currentEdge = newEdge;
        }
        else { 
            currentEdge->next = newEdge;
            currentEdge = currentEdge->next;
        }
        if (scanf("%d", &dst)){
            is_dig_flag = 1;
        }
        else{
            dst = (int)getchar();
            is_dig_flag = 0;
        }
        getchar();
        
    }

    char next_operation = (char)dst;    
    ungetc(' ', stdin);
    ungetc(next_operation, stdin);
}

