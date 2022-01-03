#ifndef ALGORITHMS
#define ALGORITHMS

#include "nodes_headers.h"

void build_graph_cmd(pnode *head);
void insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
void shortsPath_cmd(pnode head);
void permute(int *cities, int l, int r, int *MINIMUM_TSP_WEIGHT, int size, pnode head);
void swap(int *x, int *y);
void TSP(pnode head);
int dijkstra(pnode head, int src, int dst);
int minPathWeightFotPermutation(int* a, int size, pnode head);

#endif