#include "../include/parser.h"

using std::string;
using std::ifstream;
using std::ofstream;
using std::wstring;

void Parser::parse(string file_path) {
    /*
		1. Load file into fstream
		2. Read line from file
		3. Output the line to an output file
	*/
    string term_id,lang,term,reltype,related_term_id,related_lang,related_term,position,group_tag,parent_tag,parent_position;
	ifstream in_file; in_file.open(file_path);
	string current_term, current_lang; // string of wchar_t

	while (std::getline(in_file, term_id, ',') && std::getline(in_file, lang, ',') 
    && std::getline(in_file, term, ',') && std::getline(in_file, reltype, ',') 
    && std::getline(in_file, related_term_id, ',') && std::getline(in_file, related_lang, ',') 
    && std::getline(in_file, related_term, ',') && std::getline(in_file, position, ',') 
    && std::getline(in_file, group_tag, ',') && std::getline(in_file, parent_tag, ',') 
    && std::getline(in_file, parent_position)) {
        /*
            Check reltype. If valid, go on. else, disregard line
            First check if hit new term. If so, create new node.
            Check if related term exists. If not, add to list of nodes
            Add edge to edge list
        */
        auto rel = typeMap_.find(reltype);
        if (rel->second < 25){
            if (term != current_term || lang != current_lang) {
                // create new node
                Node* node_ptr = new Node(lang, term);
                nodes_.insert(std::pair<string,Node*>(lang+term,node_ptr));
                current_term = term;
                current_lang = lang;
            }

            auto relterm_itr = nodes_.find(related_lang+related_term);

            if (relterm_itr == nodes_.end()) {
                Node* related_ptr = new Node(related_lang, related_term);
                nodes_.insert(std::pair<string, Node*>(related_ptr->getID(), related_ptr));
            }
            auto term_itr = nodes_.find(lang+term);
            relterm_itr = nodes_.find(related_lang+related_term);


            auto edge_itr = edges_.find(relterm_itr->second->getID() + term_itr->second->getID());

            if (edge_itr == edges_.end()) {
                Edge* edge = new Edge(relterm_itr->second, term_itr->second, reltype);
                edges_.insert(std::pair<string, Edge*>(edge->getStart()->getID() + edge->getEnd()->getID(), edge));
            } else {
                edge_itr->second->addRelType(reltype);
            }

        }
    }
}

// Takes in data file without ignored reltypes
void Parser::printGraph(string folder_path) {
    ofstream nodes_file; nodes_file.open(folder_path + "/nodes.txt");
    ofstream edges_file; edges_file.open(folder_path + "/edges.txt");

    if (edges_.empty() || nodes_.empty()) { // If either map is empty, output empty files
        return;
    }

    std::unordered_map<std::string, Node*>::iterator it = nodes_.begin();
    while (it != nodes_.end()) {
        Node* node = it->second;
        nodes_file << node->getLang() << "," << node->getTerm() << "," << node->getID() << std::endl;
        ++it;
    }

    for (auto edge : edges_) {
        edges_file << edge.second->getStart()->getLang() << "," << edge.second->getStart()->getTerm() << "," << edge.second->getEnd()->getLang() << "," << edge.second->getEnd()->getTerm();
        for (string type : edge.second->getRelTypes()) {
            edges_file << ", " << type;
        }
        edges_file << std::endl;
    }
}