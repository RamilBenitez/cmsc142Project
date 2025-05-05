//Dynamic Program Version
// Minimum Vertex Cover

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

//node structure for tree repres.
typedef struct Node{
    int data;
    struct Node *left, *right;
}Node;

// new tree node
Node* newNode(int data){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL; 
    return node;
}

// helper to calculate vertex cover size
void vertexCover(Node* root, int* include, int* exclude){
    if(!root){
        *include = 0;
        *exclude = 0;
        return;
    }

    //stores results from subtrees
    int left_include, left_exclude;
    int right_include, right_exclude;

    //calculate for right and left subtrees recursively
    vertexCover(root->left, &left_include, &left_exclude);
    vertexCover(root->right, &right_include, &right_exclude);

    //including the current node in vertex cover
    *include = 1 + (left_include < left_exclude ? left_include : left_exclude) // min of left
             + (right_include < right_exclude ? right_include : right_exclude); // min of right

    //excluding the current node in vertex cover
    *exclude = left_include + right_include;
}

//main function to compute min vertex cover
int minVertexCover(Node* root) {
    int include, exclude;

    vertexCover(root, &include, &exclude);

    //return the smaller
    return (include < exclude) ? include : exclude;
}

// Free the memory allocated for the tree
void freeTree(Node* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// Function to create graph351 as a tree
Node* createGraph351Tree() {
    // Create tree representation of graph351

    Node* root = newNode(0);  // A
    root->left = newNode(1);  // B
    root->left->left = newNode(2);  // C
    root->left->left->left = newNode(3);  // D
    root->left->left->left->left = newNode(5);  // F
    root->left->left->left->right = newNode(6);  // G
    root->left->left->right = newNode(4);  // E
    root->left->left->right->left = newNode(5);  // F (duplicate)
    
    return root;
}

// Function to create graphConnected as a tree
Node* createGraphConnectedTree() {
    // approximation only
    Node* root = newNode(0);  // A
    root->left = newNode(1);  // B
    root->right = newNode(2);  // C
    root->left->left = newNode(3);  // D
    root->left->right = newNode(4);  // E
    root->right->left = newNode(5);  // F
    root->right->right = newNode(6);  // G
    
    return root;
}

// Function to create graphBipartite as a tree
Node* createGraphBipartiteTree() {
    // approximation only
    Node* root = newNode(0);  // A
    
    // First level - left side of bipartite graph
    root->left = newNode(1);  // B
    root->right = newNode(2);  // C
    
    // Second level
    root->left->left = newNode(3);  // D
    root->left->right = newNode(4);  // E
    root->right->left = newNode(5);  // F
    root->right->right = newNode(6);  // G
    
    // Third level
    root->left->left->left = newNode(7);  // H
    root->left->right->left = newNode(8);  // I
    root->right->left->left = newNode(9);  // J
    
    return root;
}

// Function to create graphBig as a tree
Node* createGraphBigTree() {
    // approximation only
    Node* root = newNode(0);  // A
    
    // Level 1
    root->left = newNode(1);  // B
    root->right = newNode(2);  // C
    
    // Level 2
    root->left->left = newNode(3);  // D
    root->left->right = newNode(4);  // E
    root->right->left = newNode(5);  // F
    root->right->right = newNode(6);  // G
    
    // Level 3
    root->left->left->left = newNode(7);  // H
    root->left->left->right = newNode(8);  // I
    root->left->right->left = newNode(9);  // J
    root->left->right->right = newNode(10);  // K
    root->right->left->left = newNode(11);  // L
    root->right->left->right = newNode(12);  // M
    root->right->right->left = newNode(13);  // N
    root->right->right->right = newNode(14);  // O
    
    // Level 4
    root->left->left->left->left = newNode(15);  // P
    root->left->left->left->right = newNode(16);  // Q
    root->left->left->right->left = newNode(17);  // R
    root->left->left->right->right = newNode(18);  // S
    root->left->right->left->left = newNode(19);  // T
    root->left->right->left->right = newNode(20);  // U
    
    return root;
}

// Function to time a test
double timeTest(Node* (*createTreeFunc)(), const char* graphName) {
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    
    Node* root = createTreeFunc();
    int minCover = minVertexCover(root);
    printf("Minimum Vertex Cover Size for %s: %d\n", graphName, minCover);
    freeTree(root);
    
    end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}

//main program
int main() {
    double time_used;
    
    printf("Testing graph351...\n");
    time_used = timeTest(createGraph351Tree, "graph351");
    printf("Time taken for graph351: %.6f seconds\n\n", time_used);
    
    printf("Testing graphConnected...\n");
    time_used = timeTest(createGraphConnectedTree, "graphConnected");
    printf("Time taken for graphConnected: %.6f seconds\n\n", time_used);
    
    printf("Testing graphBipartite...\n");
    time_used = timeTest(createGraphBipartiteTree, "graphBipartite");
    printf("Time taken for graphBipartite: %.6f seconds\n\n", time_used);
    
    printf("Testing graphBig...\n");
    time_used = timeTest(createGraphBigTree, "graphBig");
    printf("Time taken for graphBig: %.6f seconds\n", time_used);
    
    return 0;
}