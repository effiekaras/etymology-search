#include "../include/edge.h"

Edge::Edge(Node* start, Node* end, std::string relType) {
    start_ = start;
    end_ = end;
    relations_.push_front(relType);
}

Node* Edge::getStart() const {
    return start_;
}

Node* Edge::getEnd() const {
    return end_;
}

std::list<std::string> Edge::getRelTypes() const {
    return relations_;
}

void Edge::addRelType(std::string relType) {
    relations_.push_front(relType);
}
