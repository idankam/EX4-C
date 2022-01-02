#include <stdio.h>
#include <string.h>
#include "algorithms.h"

int main() {
    pnode head = NULL;
    char operation_char;
    operation_char = getchar();

    while(operation_char == 'A' || operation_char == 'B' || operation_char == 'D' || operation_char == 'S' || operation_char == 'T') {
        getchar();

        if(operation_char == 'A') {
            deleteGraph_cmd(&head);
            head = NULL; 
            build_graph_cmd(&head); 
            // printGraph_cmd(head);
        }
        else if(operation_char == 'B') {
            insert_node_cmd(&head);
        }
        else if(operation_char == 'D') {
            delete_node_cmd(&head);
        }
        else if(operation_char == 'S') {
            shortsPath_cmd(head);
        }
        else if(operation_char == 'T') {
            TSP_cmd(head);
        }
        // next option
        operation_char = getchar();
    }
    deleteGraph_cmd(&head);
    return 0;
}