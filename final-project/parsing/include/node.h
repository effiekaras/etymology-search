#pragma once
#include <string>

class Node { 
	// unsigned long index;
	public:
		Node(std::string l, std::string t): lang(l), term(t) {};
		
		std::string getLang() const;
		std::string getTerm() const;
		std::string getID() const;

	private:
		std::string lang;
		std::string term;
};
