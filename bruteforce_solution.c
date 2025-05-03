#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

int main() {
    // Create a sample graph
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
    
    printf("Running brute force algorithm for minimum vertex cover...\n");
    vertex_cover_brute(graph);
    
    free_graph(graph);
    return 0;
}


// Reference
// https://github.com/sedgwickc/VertexCoverSearch/blob/main/VertexCover.py
// Asked Claude.ai to convert into C, hope that's okay