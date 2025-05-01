//Dynamic Program Version
// Minimum Vertex Cover

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


//node structure for tree repres.
typedef struct Node{
    int data;
    struct Node *left,*right;
}Node;

// new tree node
Node* newNode(int data){
    Node* node = (Node*)malloc(sizeof(Node));
    node -> data = data;
    node -> left = node->right = NULL; 
    return node;
}