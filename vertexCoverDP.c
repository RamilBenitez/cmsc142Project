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

// helper to calculate vertex cover size
void vertexCover(Node* root, int* include, int* exclude){
    if(!root){
        *include =0;
        *exclude =0;
        return;
    }

    //stores resuts from subtrees
    int left_include, left_exclude;
    int right_include, right_exclude;

    //calculate for right and lefr subtress recursively
    vertexCover(root->left, &left_include, &left_exclude);
    vertexCover(root->right, &right_include, &right_exclude);

    //including the current node in vertex cover
    *include = 1 + (left_include < left_exclude ? left_include : left_exclude)// min of left
    + (right_include <right_exclude ? right_include : right_exclude); // min of right

    //excluding thee current node in vertex cover
    *exclude = left_include  + right_include;
    }

    //main function to compute min vertex cover
int minVertexCover(Node* root) {
    int include, exclude;

    vertexCover(root, &include, &exclude);

     //retrn the smaller
    return(include < exclude) ? include:exclude;
    }

//main program

int main(){

    //tree
    Node* root = newNode(10);
    root->left = newNode(20);
    root->right = newNode(30);
    root->left->left =newNode(40);
    root->left->right=newNode(50);
    root->right->right=newNode(60);

    printf("Minimum Vertex Cover Size: %d\n", minVertexCover(root));

    return 0;
    
}