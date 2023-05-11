#include "../include/adjacencyedge.h"

AdjacencyEdge::AdjacencyEdge(AdjacencyNode* p, AdjacencyNode* c, vector<string> rel) :
    parent(p), child(c), rel_type(rel) {
}

AdjacencyNode* AdjacencyEdge::getChild() {
    return child;
}

