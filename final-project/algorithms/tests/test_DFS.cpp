#include "catch2/catch.hpp"
#include "../include/adjacencyedge.h"
#include "../include/adjacencynode.h"
#include "../include/DFS.h"
#include "../include/graph.h"
#include <fstream>
using std::ifstream;

Graph graph_dfs("../algorithms/tests/edges_subset.txt", "../algorithms/tests/nodes_subset.txt");
DFS dfs(graph_dfs);
string dfs_output_file_path = "../algorithms/tests/dfs_output_test.txt";

TEST_CASE("DFS visits all points in the correct order", "DFS visits all connected components") {
    dfs.search(dfs_output_file_path);
    ifstream dfs_output_file; dfs_output_file.open(dfs_output_file_path);
    string term,lang;
    vector<std::string> actual_ids; // Stores the IDs for the nodes read in from the outputted traversal
    int node_count = 0;
    while (std::getline(dfs_output_file, lang,',') && std::getline(dfs_output_file, term)) {
        node_count++;
        actual_ids.push_back(lang + term);
    }
    REQUIRE(node_count == graph_dfs.getNodeCount()); // All nodes are traversed

    // Compare the read in IDS to the IDS stored in the Graph in the traversal order
    vector<std::string> expected_ids = graph_dfs.getNodeIDs();
    /* Order of Traversal:
         جَزِيرَة القَمَر -> comoros
        Cat
        Catt
        free
        θησαυρός -> Latin thesaurus -> English Thesaurus
        frijon
        
        Each arrow indicates the order of traversal dictated and dependent on directed edges/children
        A new line indicates there are no children of the last node, so the next component/node in the list is traversed
    */
    REQUIRE(actual_ids[0] == expected_ids[0]); // جَزِيرَة القَمَر
    REQUIRE(actual_ids[1] == expected_ids[6]); // comoros
    REQUIRE(actual_ids[2] == expected_ids[1]); // cat
    REQUIRE(actual_ids[3] == expected_ids[2]); // catt
    REQUIRE(actual_ids[4] == expected_ids[3]); //  free
    REQUIRE(actual_ids[5] == expected_ids[4]); // θησαυρός 
    REQUIRE(actual_ids[6] == expected_ids[5]); // L. thesaurus
    REQUIRE(actual_ids[7] == expected_ids[8]); // E. thesaurus
    REQUIRE(actual_ids[8] == expected_ids[7]); // frijon
}

TEST_CASE("DFS outputs empty file for empty data (no errors)") {
    DFS dfs(Graph("non-existent-data.txt", "non-existent-data.txt"));
    dfs.search("dfs_empty.txt");
    ifstream empty_file; empty_file.open("../algorithms/dfs_empty.txt");
    string line; 
    int count = 0;
    while(std::getline(empty_file, line)) {
        count++;
    }
    REQUIRE_NOTHROW(count == 0);
}