# README
#### effiek2-meghan7-ericrc3-cconley3

# Presentation Link: https://youtu.be/H9Y_mCj_x7I

## Major Code, Data, and Results

Full dataset is too large to upload to Github, so the data may be found through this link in Google Drive: https://drive.google.com/file/d/15GDqoJQZ_lwN0Z87GaDttaLvD6e5n1t-/view?usp=sharing
Locally, drag the dataset into ~/final-project/data/ for re-parsing. In this folder, there are two other subsets of the dataset used for testing purposes.

The Boost library is required, readily available through EWS. It can be installed on Linux ubuntu with the following command:
```sudo apt-get install libboost-all-dev```

The current dataset is already parsed in ```~/final-project/data/``` in edges.txt and nodes.txt. The lines in the node file can be understood as {lang, term, id}, where lang is the language, term is the node term, and id is the concatentation *lang + term*. The lines in the edge file can be understood as {rel_lang, rel_term, lang, term, {relTypes}}, where rel_lang is the language for the parent term, rel_term is the parent term, lang is the language for the child, term is the child term, and {relTypes} is the set of all relationship types between the two terms.

The major code for parsing can be found in ```~/final-project/parsing/src/parser.cpp```. The data, including the parsed edge and node text files as mentioned above can be found in ```~/final-project/parsing/data/```. 

The major code for the graph and the algorithms/traversal can be found in ```~/final-project/algorithms/src/```. The structure and loading of the graph, adjacency list, and stored nodes/node ids can be found in ```src/graph.cpp```. The Depth First Search traversal is located at ```src/DFS.cpp```. The iterative deepening DFS traversal can be found at ```src/IDDFS.cpp```. The Layered Graph Drawing code can be found at src/drawing.cpp. The main file for the algorithms can be found in ```~/final-project/algorithms/main.cpp```, and all respective headers can be found at ```~/final-project/algorithms/include/```.

Results for the algorithms may be found in ```~/final-project/algorithms/```. The DFS traversal is outputted in dfs-traversal.txt. dfs_empty.txt is an empty text file used for testing. The IDDFS traversal between two nodes are found at deep-traveresal.txt. Check the console upon running the IDDFS for a printed statement describing whether or not the term is found, at what depth. Results for the layered drawing is outputted at layered-drawing.txt; results for the layered drawing of all nodes in the dataset can be found in ```~/final-project/algorithms/layered-drawing-dataset.txt``` after running the following main commands: 3. Create layered drawing -> Enter a language/term -> 3. Draw entire dataset.

## Commands
> ### Running main for parsing

Run parsing on the full dataset to create edges.txt and nodes.txt files.
1. Download dataset and import ```~/final-project/data/``` as described above.
2. Enter parsing directory at ```~/final-project/parsing/```
3. Run ```$ cmake3 .```
4. Run ```$ make main-parsing```
5. Run ```$ ./main-parsing [OPTIONAL: path to dataset]```
   - where [path to dataset] can be used to run a separate dataset. Without the optional command, it will run on the full dataset imported in data.

> ### Running main for algorithms
1. Enter algorithms directory at ```~/final-project/algorithms/```
2. Run ```$ cmake3 .```
3. Run ```$ make main-algorithms```
4. Run ```$ ./main-algorithms```
5. Follow interactive terminal prompts for running algorithms
6. 1. Run DFS. 2. Run IDDFS. 3. Create layered drawing. 4. See related terms.

## Test Suite
> ### Running tests for parsing

View test cases and respective input and output text files in ```~/final-project/parsing/tests/```
1. Enter parsing directory at ```~/final-project/parsing/```
2. Run ```$ cmake3 .```
3. Run ```$ make test-parsing```
4. Run ```$ ./test-parsing```
5. **All tests passesd (17 assertions in 2 test cases)**

> ### Running tests for algorithms

View test cases and respective input and output text files in ```~/final-project/algorithms/tests/```
1. Enter algorithms directory at ```~/final-project/algorithms```
2. Run ```$ cmake3 .```
3. Run ```$ make test-algorithms```
4. Run ```$ ./test-algorithms```
5. **All tests passed**

We created separate testing files for building the graph, the depth first traversal, and our two algorithms. In our graph tests, we tested our graph functions (e.g. getAdjEdges, getChildren, getParent) to check that our graph is storing data the way we wanted it to, including respective edge cases for each function. We also checked for input case normalization. For DFS and IDDFS, we tested that the traversal order was correct. Our layered graph tests check that the layers are created correctly. Across test files, we checked that invalid or empty input would not throw errors. Further descriptions may be found within the test files.