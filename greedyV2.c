#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct Edge {
    int u;
    int v;
} Edge;

typedef struct Graph {
    int numVertices;
    int numEdges;
    Edge* edges;
} Graph;

Graph* createGraph(int numVertices, int maxEdges) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->numEdges = 0;
    graph->edges = (Edge*)malloc(maxEdges * sizeof(Edge));
    if (graph->edges == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    return graph;
}

void addEdge(Graph* graph, int u, int v) {
    if (u >= 0 && u < graph->numVertices && v >= 0 && v < graph->numVertices) {
        graph->edges[graph->numEdges].u = u;
        graph->edges[graph->numEdges].v = v;
        graph->numEdges++;
    } else {
        printf("Invalid vertex indices: %d or %d\n", u, v);
    }
}

//edge is covered when atleast one vertex of the edge is in the cover
bool isEdgeCovered(Edge edge, bool* vertexCover) {
    return vertexCover[edge.u] || vertexCover[edge.v];
}

bool* greedyVertexCover(Graph* graph) {
    int numVertices = graph->numVertices;
    int numEdges = graph->numEdges;
    Edge* edges = graph->edges;

    bool* vertexCover = (bool*)calloc(numVertices, sizeof(bool));
    if (!vertexCover) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    bool* coveredEdges = (bool*)calloc(numEdges, sizeof(bool));
    if (!coveredEdges) {
        perror("Memory allocation failed");
        free(vertexCover);
        exit(EXIT_FAILURE);
    }

    int remainingEdges = numEdges;

    srand(time(NULL));

    while (remainingEdges > 0) {
        // Find the first uncovered edge
        int edgeIndex = -1;
        for (int i = 0; i < numEdges; i++) {
            if (!coveredEdges[i]) {
                edgeIndex = i;
                break;
            }
        }
        if (edgeIndex == -1) break; // All edges covered

        Edge edge = edges[edgeIndex];
        int u = edge.u;
        int v = edge.v;

        // Choose the vertex with higher degree (or any other heuristic)
        int degreeU = 0, degreeV = 0;
        for (int i = 0; i < numEdges; i++) {
            if (!coveredEdges[i]) {
                if (edges[i].u == u || edges[i].v == u) degreeU++;
                if (edges[i].u == v || edges[i].v == v) degreeV++;
            }
        }

        // Add the vertex that covers more uncovered edges
        int selected;
        if (degreeU == degreeV){
            //degrees are euqal, select one of the two vertices
            selected=(rand()%2)? u : v;
        }else{
            //otherwise select the vertez with higher degree
            selected=(degreeU >degreeV)? u:v;
        }
        vertexCover[selected] = true;

        // Mark all edges covered by 'selected' as covered
        for (int i = 0; i < numEdges; i++) {
            if (!coveredEdges[i] && (edges[i].u == selected || edges[i].v == selected)) {
                coveredEdges[i] = true;
                remainingEdges--;
            }
        }
    }

    free(coveredEdges);
    return vertexCover;
}

void freeGraph(Graph* graph) {
    free(graph->edges);
    free(graph);
}

//test cases are some as the ones in bruteforce
//inserted by gemini

void testGraph351() {
    // Create a graph with 7 vertices (A through G, mapped as 0-6)
    Graph* graph = createGraph(7, 9); // Max edges = 9
    addEdge(graph, 0, 1); // A-B
    addEdge(graph, 1, 2); // B-C
    addEdge(graph, 2, 3); // C-D
    addEdge(graph, 2, 4); // C-E
    addEdge(graph, 3, 4); // D-E
    addEdge(graph, 3, 5); // D-F
    addEdge(graph, 3, 6); // D-G
    addEdge(graph, 4, 5); // E-F

    printf("Running Greedy Algorithm for graph351...\n");
    bool* vertexCover = greedyVertexCover(graph);
    int size = 0;
    printf("Approximate Vertex Cover: ");
    for (int i = 0; i < graph->numVertices; i++) {
        if (vertexCover[i]) {
            printf("%d ", i);
            size++;
        }
    }
    printf("\n");
    printf("Size: %d\n", size);
    freeGraph(graph);
    free(vertexCover);
}

void testGraphConnected() {
    // Create a graph with 7 vertices (A through G, mapped as 0-6)
    Graph* graph = createGraph(7, 21); // Max edges = 7*6/2 = 21
    for (int i = 0; i < 7; i++) {
        for (int j = i + 1; j < 7; j++) {
            addEdge(graph, i, j);
        }
    }

    printf("Running Greedy Algorithm for graphConnected...\n");
    bool* vertexCover = greedyVertexCover(graph);
    int size = 0;
    printf("Approximate Vertex Cover: ");
    for (int i = 0; i < graph->numVertices; i++) {
        if (vertexCover[i]) {
            printf("%d ", i);
            size++;
        }
    }
    printf("\n");
    printf("Size: %d\n", size);
    freeGraph(graph);
    free(vertexCover);
}

void testGraphBipartite() {
    // Create a graph with 10 vertices (A through J, mapped as 0-9)
    Graph* graph = createGraph(10, 9); // Max Edges = 9
    addEdge(graph, 0, 5); // A-F
    addEdge(graph, 0, 6); // A-G
    addEdge(graph, 1, 5); // B-F
    addEdge(graph, 2, 7); // C-H
    addEdge(graph, 2, 6); // C-G
    addEdge(graph, 3, 7); // D-H
    addEdge(graph, 3, 9); // D-J
    addEdge(graph, 4, 8); // E-I
    addEdge(graph, 4, 9); // E-J

    printf("Running Greedy Algorithm for graphBipartite...\n");
    bool* vertexCover = greedyVertexCover(graph);
    int size = 0;
    printf("Approximate Vertex Cover: ");
    for (int i = 0; i < graph->numVertices; i++) {
        if (vertexCover[i]) {
            printf("%d ", i);
            size++;
        }
    }
    printf("\n");
    printf("Size: %d\n", size);
    freeGraph(graph);
    free(vertexCover);
}

void testGraphBig() {
    // Create a graph with 21 vertices (A through U, mapped as 0-20)
    Graph* graph = createGraph(21, 88); // Max Edges = 42
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

    printf("Running Greedy Algorithm for graphBig...\n");
    bool* vertexCover = greedyVertexCover(graph);
    int size = 0;
    printf("Approximate Vertex Cover: ");
    for (int i = 0; i < graph->numVertices; i++) {
        if (vertexCover[i]) {
            printf("%d ", i);
            size++;
        }
    }
    printf("\n");
    printf("Size: %d\n", size);
    freeGraph(graph);
    free(vertexCover);
}

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
