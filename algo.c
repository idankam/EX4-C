#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include "nodes_headers.h"
#include "algorithms.h"



void build_graph_cmd(pnode *head) {

    int number_of_nodes;
    scanf("%d", &number_of_nodes);
    getchar();

    if(number_of_nodes == 0) { 
        return;
    }

    pnode tmpNode = (pnode)malloc(sizeof(node));
    if(tmpNode == NULL) {
        printf("Not enough memory!");
        exit(0);
    }

    tmpNode->node_num = 0;
    tmpNode->next = NULL;
    *head = tmpNode;
    pnode curr = tmpNode;
    
    for (int i = 1; i < number_of_nodes; i++) {
        pnode newNode = (pnode)malloc(sizeof(node));
        if(newNode == NULL) {
            printf("Not enough memory!");
            exit(0);
        }
        
        newNode->node_num = i;
        newNode->next = NULL;
        curr->next = newNode;

        curr = curr->next; 
    }
    
    for (int i = 0; i < number_of_nodes; i++) {
        char should_be_n = getchar();
        getchar(); 
        while (should_be_n == 'n') {
            create_edges_of_node(head); 
            should_be_n = getchar();
            getchar();
        }
        
        char not_n = should_be_n;
        ungetc(' ', stdin);
        ungetc(not_n, stdin);
    }
}

void insert_node_cmd(pnode *head) { 
    int id;
    scanf("%d", &id);
    getchar();
    pnode oldNode = getNode(head, id);
    if(oldNode == NULL) { 
        pnode newNode = (pnode)malloc(sizeof(node)); 
        if(newNode == NULL) {
            printf("Not enough memory!");
            exit(0);
        } 
        newNode->node_num = id;

        int notOldNode = 0;
        set_edges(head, newNode, notOldNode);
        
        if(*head == NULL) {
            *head = newNode;
        }
        else {
            pnode currentNode = *head;
            int has_next;
            if(currentNode->next != NULL){
                has_next = 1;
            }
            else{
                has_next = 0;
            }
            while(has_next) {
                currentNode = currentNode->next;

                if(currentNode->next != NULL){
                    has_next = 1;
                }
                else{
                    has_next = 0;
                }
            }
            currentNode->next = newNode;
        }  
    }

    else {
        
        pedge currentEdge = oldNode->edges;
        pedge tmpPointer;
        while(currentEdge != NULL) {
            tmpPointer = currentEdge->next;
            free(currentEdge);
            currentEdge = tmpPointer;
        }
        int isOldNode = 1;
        set_edges(head, oldNode, isOldNode);
    }
    
}


void delete_node_cmd(pnode *head) {

    if(*head == NULL){
        return;
    }
    int nodeToDeleteID;
    scanf("%d", &nodeToDeleteID);
    pnode nodeToDelete = getNode(head, nodeToDeleteID);
    getchar(); 
    pnode nextNode = NULL;
    if((*head) == nodeToDelete){ 
        nextNode = (*head)->next;
        *head = nextNode;
    }
    else {
        pnode currentNode = *head;
        while (currentNode->next != NULL) { 
            if (currentNode->next == nodeToDelete) {
                currentNode->next = currentNode->next->next;
            }
            currentNode = currentNode->next;
        }
    }
    pnode currentNode = *head;
    pedge currentEdge = NULL;
    pedge nextEdge = NULL;
    while(currentNode != NULL) {
        if (currentNode->edges != NULL) {
            
            if (currentNode->edges->endpoint == nodeToDelete) { 
                nextEdge = currentNode->edges->next;
                free(currentNode->edges);
                currentNode->edges = nextEdge;
            }
            else {
                currentEdge = currentNode->edges;
                while (currentEdge->next != NULL) {
                    if (currentEdge->next->endpoint == nodeToDelete) {
                        nextEdge = currentEdge->next->next;
                        free(currentEdge->next);
                        currentEdge->next = nextEdge;
                        break;
                    }
                    currentEdge = currentEdge->next;
                }
            }
        }
        currentNode = currentNode->next; 
    }
    
    currentEdge = nodeToDelete->edges;
    nextEdge = NULL;
    while (currentEdge != NULL) { 
        nextEdge = currentEdge->next;
        free(currentEdge);
        currentEdge = nextEdge;
        
    }
    free(nodeToDelete); 
}

void printGraph_cmd(pnode head) {
    pnode currentNode = head;
    while(currentNode != NULL) {
        printf("\nNode %d: Edges:\t[ | ", currentNode->node_num);
        
        pedge currentEdge = currentNode->edges;
        
        while(currentEdge != NULL) {
            printf("dst = %d, weight = %d | ", currentEdge->endpoint->node_num, currentEdge->weight);
            currentEdge = currentEdge->next;
        }
        printf("]");
        currentNode = currentNode->next;
    }
    putchar('\n');
}

void deleteGraph_cmd(pnode* head) {
    if(*head == NULL){
        return;
    }

    pnode currentNode = *head;
    pnode nextNode;

    while (currentNode != NULL) {
        pedge currentEdge = currentNode->edges;
        pedge nextEdge;
        
        while(currentEdge != NULL) {
            nextEdge = currentEdge->next;
            free(currentEdge);
            currentEdge = nextEdge;
        }
        
        nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;
    }
    head = NULL;
}

void shortsPath_cmd(pnode head) {

    int IN_THE_QUEUE = 0, NOT_IN_THE_QUEUE = 1;

    // change to scanf
    int src, dst;
    scanf("%d", &src);
    getchar();
    scanf("%d", &dst);
    getchar();

    pnode currentNode = head;
    int numberOfNodes = 0; // will update in next loop

    //change weight to max of each node
    //(except for source node pathWeight is zero)
    while(currentNode != NULL) {
        if(currentNode->node_num != src){
            currentNode->pathWeight = INT_MAX;
        }
        else{
            currentNode->pathWeight = 0;
        }
        currentNode->isInTheQueue = IN_THE_QUEUE;
        numberOfNodes++;
        currentNode = currentNode->next;
    }
    int roundNumber = 0;
    while(roundNumber < numberOfNodes){
        pnode minimumNode = NULL;
        int min_p = INT_MAX;
        currentNode = head;

        // find the node with the minimun weight 
        while(currentNode != NULL) {
            if(currentNode->pathWeight <= min_p && currentNode->isInTheQueue == IN_THE_QUEUE) {
                min_p = currentNode->pathWeight;
                minimumNode = currentNode;
            }
            currentNode = currentNode->next;
        }
        //update isInTheQueue flag
        minimumNode->isInTheQueue = NOT_IN_THE_QUEUE;
        
        if(minimumNode->node_num == dst){
            int dstWeight = minimumNode->pathWeight;
            printf("Dijsktra shortest path: %d\n", dstWeight);
            return;
        }

        if(minimumNode->pathWeight == INT_MAX){
            printf("Dijsktra shortest path: -1\n");
            return;
        }

        pedge currentEdge = minimumNode->edges;
        while(currentEdge != NULL){
            int currentNeighborWeight = currentEdge->endpoint->pathWeight;
            int minNodeWeight = minimumNode->pathWeight;
            int edgeToNeigborWeight = currentEdge->weight;
            if(currentNeighborWeight > minNodeWeight + edgeToNeigborWeight){
                currentEdge->endpoint->pathWeight = minNodeWeight + edgeToNeigborWeight;
            }
            currentEdge = currentEdge->next;
        }
        roundNumber++;
    }
}   

void TSP(pnode head){

    int MINIMUM_TSP_WEIGHT = INT_MAX;

    // size of nodes in the list
    int size;
    scanf("%d", &size);
    getchar();

    int cities[size]; //declare size of list of nodes to visit
    for(int i = 0; i < size; i++) { //loop size amount of times im order to add the nodes to be isInTheQueue to cities
        scanf("%d", &cities[i]);
        getchar(); //skip spaces
    }

    permute(cities, 0, size-1, &MINIMUM_TSP_WEIGHT, size, head);
    
    if (MINIMUM_TSP_WEIGHT == INT_MAX){
        printf("TSP shortest path: -1\n");
    }else{
        printf("TSP shortest path: %d\n", MINIMUM_TSP_WEIGHT);
    }
}

/* Function to swap values at two pointers */
void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
 
/* Function to print permutations of string
This function takes three parameters:
1. String
2. Starting index of the string
3. Ending index of the string. */
void permute(int *cities, int l, int r, int *MINIMUM_TSP_WEIGHT, int size, pnode head)
{
    int i;
    if (l == r){
        int tmpWeight = minPathWeightFotPermutation(cities, size, head);
        if(tmpWeight < *MINIMUM_TSP_WEIGHT){
            *MINIMUM_TSP_WEIGHT = tmpWeight;
        }
    }
    else
    {
        for (i = l; i <= r; i++)
        {
            swap((cities+l), (cities+i));
            permute(cities, l+1, r, MINIMUM_TSP_WEIGHT, size, head);
            swap((cities+l), (cities+i)); //backtrack
        }
    }
}

int minPathWeightFotPermutation(int* a, int size, pnode head){
    if (size <=1 ){
        return 0;
    }
    else{
        int sum = 0;
        for (int i = 0; i < size-1; i++)
        {
            int dij = dijkstra(head, a[i], a[i+1]);
            if (dij == INT_MAX){
                return INT_MAX;
            }
            else{
                sum += dij;
            }
        }
        return sum;
    }
}

int dijkstra(pnode head, int src, int dst){
    int IN_THE_QUEUE = 0, NOT_IN_THE_QUEUE = 1;

    pnode currentNode = head;
    int numberOfNodes = 0; // will update in next loop

    //change weight to max of each node
    //(except for source node pathWeight is zero)
    while(currentNode != NULL) {
        if(currentNode->node_num != src){
            currentNode->pathWeight = INT_MAX;
        }
        else{
            currentNode->pathWeight = 0;
        }
        currentNode->isInTheQueue = IN_THE_QUEUE;
        numberOfNodes++;
        currentNode = currentNode->next;
    }
    int roundNumber = 0;
    while(roundNumber < numberOfNodes){
        pnode minimumNode = NULL;
        int min_p = INT_MAX;
        currentNode = head;

        // find the node with the minimun weight 
        while(currentNode != NULL) {
            if(currentNode->pathWeight <= min_p && currentNode->isInTheQueue == IN_THE_QUEUE) {
                min_p = currentNode->pathWeight;
                minimumNode = currentNode;
            }
            currentNode = currentNode->next;
        }
        //update isInTheQueue flag
        minimumNode->isInTheQueue = NOT_IN_THE_QUEUE;
        
        if(minimumNode->node_num == dst){
            int dstWeight = minimumNode->pathWeight;
            return dstWeight;
        }

        if(minimumNode->pathWeight == INT_MAX){            
            return INT_MAX;
        }

        pedge currentEdge = minimumNode->edges;
        while(currentEdge != NULL){
            int currentNeighborWeight = currentEdge->endpoint->pathWeight;
            int minNodeWeight = minimumNode->pathWeight;
            int edgeToNeigborWeight = currentEdge->weight;
            if(currentNeighborWeight > minNodeWeight + edgeToNeigborWeight){
                currentEdge->endpoint->pathWeight = minNodeWeight + edgeToNeigborWeight;
            }
            currentEdge = currentEdge->next;
        }
        roundNumber++;
    }
    return INT_MAX;
}
