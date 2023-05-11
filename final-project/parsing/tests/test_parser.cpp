#include "catch2/catch.hpp"
#include "./include/parser.h"
using std::string;
using std::ifstream;

TEST_CASE("Print Graph outputs empty text file for empty dataset") {
    Parser parser;
    parser.printGraph("tests");
    SECTION("Check printGraph() doesn't error") {
        ifstream edge_file; edge_file.open("../parsing/tests/edges.txt");
        ifstream node_file; node_file.open("../parsing/tests/nodes.txt");
        string line; 
        int count_edge = 0;
        int count_node = 0;
        while(std::getline(edge_file, line)) {
            count_edge++;
        }
        while(std::getline(node_file, line)) {
            count_node++;
        }
        REQUIRE(count_node == 0);
        REQUIRE(count_edge == 0);
    }
}

TEST_CASE("Nodes.txt and Edges.txt Print Graph outputs correctly for mini subset") {
    Parser parser;
    parser.parse("../data/mini-test-subset.csv");
	parser.printGraph("tests");
    ifstream edge_file; edge_file.open("../parsing/tests/edges.txt");
    ifstream node_file; node_file.open("../parsing/tests/nodes.txt");
    SECTION("Check Nodes.txt") {
        ifstream test_node_file; test_node_file.open("../parsing/tests/mini-test-subset-nodes.txt");
        string line;
        string test_line;
        while(std::getline(test_node_file, test_line) && std::getline(node_file, line)) {
            REQUIRE(line == test_line);
        }
    } 
    SECTION("Check Edges.txt") {
        ifstream test_edge_file; test_edge_file.open("../parsing/tests/mini-test-subset-edges.txt");
        string line;
        string test_line;
        while(std::getline(edge_file, line) && std::getline(test_edge_file, test_line)) {
            REQUIRE(line == test_line);
        }
    }
}