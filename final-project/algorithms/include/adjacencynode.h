#pragma once
#include <string>
#include <list>

using std::string;
using std::list;

class AdjacencyNode {
    public:
        AdjacencyNode(std::string l, std::string t): language(l), term(t) {};
        string getLang();
        string getTerm();
        
    private:
        string term;
        string language;
};