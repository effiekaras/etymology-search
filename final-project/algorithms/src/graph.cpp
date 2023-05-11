#include "../include/graph.h"
#include <iostream>
#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>
using std::ifstream;
using std::ofstream;
using std::string;

Graph::Graph(string edge_file_path, string node_file_path) {
    // add check for if nodes.txt and edges.txt exist
    //parser.Parse("../data/test-subset.csv"); // Replace with full dataset
    ifstream edge_file; edge_file.open(edge_file_path);
    ifstream node_file; node_file.open(node_file_path);

    // Add all nodes to adjacency list
    string lang,term,term_id; // term_id = lang+term
    while (std::getline(node_file, lang, ',') && std::getline(node_file, term,',') 
    && std::getline(node_file, term_id)) {
        if (lang+term == term_id) { // Check due to dataset bugs
            boost::to_lower(lang); boost::to_lower(term); boost::to_lower(term_id); // normalize lang, term, and id
            AdjacencyNode* node_ptr = new AdjacencyNode(lang, term);
            nodes_.insert(std::pair<string, AdjacencyNode*>(term_id, node_ptr));
            node_ids_.push_back(term_id);
            std::pair<vector<AdjacencyEdge*>, vector<AdjacencyEdge*>> pair = std::pair<vector<AdjacencyEdge*>, vector<AdjacencyEdge*>>(vector<AdjacencyEdge*>(), vector<AdjacencyEdge*>());
            adj_list_.insert(std::pair<AdjacencyNode*, std::pair<vector<AdjacencyEdge*>, vector<AdjacencyEdge*>>>(node_ptr, pair));
        }
    } 

    // Add edges to adjacency list
    string line;
    while (std::getline(edge_file, line)) {
        boost::to_lower(line);
        vector<string> result;
        boost::split(result, line, boost::is_any_of(","));
        if (result.size() < 5) {
            continue;
        }
        vector<string> relTypes;
        // result[0] - result[3] = rel_lang, rel_term, lang, term ... relTypes
        for (int i = 4; i < result.size(); ++i) {
            relTypes.push_back(result.at(i));
        }
        string rel_id = result.at(0) + result.at(1) + "";
        string id = result.at(2) + result.at(3) + "";
        // parent is related term, find from node map
        auto parent = nodes_.find(rel_id);
        auto child = nodes_.find(id);

        if (parent == nodes_.end()) {
            std::cout << "parent not found :(" << std::endl;
            std::cout << line << std::endl;
            std::cout << rel_id;
            return;
        } else if (child == nodes_.end()) {
            std::cout << "child not found :(" << std::endl;
            return;
        }
        insertEdge(parent->second, child->second, relTypes, true); // Adds child to children vector
        insertEdge(child->second, parent->second, relTypes, false); // Adds parent to parent vector
    }
}

void Graph::insertEdge(AdjacencyNode* parent, AdjacencyNode* child, vector<string> rel_types, bool isParentChildRel) {
    // Create an edge and add to the edge list mapped to the parent node
    if (adj_list_.find(parent) == adj_list_.end()) {
        insertNode(parent);
    } 
    if (adj_list_.find(child) == adj_list_.end()) {
        insertNode(child);
    } 
    AdjacencyEdge* new_edge = new AdjacencyEdge(parent, child, rel_types);
    if (isParentChildRel) {
        adj_list_[parent].second.push_back(new_edge);
    } else {
        adj_list_[parent].first.push_back(new_edge);
    }
}

void Graph::insertNode(AdjacencyNode* new_node_ptr) {
    string term_id = new_node_ptr->getLang() + new_node_ptr->getTerm();
    nodes_.insert(std::pair<string, AdjacencyNode*>(term_id, new_node_ptr));
    node_ids_.push_back(term_id);
    std::pair<vector<AdjacencyEdge*>, vector<AdjacencyEdge*>> pair = 
    std::pair<vector<AdjacencyEdge*>, vector<AdjacencyEdge*>>(vector<AdjacencyEdge*>(), vector<AdjacencyEdge*>());
    adj_list_.insert(std::pair<AdjacencyNode*, std::pair<vector<AdjacencyEdge*>, vector<AdjacencyEdge*>>>(new_node_ptr, pair));
}

std::vector<AdjacencyNode*> Graph::getAdjacentChildren(AdjacencyNode* vertex) {
    std::vector<AdjacencyNode*> adj_nodes;
    for (AdjacencyEdge* edge : adj_list_[vertex].second) {
        adj_nodes.push_back(edge->getChild());
    }
    return adj_nodes;
}

std::vector<AdjacencyNode*> Graph::getAdjacentParent(AdjacencyNode* vertex) {
    std::vector<AdjacencyNode*> adj_nodes;
    for (AdjacencyEdge* edge : adj_list_[vertex].first) {
        adj_nodes.push_back(edge->getChild());
    }
    return adj_nodes;
}

std::vector<AdjacencyNode*> Graph::getAdjacentNodes(AdjacencyNode* vertex) {
    std::vector<AdjacencyNode*> adj_nodes;
    for (AdjacencyEdge* edge : adj_list_[vertex].first) {
        adj_nodes.push_back(edge->getChild());
    }

    for (AdjacencyEdge* edge : adj_list_[vertex].second) {
        adj_nodes.push_back(edge->getChild());
    }

    return adj_nodes;
}

AdjacencyNode* Graph::getNode(string id){
    boost::to_lower(id);
    auto node = nodes_.find(id);
    if (node == nodes_.end()) {
        std::cout << "Node ID: " << id << " does not exist, returning nullptr." << std::endl;
        return nullptr;
    }

    return nodes_[id];
}

std::vector<AdjacencyEdge*> Graph::getAdjEdges(AdjacencyNode* vertex){
    return adj_list_[vertex].second; // For Children
}

string Graph::getNodeID(size_t i){
    if (i >= node_ids_.size()) {
        std::cout << "Index is out of bounds" << std::endl;
        return "";
    }
    return node_ids_[i];
}

size_t Graph::getNodeCount(){
    return node_ids_.size();
}

std::vector<string> Graph::getNodeIDs() {
    return node_ids_;
}