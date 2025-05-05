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
    int num_vertices;
    int num_edges;
    Edge edges[MAX_EDGES];
} Graph;

// Function to create a graph
Graph* create_graph(int num_vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->num_vertices = num_vertices;
    graph->num_edges = 0;
    return graph;
}

// Function to add an edge to the graph
void add_edge(Graph* graph, int u, int v) {
    graph->edges[graph->num_edges].u = u;
    graph->edges[graph->num_edges].v = v;
    graph->num_edges++;
}

// Function to verify if a subset of vertices forms a valid vertex cover
bool verify_vertex_cover(bool* cover, Graph* graph) {
    // Check that at least one vertex from each edge appears in the cover
    for (int i = 0; i < graph->num_edges; i++) {
        Edge edge = graph->edges[i];
        if (!cover[edge.u] && !cover[edge.v]) {
            return false; // This edge is not covered
        }
    }
    return true; // All edges are covered
}

// Function to generate all subsets of size k using backtracking
void generate_subsets(int* vertices, int n, bool* current_subset, bool* best_subset, 
                      int k, int start, Graph* graph, bool* found, int* min_size) {
    // If we've selected k vertices, check if they form a valid cover
    if (k == 0) {
        if (verify_vertex_cover(current_subset, graph)) {
            // Count the number of vertices in the current subset
            int size = 0;
            for (int i = 0; i < n; i++) {
                if (current_subset[i]) size++;
            }
            
            // Update the best cover if this is smaller
            if (!*found || size < *min_size) {
                *min_size = size;
                *found = true;
                memcpy(best_subset, current_subset, n * sizeof(bool));
            }
        }
        return;
    }
    
    // If we have no more vertices to consider, return
    if (start >= n) {
        return;
    }
    
    // Include the current vertex in the subset
    current_subset[start] = true;
    generate_subsets(vertices, n, current_subset, best_subset, k - 1, start + 1, graph, found, min_size);
    
    // Exclude the current vertex from the subset
    current_subset[start] = false;
    generate_subsets(vertices, n, current_subset, best_subset, k, start + 1, graph, found, min_size);
}

// Function to find the minimum vertex cover using brute force
void vertex_cover_brute(Graph* graph) {
    int n = graph->num_vertices;
    int vertices[MAX_VERTICES];
    bool current_subset[MAX_VERTICES] = {false};
    bool best_subset[MAX_VERTICES] = {false};
    bool found = false;
    int min_size = n + 1; // Initialize to an impossible value
    
    // Initialize the vertices array
    for (int i = 0; i < n; i++) {
        vertices[i] = i;
    }
    
    // Try all possible subset sizes from 1 to n
    for (int k = 1; k <= n && !found; k++) {
        generate_subsets(vertices, n, current_subset, best_subset, k, 0, graph, &found, &min_size);
        if (found) break; // We found a valid cover, no need to check larger sizes
    }
    
    // Print the minimum vertex cover
    if (found) {
        printf("Minimum Vertex Cover Size: %d\n", min_size);
        printf("Vertices in Minimum Cover: ");
        for (int i = 0; i < n; i++) {
            if (best_subset[i]) {
                printf("%d ", i);
            }
        }
        printf("\n");
    } else {
        printf("No valid vertex cover found.\n");
    }
}

// Free the memory allocated for the graph
void free_graph(Graph* graph) {
    free(graph);
}

// Function to test graph351
void test_graph351() {
    // Create a graph with 7 vertices (A through G, mapped as 0-6)
    Graph* graph = create_graph(7);
    
    // Add edges for graph351
    add_edge(graph, 0, 1); // A-B
    add_edge(graph, 1, 2); // B-C
    add_edge(graph, 2, 3); // C-D
    add_edge(graph, 2, 4); // C-E
    add_edge(graph, 3, 4); // D-E
    add_edge(graph, 3, 5); // D-F
    add_edge(graph, 3, 6); // D-G
    add_edge(graph, 4, 5); // E-F
    
    printf("Running brute force algorithm for minimum vertex cover on graph351...\n");
    vertex_cover_brute(graph);
    
    free_graph(graph);
}

// Function to test graphConnected (complete graph with 7 vertices)
void test_graphConnected() {
    // Create a graph with 7 vertices (A through G, mapped as 0-6)
    Graph* graph = create_graph(7);
    
    // Add edges for graphConnected (complete graph)
    for (int i = 0; i < 7; i++) {
        for (int j = i + 1; j < 7; j++) {
            add_edge(graph, i, j);
        }
    }
    
    printf("Running brute force algorithm for minimum vertex cover on graphConnected...\n");
    vertex_cover_brute(graph);
    
    free_graph(graph);
}

// Function to test graphBipartite
void test_graphBipartite() {
    // Create a graph with 10 vertices (A through J, mapped as 0-9)
    Graph* graph = create_graph(10);
    
    // Add edges for graphBipartite
    add_edge(graph, 0, 5); // A-F
    add_edge(graph, 0, 6); // A-G
    add_edge(graph, 1, 5); // B-F
    add_edge(graph, 2, 7); // C-H
    add_edge(graph, 2, 6); // C-G
    add_edge(graph, 3, 7); // D-H
    add_edge(graph, 3, 9); // D-J
    add_edge(graph, 4, 8); // E-I
    add_edge(graph, 4, 9); // E-J
    
    printf("Running brute force algorithm for minimum vertex cover on graphBipartite...\n");
    vertex_cover_brute(graph);
    
    free_graph(graph);
}

// Function to test graphBig
void test_graphBig() {
    // Create a graph with 21 vertices (A through U, mapped as 0-20)
    Graph* graph = create_graph(21);
    
    // Map letters to indices: A=0, B=1, C=2, D=3, E=4, F=5, G=6, H=7, I=8, J=9,
    // K=10, L=11, M=12, N=13, O=14, P=15, Q=16, R=17, S=18, T=19, U=20
    
    // Add edges for graphBig
    // A's edges
    add_edge(graph, 0, 1);  // A-B
    add_edge(graph, 0, 4);  // A-E
    add_edge(graph, 0, 3);  // A-D
    
    // B's edges
    add_edge(graph, 1, 0);  // B-A
    add_edge(graph, 1, 4);  // B-E
    add_edge(graph, 1, 5);  // B-F
    add_edge(graph, 1, 2);  // B-C
    
    // C's edges
    add_edge(graph, 2, 1);  // C-B
    add_edge(graph, 2, 5);  // C-F
    
    // D's edges
    add_edge(graph, 3, 0);  // D-A
    add_edge(graph, 3, 4);  // D-E
    add_edge(graph, 3, 7);  // D-H
    add_edge(graph, 3, 6);  // D-G
    
    // E's edges
    add_edge(graph, 4, 3);  // E-D
    add_edge(graph, 4, 0);  // E-A
    add_edge(graph, 4, 1);  // E-B
    add_edge(graph, 4, 5);  // E-F
    add_edge(graph, 4, 8);  // E-I
    add_edge(graph, 4, 7);  // E-H
    
    // F's edges
    add_edge(graph, 5, 4);  // F-E
    add_edge(graph, 5, 1);  // F-B
    add_edge(graph, 5, 2);  // F-C
    add_edge(graph, 5, 8);  // F-I
    
    // G's edges
    add_edge(graph, 6, 3);  // G-D
    add_edge(graph, 6, 7);  // G-H
    add_edge(graph, 6, 10); // G-K
    add_edge(graph, 6, 9);  // G-J
    
    // H's edges
    add_edge(graph, 7, 6);  // H-G
    add_edge(graph, 7, 3);  // H-D
    add_edge(graph, 7, 4);  // H-E
    add_edge(graph, 7, 8);  // H-I
    add_edge(graph, 7, 11); // H-L
    add_edge(graph, 7, 10); // H-K
    
    // I's edges
    add_edge(graph, 8, 7);  // I-H
    add_edge(graph, 8, 4);  // I-E
    add_edge(graph, 8, 5);  // I-F
    add_edge(graph, 8, 11); // I-L
    
    // J's edges
    add_edge(graph, 9, 6);  // J-G
    add_edge(graph, 9, 10); // J-K
    add_edge(graph, 9, 13); // J-N
    add_edge(graph, 9, 12); // J-M
    
    // K's edges
    add_edge(graph, 10, 9);  // K-J
    add_edge(graph, 10, 6);  // K-G
    add_edge(graph, 10, 7);  // K-H
    add_edge(graph, 10, 11); // K-L
    add_edge(graph, 10, 14); // K-O
    add_edge(graph, 10, 13); // K-N
    
    // L's edges
    add_edge(graph, 11, 10); // L-K
    add_edge(graph, 11, 7);  // L-H
    add_edge(graph, 11, 8);  // L-I
    add_edge(graph, 11, 14); // L-O
    
    // M's edges
    add_edge(graph, 12, 9);  // M-J
    add_edge(graph, 12, 13); // M-N
    add_edge(graph, 12, 16); // M-Q
    add_edge(graph, 12, 15); // M-P
    
    // N's edges
    add_edge(graph, 13, 12); // N-M
    add_edge(graph, 13, 9);  // N-J
    add_edge(graph, 13, 10); // N-K
    add_edge(graph, 13, 14); // N-O
    add_edge(graph, 13, 17); // N-R
    add_edge(graph, 13, 16); // N-Q
    
    // O's edges
    add_edge(graph, 14, 13); // O-N
    add_edge(graph, 14, 10); // O-K
    add_edge(graph, 14, 11); // O-L
    add_edge(graph, 14, 17); // O-R
    
    // P's edges
    add_edge(graph, 15, 12); // P-M
    add_edge(graph, 15, 16); // P-Q
    add_edge(graph, 15, 19); // P-T
    add_edge(graph, 15, 18); // P-S
    
    // Q's edges
    add_edge(graph, 16, 15); // Q-P
    add_edge(graph, 16, 12); // Q-M
    add_edge(graph, 16, 13); // Q-N
    add_edge(graph, 16, 17); // Q-R
    add_edge(graph, 16, 20); // Q-U
    add_edge(graph, 16, 19); // Q-T
    
    // R's edges
    add_edge(graph, 17, 16); // R-Q
    add_edge(graph, 17, 13); // R-N
    add_edge(graph, 17, 14); // R-O
    add_edge(graph, 17, 20); // R-U
    
    // S's edges
    add_edge(graph, 18, 15); // S-P
    add_edge(graph, 18, 19); // S-T
    
    // T's edges
    add_edge(graph, 19, 18); // T-S
    add_edge(graph, 19, 15); // T-P
    add_edge(graph, 19, 16); // T-Q
    add_edge(graph, 19, 20); // T-U
    
    // U's edges
    add_edge(graph, 20, 19); // U-T
    add_edge(graph, 20, 16); // U-Q
    add_edge(graph, 20, 17); // U-R
    
    printf("Running brute force algorithm for minimum vertex cover on graphBig...\n");
    vertex_cover_brute(graph);
    
    free_graph(graph);
}

// Function to time a graph test
double time_test(void (*test_function)()) {
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    test_function();
    end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}

int main() {
    double time_used;
    
    printf("Testing graph351...\n");
    time_used = time_test(test_graph351);
    printf("Time taken for graph351: %.6f seconds\n\n", time_used);
    
    printf("Testing graphConnected...\n");
    time_used = time_test(test_graphConnected);
    printf("Time taken for graphConnected: %.6f seconds\n\n", time_used);
    
    printf("Testing graphBipartite...\n");
    time_used = time_test(test_graphBipartite);
    printf("Time taken for graphBipartite: %.6f seconds\n\n", time_used);
    
    printf("Testing graphBig\n");
    time_used = time_test(test_graphBig);
    printf("Time taken for graphBig: %.6f seconds\n", time_used);
    
    return 0;
}


// Reference
// https://github.com/sedgwickc/VertexCoverSearch/blob/main/VertexCover.py
// Asked Claude.ai to convert into C, hope that's okay