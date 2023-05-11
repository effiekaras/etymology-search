#pragma once
#include "adjacencyedge.h"
#include "adjacencynode.h"
#include "graph.h"

class DFS{
    public:
        DFS(Graph graph): graph_(graph) {};
        void search(string filename = "dfs-traversal.txt");
    private:
		void search(AdjacencyNode* vertex, std::ofstream& dfs_file);
        Label getLabel(AdjacencyNode* vertex); // Gets Label for vertex
		Label getLabel(AdjacencyNode* parent, AdjacencyNode* child); // Gets Label for Edge
		void setLabel(AdjacencyNode* vertex, Label label);
		void setLabel(AdjacencyNode* parent, AdjacencyNode* child, Label label);
        std::unordered_map<AdjacencyNode*, Label> getAllNodeLabels();
		std::unordered_map<AdjacencyNode*, vector<Label>> getAllEdgeLabels();

        Graph graph_;
        std::unordered_map<AdjacencyNode*, Label> node_labels_;
		std::unordered_map<AdjacencyNode*, vector<Label>> edge_labels_;
};