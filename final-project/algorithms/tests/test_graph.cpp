#include "catch2/catch.hpp"
#include "../include/adjacencyedge.h"
#include "../include/adjacencynode.h"
#include "../include/graph.h"
#include <set>
using std::set;

Graph graph("../algorithms/tests/edges_subset.txt", "../algorithms/tests/nodes_subset.txt");

TEST_CASE("Creating Graph From Nodes.txt and Edges.txt subsets") {
    SECTION("Number of nodes") {
        REQUIRE(graph.getNodeCount() == 9);
    }

    SECTION("Test no nodes are repeated", "[getNodeCount]") {
        set<string> nodeIDs;
        int set_length = 0;
        for (int i=0; i < graph.getNodeCount(); i++) {
            nodeIDs.insert(graph.getNodeID(i));
            set_length++;
            REQUIRE(nodeIDs.size() == set_length);
        }
    } 
}

TEST_CASE("Get Adjacent Children") {
    SECTION("Node with No Children") {
        auto no_child_node = graph.getNode("englishthesaurus");
        auto children = graph.getAdjacentChildren(no_child_node);
        REQUIRE(children.empty());
    }
    SECTION("Node with Child") {
        auto node = graph.getNode("old englishcatt");
        auto children = graph.getAdjacentChildren(node);
        REQUIRE(children.size() == 1);
        auto child = children[0];
        REQUIRE(child->getLang() == "middle english");
        REQUIRE(child->getTerm() == "cat");
    }
    SECTION("Node with Multiple Children") {
        auto node = graph.getNode("ancient greekθησαυρός");
        auto children = graph.getAdjacentChildren(node);
        REQUIRE(children.size() == 2);
        REQUIRE(children[0]->getLang() == "latin");
        REQUIRE(children[0]->getTerm() == "thesaurus");
        REQUIRE(children[1]->getLang() == "english");
        REQUIRE(children[1]->getTerm() == "thesaurus");
    }
}

TEST_CASE("Get Adjacent Parents") {
    SECTION("Node with No Parent") {
        auto node = graph.getNode("Proto-West Germanic*frijōn");
        auto parents = graph.getAdjacentParent(node);
        REQUIRE(parents.size() == 0);
    }
    SECTION("Node with One Parent", "Segmental Writing Language") {
        auto node = graph.getNode("englishcomoros");
        auto parents = graph.getAdjacentParent(node);
        REQUIRE(parents.size() == 1);
        auto parent = parents[0];
        REQUIRE(parent->getLang() == "arabic");
        REQUIRE(parent->getTerm() == "جَزِيرَة القَمَر");
    }
    SECTION("Node with Multiple Parents") {
        auto node = graph.getNode("Englishthesaurus");
        auto parents = graph.getAdjacentParent(node);
        REQUIRE(parents.size() == 2);
        REQUIRE(parents[0]->getLang() == "ancient greek");
        REQUIRE(parents[0]->getTerm() == "θησαυρός");
        REQUIRE(parents[1]->getLang() == "latin");
        REQUIRE(parents[1]->getTerm() == "thesaurus");
    }
}

TEST_CASE("Get Adjacent Edges") {

    SECTION("Node with No Directed Adjacent Edges") {
        auto node = graph.getNode("englishfree");
        auto adj_edges = graph.getAdjEdges(node);
        REQUIRE(adj_edges.size() == 0);
    }

    SECTION("Node with One Directed Adjacent Edge") {
        auto node = graph.getNode("Proto-West Germanic*frijōn");
        auto adj_edges = graph.getAdjEdges(node);
        REQUIRE(adj_edges.size() == 1);
        REQUIRE(adj_edges[0]->getChild() == graph.getNode("englishfree"));
    }

    SECTION("Node with Multiple Directed Adjacent Edges") {
        auto node = graph.getNode("ancient greekθησαυρός");
        auto adj_edges = graph.getAdjEdges(node);
        REQUIRE(adj_edges.size() == 2);
        REQUIRE(adj_edges[0]->getChild() == graph.getNode("latinthesaurus"));
        REQUIRE(adj_edges[1]->getChild() == graph.getNode("englishthesaurus"));
    }
}

TEST_CASE("Handling term ID inputs for cases, nonexistents") {
    SECTION("Nullptr returned for non-existent node ID inputs") {
        REQUIRE_NOTHROW(nullptr == graph.getNode("MadeUpWord"));
    }
    SECTION("Case insensitvity") {
        REQUIRE(graph.getNode("Englishthesaurus") == graph.getNode("englishthesaurus"));
        REQUIRE(graph.getNode("Englishthesaurus") == graph.getNode("EnglishThesaurus"));
        REQUIRE(graph.getNode("ENGLISHTHESAURUS") == graph.getNode("englishthesaurus"));
    }
}