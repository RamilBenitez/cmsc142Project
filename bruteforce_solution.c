#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAX_VERTICES 100
#define MAX_EDGES 1000

// Structure to represent an edge
typedef struct {
    int u, v;
} Edge;

// Structure to represent a graph
typedef struct {
    int numVertices;
    int numEdges;
    Edge edges[MAX_EDGES];
} Graph;

// Function to create a graph
Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->numEdges = 0;
    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int u, int v) {
    graph->edges[graph->numEdges].u = u;
    graph->edges[graph->numEdges].v = v;
    graph->numEdges++;
}

// Function to verify if a subset of vertices forms a valid vertex cover
bool verifyVertexCover(bool* cover, Graph* graph) {
    // Check that at least one vertex from each edge appears in the cover
    for (int i = 0; i < graph->numEdges; i++) {
        Edge edge = graph->edges[i];
        if (!cover[edge.u] && !cover[edge.v]) {
            return false; // This edge is not covered
        }
    }
    return true; // All edges are covered
}

// Function to generate all subsets of size k using backtracking
void generateSubsets(int* vertices, int n, bool* currentSubset, bool* bestSubset, 
                      int k, int start, Graph* graph, bool* found, int* minSize) {
    // If we've selected k vertices, check if they form a valid cover
    if (k == 0) {
        if (verifyVertexCover(currentSubset, graph)) {
            // Count the number of vertices in the current subset
            int size = 0;
            for (int i = 0; i < n; i++) {
                if (currentSubset[i]) size++;
            }
            
            // Update the best cover if this is smaller
            if (!*found || size < *minSize) {
                *minSize = size;
                *found = true;
                memcpy(bestSubset, currentSubset, n * sizeof(bool));
            }
        }
        return;
    }
    
    // If we have no more vertices to consider, return
    if (start >= n) {
        return;
    }
    
    // Include the current vertex in the subset
    currentSubset[start] = true;
    generateSubsets(vertices, n, currentSubset, bestSubset, k - 1, start + 1, graph, found, minSize);
    
    // Exclude the current vertex from the subset
    currentSubset[start] = false;
    generateSubsets(vertices, n, currentSubset, bestSubset, k, start + 1, graph, found, minSize);
}

// Function to find the minimum vertex cover using brute force
void vertexCoverBrute(Graph* graph) {
    int n = graph->numVertices;
    int vertices[MAX_VERTICES];
    bool currentSubset[MAX_VERTICES] = {false};
    bool bestSubset[MAX_VERTICES] = {false};
    bool found = false;
    int minSize = n + 1; // Initialize to an impossible value
    
    // Initialize the vertices array
    for (int i = 0; i < n; i++) {
        vertices[i] = i;
    }
    
    // Try all possible subset sizes from 1 to n
    for (int k = 1; k <= n && !found; k++) {
        generateSubsets(vertices, n, currentSubset, bestSubset, k, 0, graph, &found, &minSize);
        if (found) break; // We found a valid cover, no need to check larger sizes
    }
    
    // Print the minimum vertex cover
    if (found) {
        printf("Minimum Vertex Cover Size: %d\n", minSize);
        printf("Vertices in Minimum Cover: ");
        for (int i = 0; i < n; i++) {
            if (bestSubset[i]) {
                printf("%d ", i);
            }
        }
        printf("\n");
    } else {
        printf("No valid vertex cover found.\n");
    }
}

// Free the memory allocated for the graph
void freeGraph(Graph* graph) {
    free(graph);
}

// Function to test graph351
void testGraph351() {
    // Create a graph with 7 vertices (A through G, mapped as 0-6)
    Graph* graph = createGraph(7);
    
    // Add edges for graph351
    addEdge(graph, 0, 1); // A-B
    addEdge(graph, 1, 2); // B-C
    addEdge(graph, 2, 3); // C-D
    addEdge(graph, 2, 4); // C-E
    addEdge(graph, 3, 4); // D-E
    addEdge(graph, 3, 5); // D-F
    addEdge(graph, 3, 6); // D-G
    addEdge(graph, 4, 5); // E-F
    
    printf("Running brute force algorithm for minimum vertex cover on graph351...\n");
    vertexCoverBrute(graph);
    
    freeGraph(graph);
}

// Function to test graphConnected (complete graph with 7 vertices)
void testGraphConnected() {
    // Create a graph with 7 vertices (A through G, mapped as 0-6)
    Graph* graph = createGraph(7);
    
    // Add edges for graphConnected (complete graph)
    for (int i = 0; i < 7; i++) {
        for (int j = i + 1; j < 7; j++) {
            addEdge(graph, i, j);
        }
    }
    
    printf("Running brute force algorithm for minimum vertex cover on graphConnected...\n");
    vertexCoverBrute(graph);
    
    freeGraph(graph);
}

// Function to test graphBipartite
void testGraphBipartite() {
    // Create a graph with 10 vertices (A through J, mapped as 0-9)
    Graph* graph = createGraph(10);
    
    // Add edges for graphBipartite
    addEdge(graph, 0, 5); // A-F
    addEdge(graph, 0, 6); // A-G
    addEdge(graph, 1, 5); // B-F
    addEdge(graph, 2, 7); // C-H
    addEdge(graph, 2, 6); // C-G
    addEdge(graph, 3, 7); // D-H
    addEdge(graph, 3, 9); // D-J
    addEdge(graph, 4, 8); // E-I
    addEdge(graph, 4, 9); // E-J
    
    printf("Running brute force algorithm for minimum vertex cover on graphBipartite...\n");
    vertexCoverBrute(graph);
    
    freeGraph(graph);
}

// Function to test graphBig
void testGraphBig() {
    // Create a graph with 21 vertices (A through U, mapped as 0-20)
    Graph* graph = createGraph(21);
    
    // Map letters to indices: A=0, B=1, C=2, D=3, E=4, F=5, G=6, H=7, I=8, J=9,
    // K=10, L=11, M=12, N=13, O=14, P=15, Q=16, R=17, S=18, T=19, U=20
    
    // Add edges for graphBig
    // A's edges
    addEdge(graph, 0, 1);  // A-B
    addEdge(graph, 0, 4);  // A-E
    addEdge(graph, 0, 3);  // A-D
    
    // B's edges
    addEdge(graph, 1, 0);  // B-A
    addEdge(graph, 1, 4);  // B-E
    addEdge(graph, 1, 5);  // B-F
    addEdge(graph, 1, 2);  // B-C
    
    // C's edges
    addEdge(graph, 2, 1);  // C-B
    addEdge(graph, 2, 5);  // C-F
    
    // D's edges
    addEdge(graph, 3, 0);  // D-A
    addEdge(graph, 3, 4);  // D-E
    addEdge(graph, 3, 7);  // D-H
    addEdge(graph, 3, 6);  // D-G
    
    // E's edges
    addEdge(graph, 4, 3);  // E-D
    addEdge(graph, 4, 0);  // E-A
    addEdge(graph, 4, 1);  // E-B
    addEdge(graph, 4, 5);  // E-F
    addEdge(graph, 4, 8);  // E-I
    addEdge(graph, 4, 7);  // E-H
    
    // F's edges
    addEdge(graph, 5, 4);  // F-E
    addEdge(graph, 5, 1);  // F-B
    addEdge(graph, 5, 2);  // F-C
    addEdge(graph, 5, 8);  // F-I
    
    // G's edges
    addEdge(graph, 6, 3);  // G-D
    addEdge(graph, 6, 7);  // G-H
    addEdge(graph, 6, 10); // G-K
    addEdge(graph, 6, 9);  // G-J
    
    // H's edges
    addEdge(graph, 7, 6);  // H-G
    addEdge(graph, 7, 3);  // H-D
    addEdge(graph, 7, 4);  // H-E
    addEdge(graph, 7, 8);  // H-I
    addEdge(graph, 7, 11); // H-L
    addEdge(graph, 7, 10); // H-K
    
    // I's edges
    addEdge(graph, 8, 7);  // I-H
    addEdge(graph, 8, 4);  // I-E
    addEdge(graph, 8, 5);  // I-F
    addEdge(graph, 8, 11); // I-L
    
    // J's edges
    addEdge(graph, 9, 6);  // J-G
    addEdge(graph, 9, 10); // J-K
    addEdge(graph, 9, 13); // J-N
    addEdge(graph, 9, 12); // J-M
    
    // K's edges
    addEdge(graph, 10, 9);  // K-J
    addEdge(graph, 10, 6);  // K-G
    addEdge(graph, 10, 7);  // K-H
    addEdge(graph, 10, 11); // K-L
    addEdge(graph, 10, 14); // K-O
    addEdge(graph, 10, 13); // K-N
    
    // L's edges
    addEdge(graph, 11, 10); // L-K
    addEdge(graph, 11, 7);  // L-H
    addEdge(graph, 11, 8);  // L-I
    addEdge(graph, 11, 14); // L-O
    
    // M's edges
    addEdge(graph, 12, 9);  // M-J
    addEdge(graph, 12, 13); // M-N
    addEdge(graph, 12, 16); // M-Q
    addEdge(graph, 12, 15); // M-P
    
    // N's edges
    addEdge(graph, 13, 12); // N-M
    addEdge(graph, 13, 9);  // N-J
    addEdge(graph, 13, 10); // N-K
    addEdge(graph, 13, 14); // N-O
    addEdge(graph, 13, 17); // N-R
    addEdge(graph, 13, 16); // N-Q
    
    // O's edges
    addEdge(graph, 14, 13); // O-N
    addEdge(graph, 14, 10); // O-K
    addEdge(graph, 14, 11); // O-L
    addEdge(graph, 14, 17); // O-R
    
    // P's edges
    addEdge(graph, 15, 12); // P-M
    addEdge(graph, 15, 16); // P-Q
    addEdge(graph, 15, 19); // P-T
    addEdge(graph, 15, 18); // P-S
    
    // Q's edges
    addEdge(graph, 16, 15); // Q-P
    addEdge(graph, 16, 12); // Q-M
    addEdge(graph, 16, 13); // Q-N
    addEdge(graph, 16, 17); // Q-R
    addEdge(graph, 16, 20); // Q-U
    addEdge(graph, 16, 19); // Q-T
    
    // R's edges
    addEdge(graph, 17, 16); // R-Q
    addEdge(graph, 17, 13); // R-N
    addEdge(graph, 17, 14); // R-O
    addEdge(graph, 17, 20); // R-U
    
    // S's edges
    addEdge(graph, 18, 15); // S-P
    addEdge(graph, 18, 19); // S-T
    
    // T's edges
    addEdge(graph, 19, 18); // T-S
    addEdge(graph, 19, 15); // T-P
    addEdge(graph, 19, 16); // T-Q
    addEdge(graph, 19, 20); // T-U
    
    // U's edges
    addEdge(graph, 20, 19); // U-T
    addEdge(graph, 20, 16); // U-Q
    addEdge(graph, 20, 17); // U-R
    
    printf("Running brute force algorithm for minimum vertex cover on graphBig...\n");
    vertexCoverBrute(graph);
    
    freeGraph(graph);
}

// Function to time a graph test
double timeTest(void (*testFunction)()) {
    clock_t start, end;
    double cpuTimeUsed;
    
    start = clock();
    testFunction();
    end = clock();
    
    cpuTimeUsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    return cpuTimeUsed;
}

int main() {
    double timeUsed;
    
    printf("Testing graph351...\n");
    timeUsed = timeTest(testGraph351);
    printf("Time taken for graph351: %.6f seconds\n\n", timeUsed);
    
    printf("Testing graphConnected...\n");
    timeUsed = timeTest(testGraphConnected);
    printf("Time taken for graphConnected: %.6f seconds\n\n", timeUsed);
    
    printf("Testing graphBipartite...\n");
    timeUsed = timeTest(testGraphBipartite);
    printf("Time taken for graphBipartite: %.6f seconds\n\n", timeUsed);
    
    printf("Testing graphBig\n");
    timeUsed = timeTest(testGraphBig);
    printf("Time taken for graphBig: %.6f seconds\n", timeUsed);
    
    return 0;
}


// Reference
// https://github.com/sedgwickc/VertexCoverSearch/blob/main/VertexCover.py
// Asked Claude.ai to convert into C, hope that's okay