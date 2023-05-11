#include "include/graph.h"
#include "include/DFS.h"
#include "include/IDDFS.h"
#include <boost/algorithm/string.hpp>
#include "include/drawing.h"
#include <iostream>

int main()
{
	Graph graph;
	bool quit = false;
	std::cout << "What woud you like to do?" << std::endl;
	std::cout << "1. Run DFS 2. Run IDDFS 3. Create layered drawing. 4. See related terms" << std::endl;
	char input;
	
	while (!quit) {
		std::cout << "Type a number between 1-4 or q to quit: ";
		std::cin >> input;

		if (input == 'q' || input == 'Q') {
			quit = true;
			continue;
		}

		int digit = input - '0';

		if (digit > 0 && digit < 5) {
			
			if (digit == 1) {
				DFS dfs(graph);
				dfs.search();
				std::cout << "Check dfs-traversal.txt for your DFS!" << std::endl;
			} else {
				string lang;
				string word;

				std::cout << "Please enter a start language: ";
				std::cin >> lang;
				boost::algorithm::trim(lang); boost::to_lower(lang);
				std::cout << "Please enter a start term: ";
				std::cin >> word;
				boost::algorithm::trim(word); boost::to_lower(word);
				int depth;

				if (graph.getNode(lang+word) == nullptr) {
					continue;
				}

				if (digit == 2) {
					string t_lang;
					string t_word;
					std::cout << "Please enter a target language: ";
					std::cin >> t_lang;
					boost::algorithm::trim(t_lang); boost::to_lower(t_lang);
					std::cout << "Please enter a target term: ";
					std::cin >> t_word;
					boost::algorithm::trim(t_word); boost::to_lower(t_word);
					std::cout << "Please enter a depth: ";
					std::cin >> depth;

					IDDFS iddfs(graph);
					iddfs.search("deep-traversal.txt", lang+word, t_lang+t_word, depth);

					std::cout << "Check out the traversal in deep-traversal.txt!" << std::endl;
				} else if (digit == 3) {
					std::cout << "Would you like to draw the parents or children of the node?" << std::endl;
					std::cout << "1. Draw Parents. 2. Draw Children 3. Draw entire dataset" << std::endl;
					char input;
					std::cin >> input;

					if (input == 'q' || input == 'Q') {
						quit = true;
						break;
					}

					int in = input - '0';

					if (in == 1) {
						Drawing drawing(graph);
						drawing.drawRelated(lang+word, "layered-drawing.txt", true);
						std::cout << "You can find the drawing in the layered-drawing.txt file :)" << std::endl;
					} else if (in == 2) {
						Drawing drawing(graph);
						drawing.drawRelated(lang+word, "layered-drawing.txt", false);
						std::cout << "You can find the drawing in the layered-drawing.txt file :)" << std::endl;
					} else if (in == 3) {
						Drawing drawing(graph);
						drawing.printDataset("layered-drawing-dataset.txt");
						std::cout << "You can find the drawing in the layered-drawing-dataset.txt file :)" << std::endl;
					} else {
						std::cout << "Please enter a valid input" << std::endl;
						continue;
					}					
				} else if (digit == 4) {
					std::cout << "Here is the child(ren) of the term: " << std::endl;
					int i = 1;
					auto children_nodes = graph.getAdjacentChildren(graph.getNode(lang+word));
					for (AdjacencyNode* children_node : children_nodes) {
						std::cout << children_node->getLang() << " " << children_node->getTerm(); 
						if (i < children_nodes.size()) {
							std::cout << ", ";
						}
						++i;
					}
					i = 1;
					std::cout << std::endl;
					std::cout << "Here is the parent(s) of the term: " << std::endl; 
					auto parent_nodes = graph.getAdjacentParent(graph.getNode(lang+word));
					for (AdjacencyNode* parent_node : parent_nodes) {
						std::cout << parent_node->getLang() << " " << parent_node->getTerm();
						if (i < parent_nodes.size()) {
							std::cout << ", ";
						}
						++i;
					}
					std::cout << std::endl;
				} else {
					std::cout << "Uh oh, something unexpected happened! Please try again." << std::endl;
				}
			}
		} else {
			std::cout << "I wasn't expecting that!" << std::endl;
		}
	}
	return 0;
}
