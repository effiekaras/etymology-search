#pragma once   
#include "graph.h"
#include "adjacencyedge.h"
#include "adjacencynode.h"

class IDDFS{
    public:
        IDDFS(Graph graph): graph_(graph) {};
        bool search(string filename, string start_id, string target_id, int depth); //IDDFS
    private:
        bool search(AdjacencyNode* start, AdjacencyNode* target, int depth, ofstream& dfs_file); //recursive Depth Limited Search
        Graph graph_;
        AdjacencyNode* recent_ = nullptr;
        AdjacencyNode* previous_ = nullptr;
};