#include "../include/DFS.h"
#include "../include/graph.h"
using std::ifstream;
using std::ofstream;
using std::string;
#include <iostream>
#include <bits/stdc++.h>

void DFS::search(string filename) {
    ofstream dfs_file_; dfs_file_.open(filename);
    // On calling DFS, load map of vertices to UNEXPLORED vertices and edges
    node_labels_.clear();
    edge_labels_.clear();
    
    for (size_t i = 0; i < graph_.getNodeCount(); ++i) {
        AdjacencyNode* curr_node = graph_.getNode(graph_.getNodeID(i));
        // Load/set node labels to be unexplored
        node_labels_.insert(std::pair<AdjacencyNode*, Label>(curr_node, Label::UNEXPLORED));
        std::vector<Label> curr_edges_;
        for (size_t j = 0; j < graph_.getAdjEdges(curr_node).size(); ++j) {
            curr_edges_.push_back(Label::UNEXPLORED);
        }
        // Load/set edge labels to be unexplored
        edge_labels_.insert(std::pair<AdjacencyNode*, std::vector<Label>>(curr_node, curr_edges_));
    }
    for (size_t i = 0; i < graph_.getNodeCount(); ++i) {
        AdjacencyNode* curr_node = graph_.getNode(graph_.getNodeID(i));
        if (getLabel(curr_node) == Label::UNEXPLORED) {
            search(curr_node, dfs_file_);
        }
    }
}

void DFS::search(AdjacencyNode* vertex, ofstream& dfs_file) {
    dfs_file << vertex->getLang() << "," << vertex->getTerm() << std::endl;
    setLabel(vertex, Label::VISITED);
    for (AdjacencyNode* adj_vertex : graph_.getAdjacentChildren(vertex)) {
        if (getLabel(adj_vertex) == Label::UNEXPLORED) {
            setLabel(vertex, adj_vertex, Label::DISCOVERY);
            search(adj_vertex, dfs_file);
        } else if (getLabel(vertex, adj_vertex) == Label::UNEXPLORED) { // Edge is new
            setLabel(vertex, adj_vertex, Label::BACK);
        }
    }
}

Label DFS::getLabel(AdjacencyNode* vertex) {
    return node_labels_[vertex];
}

Label DFS::getLabel(AdjacencyNode* parent, AdjacencyNode* child) {
    vector<AdjacencyEdge*> edges = graph_.getAdjEdges(parent);
    // Determine which index our child is relative to the vector of edges, so we can find the label in the label vertex
    size_t index = -1;
    for (size_t i = 0; i < edges.size(); ++i) {
        if (child == edges.at(i)->getChild()) {
            index = i;
        }
    }
    // We always expect the child to be found, in the set of edges
    if (index == -1) {
        std::cout << "Error: child not found in edges, BUG" << std::endl;
    }
    return edge_labels_[parent].at(index);
}

void DFS::setLabel(AdjacencyNode* vertex, Label label) {
    node_labels_[vertex] = label;
}

void DFS::setLabel(AdjacencyNode* parent, AdjacencyNode* child, Label label) {
    vector<AdjacencyEdge*> edges = graph_.getAdjEdges(parent);
    size_t index = -1;
    for (size_t i = 0; i < edges.size(); ++i) {
        edges.at(0);
        if (child == edges.at(i)->getChild()) {
            index = i;
        }
    }
    if (index == -1) {
        std::cout << "Error: child not found in edges, BUG" << std::endl;
    }
    edge_labels_[parent].at(index) = label;
}

// Useful for testing
std::unordered_map<AdjacencyNode*, Label> DFS::getAllNodeLabels() {
    return node_labels_;
}

// Useful for testing
std::unordered_map<AdjacencyNode*, vector<Label>> DFS::getAllEdgeLabels() {
    return edge_labels_;
}