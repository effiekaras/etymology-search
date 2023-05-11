#pragma once
#include "adjacencynode.h"
#include <vector>
using std::vector;

class AdjacencyEdge {
    public:
        AdjacencyEdge(AdjacencyNode* p, AdjacencyNode* c, vector<string> rel);
        AdjacencyNode* getChild();
    private:
        AdjacencyNode* parent;
		AdjacencyNode* child;
		vector<string> rel_type;
		bool is_parent;
};