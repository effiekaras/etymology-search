#include "include/parser.h"

int main(int argc, char** argv) {
	if (argc > 1) {
		std::cout << "Incorrect arguments" << std::endl;
		return 0;
	}

	std::string data_path = "../data/etymology.csv";
	std::string out_path = "./data";

	if (argc == 1) {
		data_path = argv[0];
	}

	Parser parser;
	parser.parse(data_path);
	parser.printGraph(out_path);
	return 0;
}