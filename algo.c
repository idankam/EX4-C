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

        set_edges(head, newNode);
        
        if(*head == NULL) {
            *head = newNode;
        }
        else {
            pnode currentNnode = *head;
            int has_next;
            if(currentNnode->next != NULL){
                has_next = 1;
            }
            else{
                has_next = 0;
            }
            while(has_next) {
                currentNnode = currentNnode->next;

                if(currentNnode->next != NULL){
                    has_next = 1;
                }
                else{
                    has_next = 0;
                }
            }
            currentNnode->next = newNode;
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
        
        set_edges(head, oldNode);
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
    pnode currentNnode = *head;
    pedge currentEdge = NULL;
    pedge nextEdge = NULL;
    while(currentNnode != NULL) {
        if (currentNnode->edges != NULL) {
            
            if (currentNnode->edges->endpoint == nodeToDelete) { 
                nextEdge = currentNnode->edges->next;
                free(currentNnode->edges);
                currentNnode->edges = nextEdge;
            }
            else {
                currentEdge = currentNnode->edges;
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
        currentNnode = currentNnode->next; 
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
    pnode currentNnode = head;
    while(currentNnode != NULL) {
        printf("\nNode %d: Edges:\t[ | ", currentNnode->node_num);
        
        pedge currentEdge = currentNnode->edges;
        
        while(currentEdge != NULL) {
            printf("dst = %d, weight = %d | ", currentEdge->endpoint->node_num, currentEdge->weight);
            currentEdge = currentEdge->next;
        }
        printf("]");
        currentNnode = currentNnode->next;
    }
    putchar('\n');
}

void deleteGraph_cmd(pnode* head) {
    if(*head == NULL){
        return;
    }

    pnode currentNnode = *head;
    pnode nextNode;

    while (currentNnode != NULL) {
        pedge currentEdge = currentNnode->edges;
        pedge nextEdge;
        
        while(currentEdge != NULL) {
            nextEdge = currentEdge->next;
            free(currentEdge);
            currentEdge = nextEdge;
        }
        
        nextNode = currentNnode->next;
        free(currentNnode);
        currentNnode = nextNode;
    }
    head = NULL;
}

void shortsPath_cmd(pnode head) {
    //receive source and dst from buffer
    int src = (int)getchar() - '0';
    getchar();
    int dst = (int)getchar() - '0';
    getchar();
    pnode curr = head;
    int counter = 0;
    //change priority of every node to max int except for source node priority is zero
    while(curr != NULL) {
        if(curr->node_num != src){
            curr->priority = INT_MAX;
        }
        else{
            curr->priority = 0;
        }
        curr->visited = 0;
        counter++;
        curr = curr->next;
    }
    int i = 0;
    while(i < counter){
        pnode smallest = NULL;
        int min_p = INT_MAX;
        curr = head;
        //find node with smallest priority
        while(curr != NULL) {
            if(curr->priority <= min_p && curr->visited == 0) {
                min_p = curr->priority;
                smallest = curr;
            }
            curr = curr->next;
        }
        //update tag visited 
        smallest->visited = 1;
        //if the smallest priority is int_max, then there is no path betweent the src and dst node
        if(smallest->priority == INT_MAX){
            printf("Dijsktra shortest path: -1 \n");
            return;
        }
        //if the node smallest priority is the dst node then we've found our shortest path 
        if(smallest->node_num == dst){
            printf("Dijsktra shortest path: %d \n", smallest->priority);
            return;
        }
        pedge currentEdge = smallest->edges;
        //go through edges to check priority of neighboring nodes
        while(currentEdge != NULL){
            if(currentEdge->endpoint->priority > smallest->priority + currentEdge->weight){ //relaxing
                currentEdge->endpoint->priority = smallest->priority + currentEdge->weight;
            }
            currentEdge = currentEdge->next;
        }
        i++;
    }
}   

//finds the shortest path distance that visists specific nodes on the graph
void TSP_cmd(pnode head) {
    int size = (int)getchar() - '0'; //get size of "list" of cities from buffer
    getchar(); //skip spaces
    int cities[size]; //declare size of list of nodes to visit
    for(int i = 0; i < size; i++) { //loop size amount of times im order to add the nodes to be visited to cities
        cities[i] = (int)getchar() - '0';
        getchar(); //skip spaces
    }
    int min_weight = INT_MAX; //originally declare min_weight to be the highest it can be
    for(int i = 0; i < size; i++) { //runs through every option of starter nodes
        int new_cities[size-1];
        int j = 0;
        for(int k = 0; k < size; k++) {
            if(i != k) { //j moves forward only when something is inserted, meaning i != k
                new_cities[j++] = cities[k]; //copy over to new array
            }
        }
        int weight = tsp_helper(head, cities[i], new_cities, size-1);
        if(weight == -1) { //no path exists
            continue;
        }
        if(weight < min_weight) { //we have found a smaller weight so update min_weight
            min_weight = weight;
        }
    }
    if(min_weight != INT_MAX) { //if min_weight was changed throughout the function, that is the shortest path for TSP
        printf("TSP shortest path: %d \n", min_weight);
    }
    else { //if min_weight was not changed, no such path exists that visits each node in cities
        printf("TSP shortest path: -1 \n");
    }
}

//TSP helper function that ginds the shortest path between two nodes. similar to shortest_path_cmd
int get_shortest_path_dist(pnode head, int src, int dst) {
    pnode curr = head;
    int counter = 0;
    //change priority of every node to max int except for source node priority is zero
    while(curr != NULL) {
        if(curr->node_num != src){
            curr->priority = INT_MAX;
        }
        else{
            curr->priority = 0;
        }
        curr->visited = 0;
        counter++;
        curr = curr->next;
    }
    int i = 0;
    while(i < counter){
        pnode smallest = NULL;
        int min_p = INT_MAX;
        curr = head;
        //find node with smallest priority
        while(curr != NULL) {
            if(curr->priority <= min_p && curr->visited == 0) {
                min_p = curr->priority;
                smallest = curr;
            }
            curr = curr->next;
        }
        //update tag visited 
        smallest->visited = 1;
        //if the smallest priority is int_max, then there is no path betweent the src and dst node
        if(smallest->priority == INT_MAX){
            return -1;
        }
        //if the node smallest priority is the dst node then we've found our shortest path 
        if(smallest->node_num == dst){
            return smallest->priority;
        }
        pedge currentEdge = smallest->edges;
        //go through edges to check priority of neighboring nodes
        while(currentEdge != NULL){
            if(currentEdge->endpoint->priority > smallest->priority + currentEdge->weight){ //relaxing
                currentEdge->endpoint->priority = smallest->priority + currentEdge->weight;
            }
            currentEdge = currentEdge->next;
        }
        i++;
    }
    return -1;
}

//TSP recursive helper function
int tsp_helper(pnode head, int src, int *cities, int size) {
    if(size == 0) { //base case, no more options to check
        return 0;
    }
    int min_weight = INT_MAX;
    //now checking all options with specific starter node
    for(int i = 0; i < size; i++) {
        int new_cities[size-1];
        int j = 0;
        for(int k = 0; k < size; k++) {
            if(i != k) {
                new_cities[j++] = cities[k];
            }
        }
        int edge_weight = get_shortest_path_dist(head, src, cities[i]);
        if(edge_weight == -1) { //no path between src and dst, go to next iteration
            continue;
        }
        int res = tsp_helper(head, cities[i], new_cities, size-1); //call recursively to find shortest path visiting each node in new_cities
        if(res == -1) {
            continue;
        }
        int weight = edge_weight + res; //distance from starter node to first node in new_cities + cost of path visiting each node in new_cities
        if(weight < min_weight) { //found a smaller cost
            min_weight = weight; //update weight
        }
    }
    //min_weight was not changed so no path exists that covers every node in new_cities
    if(min_weight == INT_MAX) {
        return -1;
    }
    return min_weight; //return TSP shortes path
}