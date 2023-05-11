#pragma once   
#include "graph.h"
#include <map>
#include "adjacencyedge.h"
#include "adjacencynode.h"
#include <stack>
#include <fstream>
#include <sstream>

class Drawing{
    public:
        Drawing(Graph graph): graph_(graph) {};
        /*
         If drawParents == true, then parents are drawn. Else, children tree is drawn.
        */
        void drawRelated(string term_id, std::string filename, bool shouldDrawParents, bool new_file = true); 
        void printDataset(string outfile);
    private:
        void drawParents(AdjacencyNode* node, int layer, int prevLine); //recursively draw all parents of node to output vector
        void drawChildren(AdjacencyNode* node, int layer, int prevLine); //recursively draw all children of node to output vector
        void clear(); //initialize/empty all tracking variables
        void adjustLines(); //draw arrow segments and blank space to make output line up visually
        void printOutput(string filename, bool newFile = true);

        Graph graph_;
        std::vector<std::vector<std::string>> output_; //output string map to be printed
        std::unordered_map<AdjacencyNode*, int> node_layers_; //track which layer each node is in to avoid cycles
        std::map<int, unsigned> layer_line_sizes_; //track the max length of a string in each layer
        std::map<int, int> layer_indices_; //track the index of each layer in the output vector (possibly unnecessary)
        int layer_min_; //lowest layer
        int layer_max_; //highest layer
        int line_; //track the current line being written to
        unsigned layer_size_; //track length of largest layer
};