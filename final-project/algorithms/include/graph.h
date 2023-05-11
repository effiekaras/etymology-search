#pragma once
//#include "../parsing/include/parser.h"
#include "adjacencyedge.h"
#include "adjacencynode.h"
#include <unordered_map>
#include <vector>
using std::vector;
using std::string;
using std::ofstream;
enum Label {
	UNEXPLORED,
	VISITED,
	DISCOVERY,
	BACK
};

class Graph {
	public:
		Graph(string edge_file_path = "../parsing/data/edges.txt", string node_file_path = "../parsing/data/nodes.txt");
		AdjacencyNode* getNode(string id);
		std::vector<AdjacencyNode*> getAdjacentChildren(AdjacencyNode* vertex);
		std::vector<AdjacencyNode*> getAdjacentParent(AdjacencyNode* vertex);
		std::vector<AdjacencyNode*> getAdjacentNodes(AdjacencyNode* vertex);
		std::vector<AdjacencyEdge*> getAdjEdges(AdjacencyNode* vertex);
		string getNodeID(size_t i);
		size_t getNodeCount();
		std::vector<string> getNodeIDs();
	
	private:
		void insertNode(AdjacencyNode* new_node);
		void insertEdge(AdjacencyNode* parent, AdjacencyNode* child, vector<string> rel_types, bool isParentChildRel);

		// mapping id to node pointer
		std::unordered_map<string, AdjacencyNode*> nodes_;
		// mapping each node to the list of edges coming out of that node
		std::unordered_map<AdjacencyNode*, std::pair<vector<AdjacencyEdge*>, vector<AdjacencyEdge*>>> adj_list_; // pair holds <parent> <children>
		std::vector<string> node_ids_;	
};