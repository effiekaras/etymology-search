#include "../include/graph.h"
#include "../include/IDDFS.h"
#include <boost/algorithm/string.hpp>
using std::ifstream;
using std::ofstream;
using std::string;
#include <iostream>
#include <bits/stdc++.h>

bool IDDFS::search(string filename, string start_id, string target_id, int depth) {
    boost::algorithm::trim(start_id); boost::algorithm::trim(target_id);
    ofstream dfs_file_; dfs_file_.open(filename);
    AdjacencyNode* start = graph_.getNode(start_id);
    AdjacencyNode* target = graph_.getNode(target_id);
    if (start == nullptr) {
        std::cout << "Invalid start ID: " << start_id << std::endl;
        return false;
    } else if (target == nullptr) {
        std::cout << "Invalid target ID: " << target_id << std::endl;
        return false;
    }
    if (start_id == target_id) {
        return true;
    }
    if (depth <= 0) {
        return false;
    }

    for (int i = 0; i < depth; i++) {

        dfs_file_ << "Starting depth " << i << std::endl;
        if (search(start, target, i, dfs_file_)) {
            std::cout << target_id << " found at depth " << i << std::endl;
            return true;
        }
    }
    std::cout << start_id << " is not related to " << target_id << " within depth " << depth << std::endl;
    return false;
}

bool IDDFS::search(AdjacencyNode* start, AdjacencyNode* target, int depth, ofstream& dfs_file){
    dfs_file << start->getLang() << "," << start->getTerm() << std::endl;
    recent_ = start;
    if (start == target) {
        return true;
    }

    if (depth <= 0){
        return false;
    }
    
    std::vector<AdjacencyNode*> adjacent = graph_.getAdjacentNodes(start);
    for(size_t i = 0; i < adjacent.size(); i++){
        if (search(adjacent[i], target, depth - 1, dfs_file)) {
            return true;
        }
    }
    return false;
}