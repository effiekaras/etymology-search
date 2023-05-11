#include "catch2/catch.hpp"
#include "../include/drawing.h"
#include "../include/graph.h"
#include <fstream>
using std::ifstream;

string layered_graph_folder = "../algorithms/tests/layered_graph_output_tests/";
string layered_graph_output_file = layered_graph_folder + "layered_graph_output_test.txt";
Drawing layered_graph(Graph("../algorithms/tests/edges_subset.txt", "../algorithms/tests/nodes_subset.txt"));

TEST_CASE("Drawing Related Parents") {
	// Test that output file matches expected file and edge cases do not throw errors
    SECTION("Node with no children") {
        REQUIRE_NOTHROW(layered_graph.drawRelated("englishthesaurus", layered_graph_output_file, true));
        ifstream layered_expected; layered_expected.open(layered_graph_folder + "rel_parent_no_child.txt");
        ifstream layered_actual; layered_actual.open(layered_graph_output_file);
        string line; string test_line;
        while(std::getline(layered_actual, test_line) && std::getline(layered_expected, line)) {
            REQUIRE(line == test_line);
        }
    }
    
    SECTION("Node with no parents") {
        REQUIRE_NOTHROW(layered_graph.drawRelated("Ancient Greekθησαυρός", layered_graph_output_file, true));
        ifstream layered_expected; layered_expected.open(layered_graph_folder + "rel_parent_no_parent.txt");
        ifstream layered_actual; layered_actual.open(layered_graph_output_file);
        string line; string test_line;
        while(std::getline(layered_actual, test_line) && std::getline(layered_expected, line)) {
            REQUIRE(line == test_line);
        }
    }
}

TEST_CASE("Drawing Related Children") {
	// Test that output file matches expected file and edge cases do not throw errors
    SECTION("Node with no children") {
        REQUIRE_NOTHROW(layered_graph.drawRelated("englishthesaurus", layered_graph_output_file, false));
        ifstream layered_expected; layered_expected.open(layered_graph_folder + "rel_children_no_child.txt");
        ifstream layered_actual; layered_actual.open(layered_graph_output_file);
        string line; string test_line;
        while(std::getline(layered_actual, test_line) && std::getline(layered_expected, line)) {
            REQUIRE(line == test_line);
        }
    }
    
    SECTION("Node with no parents") {
        REQUIRE_NOTHROW(layered_graph.drawRelated("Ancient Greekθησαυρός", layered_graph_output_file, false));
        ifstream layered_expected; layered_expected.open(layered_graph_folder + "rel_children_no_parent.txt");
        ifstream layered_actual; layered_actual.open(layered_graph_output_file);
        string line; string test_line;
        while(std::getline(layered_actual, test_line) && std::getline(layered_expected, line)) {
            REQUIRE(line == test_line);
        }
    }
}

TEST_CASE("Test Invalid Inputs") {
    SECTION("Input Nonexistent Node ID") {
        REQUIRE_NOTHROW(layered_graph.drawRelated("n8σαυρός4284**@#7283q92812sdksd", "", true));
    }
}
