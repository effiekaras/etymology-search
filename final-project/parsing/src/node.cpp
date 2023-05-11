#include "../include/node.h"

std::string Node::getLang() const {
	return lang;
}

std::string Node::getTerm() const {
	return term;
}

std::string Node::getID() const {
	return lang + term;
}