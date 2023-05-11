#include "catch2/catch.hpp"
#include "../include/adjacencyedge.h"
#include "../include/adjacencynode.h"
#include "../include/DFS.h"
#include "../include/graph.h"
#include "../include/IDDFS.h"
#include <fstream>
using std::ifstream;

Graph graph_iddfs("../algorithms/tests/edges_subset.txt", "../algorithms/tests/nodes_subset.txt");
IDDFS iddfs(graph_iddfs);
string iddfs_output_file_path = "../algorithms/tests/iddfs_output_test.txt";

TEST_CASE("IDDFS outputs empty file for invalid outputs (no errors)") {
    SECTION("Invalid start ID") {
        REQUIRE_NOTHROW(iddfs.search(iddfs_output_file_path, "notaLangthesaurus", "middle englishcat", 2));
    }
    SECTION("Invalid target ID") {
        REQUIRE_NOTHROW(iddfs.search(iddfs_output_file_path, "latinthesaurus", "englishnotaword", 2));
    }
}

TEST_CASE("Run IDDFS for valid inputs") {
    SECTION("IDDFS returns true, found input as related term") {
        REQUIRE(iddfs.search(iddfs_output_file_path, "latinthesaurus", "englishthesaurus", 2));
    }

    SECTION("IDDFS returns false, term is not related") {
        REQUIRE_FALSE(iddfs.search(iddfs_output_file_path, "englishcomoros", "latinthesaurus", 5));
    }

    SECTION("IDDFS returns true for extra whitespace inputs") {
        REQUIRE(iddfs.search(iddfs_output_file_path, "  latinthesaurus  ", "    englishthesaurus    ", 2));
        REQUIRE(iddfs.search(iddfs_output_file_path, "  latinthesaurus", "englishthesaurus  ", 2));
        REQUIRE(iddfs.search(iddfs_output_file_path, "latinthesaurus      ", "  englishthesaurus", 2));
    }
}

TEST_CASE("Specified Depth") {
    SECTION("Target Exists but Not Within Depth") {
        REQUIRE_FALSE(iddfs.search(iddfs_output_file_path, "latinthesaurus", "englishthesaurus", 1));
    }

    SECTION("Depth is Larger than Needed") {
        REQUIRE_NOTHROW(iddfs.search(iddfs_output_file_path, "latinthesaurus", "englishthesaurus", 10));
        REQUIRE(iddfs.search(iddfs_output_file_path, "latinthesaurus", "englishthesaurus", 10));
    }
    
    SECTION("Check negative depths") {
        // Expected behavior: Only return true when the start=target, else always false
        REQUIRE_FALSE(iddfs.search(iddfs_output_file_path, "latinthesaurus", "englishthesaurus", -1));
        REQUIRE(iddfs.search(iddfs_output_file_path, "englishthesaurus", "englishthesaurus", -5));
    }  

    SECTION("Check 0 depths") {
        // Expected behavior: Only return true when the start=target, else always false
        REQUIRE_FALSE(iddfs.search(iddfs_output_file_path, "latinthesaurus", "englishthesaurus", 0));
        REQUIRE(iddfs.search(iddfs_output_file_path, "latinthesaurus", "latinthesaurus", 0));
    }
}

TEST_CASE("Check traversal order in actual vs expected IDDFS txts") {
    iddfs.search(iddfs_output_file_path, "Ancient Greekθησαυρός", "englishthesaurus", 2);
    ifstream iddfs_expected; iddfs_expected.open("../algorithms/tests/iddfs_expected.txt");
    ifstream iddfs_actual; iddfs_actual.open("../algorithms/tests/iddfs_output_test.txt");
    string line; string test_line;
    while(std::getline(iddfs_actual, test_line) && std::getline(iddfs_expected, line)) {
        REQUIRE(line == test_line);
    }
}