#include "../include/drawing.h"
#include <iostream>
using std::ofstream;
using std::map;
using std::string;

void Drawing::printDataset(string filename) {
    // For each node in dataset
    // If node has no children and no parents, skip this node
    // If node has no children, only print parent graph
    // If node has no parents, only print child graph
    // If node has parents and children, print both graph
    auto node_ids = graph_.getNodeIDs();
    for (string id : node_ids) {
        AdjacencyNode* curr_node = graph_.getNode(id);
        auto children = graph_.getAdjacentChildren(curr_node);
        if (children.empty()) {
            drawRelated(id, filename, true, false);
        }
    }
}

void Drawing::drawRelated(string term_id, std::string filename, bool shouldDrawParents, bool new_file) {
    AdjacencyNode* node = graph_.getNode(term_id);
    if (node == nullptr) {
        std::cout << "Invalid node ID: " << term_id << std::endl;
        return;
    }
    clear();
    node_layers_[node] = 0;
    layer_indices_[0] = 0;
    vector<string> startterm;
    startterm.push_back(node->getTerm());
    output_.push_back(startterm);
    if (shouldDrawParents) {
        vector<AdjacencyNode*> parents = graph_.getAdjacentParent(node); //draw all parent layers
        for(int i = 0; i < parents.size(); i++){
            drawParents(parents[i], -1, 0);
        }
    } else {
        vector<AdjacencyNode*> children = graph_.getAdjacentChildren(node); // draw all children layers
        for (int i = 0; i < children.size(); i++) {
            drawChildren(children[i], -1, 0);
        }
    }
    line_ = 0; //reset line
    adjustLines();
    printOutput(filename, new_file);
}

std::size_t strlen_utf8(const std::string& str) {
	std::size_t length = 0;
	for (char c : str) {
		if ((c & 0xC0) != 0x80) {
			++length;
		}
	}
	return length;
}

void Drawing::drawParents(AdjacencyNode* node, int layer, int prevLine) {
    if (node == nullptr) {
        return;
    }
    if (node_layers_.find(node) != node_layers_.end() && node_layers_[node] != layer) { //if node exists on other layer, skip
        return;
    }
    node_layers_[node] = layer; //mark node as existing on this layer
    std::string word = node->getTerm();   
    if (layer_line_sizes_.find(layer) != layer_line_sizes_.end())  { //checks if layer exists
        if (strlen_utf8(word) > layer_line_sizes_[layer]) { //update layer line size
            layer_line_sizes_[layer] = strlen_utf8(word);
        }
        if (output_[layer_indices_[layer]].size() < line_ + 1) {  //add space to vector for new line
            output_[layer_indices_[layer]].resize(line_ + 1);
            output_[layer_indices_[layer] + 1].resize(line_ + 1);
        }
        output_[layer_indices_[layer]][line_] = word; //write word to correct location in output
        if (line_ == prevLine) { //draw correct arrow head for line
            output_[layer_indices_[layer] + 1][line_] = ">";
        } else {
            output_[layer_indices_[layer] + 1][line_] = "|";
        }
    } else { //create new layer if layer does not exist    
        for (int i = layer_min_; i <= layer_max_; i++) { // update all layer indices
            layer_indices_[i] += 2;
        }
        layer_min_ = layer;
        layer_indices_[layer] = 0; //add new layer to front
        layer_line_sizes_[layer] = strlen_utf8(word);

        std::vector<std::string> newcol; //create new vector to add as new column
        newcol.resize(line_ + 1);
        if (line_ == prevLine) { //draw correct arrow head to new column
            newcol.at(line_) = ">";
        } else {
            newcol.at(line_) = "|";
        }
        output_.insert(output_.begin(), newcol); //add new column to fornt of output
        newcol.clear(); //clear new column
        newcol.resize(line_ + 1);
        newcol.at(line_) = word; //add word to new column
        output_.insert(output_.begin(), newcol); //add new column to front of output
    }
    
    vector<AdjacencyNode*> parents = graph_.getAdjacentParent(node);
    int line = line_;
    if (parents.empty()) {
        line_++;
        return;
    } //tracks line of current node for recursive calls
    for (int i = 0; i < parents.size(); i++) {//recurse over all parents
        drawParents(parents.at(i), layer - 1, line);
    }
}

void Drawing::drawChildren(AdjacencyNode* node, int layer, int prevLine) {
    if (node == nullptr) {
        return;
    }
    if (node_layers_.find(node) != node_layers_.end() && node_layers_[node] != layer) { //if node exists on other layer, skip
        return;
    }
    node_layers_[node] = layer; //mark node as existing on this layer
    std::string word = node->getTerm();   
    if (layer_line_sizes_.find(layer) != layer_line_sizes_.end())  { //checks if layer exists
        if (strlen_utf8(word) > layer_line_sizes_[layer]) { //update layer line size
            layer_line_sizes_[layer] = strlen_utf8(word);
        }
        if (output_[layer_indices_[layer]].size() < line_ + 1) {  //add space to vector for new line
            output_[layer_indices_[layer]].resize(line_ + 1);
            output_[layer_indices_[layer] + 1].resize(line_ + 1);
        }
        output_[layer_indices_[layer]][line_] = word; //write word to correct location in output
        if (line_ == prevLine) { //draw correct arrow head for line
            output_[layer_indices_[layer] + 1][line_] = "<";
        } else {
            output_[layer_indices_[layer] + 1][line_] = "|";
        }
    } else { //create new layer if layer does not exist    
        for (int i = layer_min_; i <= layer_max_; i++) { // update all layer indices
            layer_indices_[i] += 2;
        }
        layer_min_ = layer;
        layer_indices_[layer] = 0; //add new layer to front
        layer_line_sizes_[layer] = strlen_utf8(word);

        std::vector<std::string> newcol; //create new vector to add as new column
        newcol.resize(line_ + 1);
        if (line_ == prevLine) { //draw correct arrow head to new column
            newcol.at(line_) = "<";
        } else {
            newcol.at(line_) = "|";
        }
        output_.insert(output_.begin(), newcol); //add new column to fornt of output
        newcol.clear(); //clear new column
        newcol.resize(line_ + 1);
        newcol.at(line_) = word; //add word to new column
        output_.insert(output_.begin(), newcol); //add new column to front of output
    }
    
    vector<AdjacencyNode*> children = graph_.getAdjacentChildren(node);
    int line = line_;
    if (children.empty()) {
        line_++;
        return;
    } //tracks line of current node for recursive calls
    for (int i = 0; i < children.size(); i++) {//recurse over all children
        drawChildren(children.at(i), layer - 1, line);
    }
}

void Drawing::adjustLines() {
    for (int i = layer_min_; i <= layer_max_; i++) { //loop over all layers
        if (output_[layer_indices_[i]].size() > layer_size_) {
            layer_size_ = output_[layer_indices_[i]].size();
        }
        for (size_t j = 0; j < output_[layer_indices_[i]].size(); j++) { //loop over each layer's word vector
            if (output_[layer_indices_[i]][j].empty()) { //add appropriate blank space to all empty cells for word size AND arrow head
                while (strlen_utf8(output_[layer_indices_[i]][j]) <= layer_line_sizes_[i]) {
                    output_[layer_indices_[i]][j].push_back(' ');
                }
            }
            else{
                while (strlen_utf8(output_[layer_indices_[i]][j]) <= layer_line_sizes_[i]) { //add arrow segments to all words
                    output_[layer_indices_[i]][j].push_back('-');
                }
            }
        }
    }
    
    for(size_t i = 0; i < output_.size(); i++){
        if (output_[i].size() < layer_size_) {
            output_[i].resize(layer_size_);
        }

        for (size_t j = 0; j < output_[i].size(); j++){
            if (i % 2 == 0){
                if (output_[i][j].size() == 0){
                    while (strlen_utf8(output_[i][j]) <= layer_line_sizes_[layer_min_ + static_cast<int>(2*i)]) {
                        output_[i][j].push_back(' ');
                    }
                }
            }
            else {
                if (output_[i][j].size() == 0) {
                    output_[i][j] = ' ';
                }
            }
        }
    }
}

void Drawing::printOutput(string filename, bool new_file) {
    ofstream outfile; 
    if (new_file) {
        outfile.open(filename);
    } else {
        outfile.open(filename, std::ios_base::app);
    }
    for (int j = 0; j < layer_size_; ++j) {
        for (int i = 0; i < output_.size(); ++i) {
            if (j < output_[i].size()) {
                outfile << output_[i][j];
            }
        }
        outfile << std::endl;
    }
    if (!new_file) {
        outfile << std::endl;
    }
}

void Drawing::clear() {
    line_ = 0;
    layer_min_ = 0;
    layer_max_ = 0;
    layer_size_ = 0;
    output_.clear();
    node_layers_.clear();
    layer_line_sizes_.clear();
    layer_indices_.clear();
}