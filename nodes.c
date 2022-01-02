#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "nodes_headers.h"

void set_edges(pnode *head, pnode node){
    node->edges = NULL;
    node->next = NULL;
    pedge currentEdge;
    
    // char dst = getchar();
    int is_dig_flag;
    int dst;
    if (scanf("%d", &dst)){
        is_dig_flag = 1;
    }
    else{
        dst = (int)getchar();
        is_dig_flag = 0;
    }
    printf("%d, %d\n", is_dig_flag, dst);
    getchar();
    
    while(is_dig_flag) {
        
        //get weight from buffer
        //int weight = (int)getchar() - '0';
        int weight;
        scanf("%d", &weight);
        printf("%d\n", weight);
        getchar();
        
        pedge newEdge = (pedge)malloc(sizeof(edge));
        if(newEdge == NULL) {
            printf("Not enough memory!");
            exit(0);
        }
            //assign parameters
        newEdge->endpoint = getNode(head, dst);
        newEdge->weight = weight;
        //if first edge to link, make it the head 
        if(node->edges == NULL) {
            node->edges = newEdge;
            currentEdge = newEdge;
        }
        else {
            //link this edge to the end of the linked list
            currentEdge->next = newEdge;
            currentEdge = currentEdge->next;
        }
        
        // dst = getchar(); //get dst from buffer
        
        if (scanf("%d", &dst)){
            is_dig_flag = 1;
        }
        else{
            dst = (int)getchar();
            is_dig_flag = 0;
        }
        getchar();

        printf("%d, %d\n", is_dig_flag, dst);
    }
    // puts space and char back in buffer because its on to new command
    ungetc(' ', stdin);
    ungetc(dst, stdin);
}

pnode getNode(pnode *head, int id) {
    if(head == NULL) {
        return NULL;
    }
    pnode currentNode = *head;
    while(currentNode != NULL && currentNode->node_num != id) { //update only if node does not have given id and is not null
        currentNode = currentNode->next;
    }
    return currentNode;
}


void create_edges_of_node(pnode *head) {
    
    int node_id;
    scanf("%d", &node_id);
    getchar(); //skip spaces
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
    printf("%d, %d\n", is_dig_flag, dst);

    getchar();

    while(is_dig_flag) {
        
        int weight;
        scanf("%d", &weight);

        printf("%d\n", weight);
        

        getchar();
        pedge newEdge = (pedge)malloc(sizeof(edge));
        if(newEdge == NULL) {
            printf("Not enough memory!");
            exit(0);
        }
        newEdge->endpoint = getNode(head, dst);
        newEdge->weight = weight; 
        
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

        printf("%d, %d\n", is_dig_flag, dst);
        
    }

    char next_operation = (char)dst;
    printf("%c", next_operation);
    
    ungetc(' ', stdin);
    ungetc(next_operation, stdin);
}

