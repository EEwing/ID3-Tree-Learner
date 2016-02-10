#include <iostream>
#include <cstdlib>

#include <fstream>

#include "CSVReader.h"
#include "ID3Tree.h"

using std::cout;
using std::endl;

int main(int argc, char **argv) {

    if(argc != 4) {
        cout << "Usage: " << argv[0] << " <training set> <test set> <model file>" << endl;
        exit(EXIT_FAILURE);
    }

    CSVReader reader;
    reader.SetFileName(argv[1]);
    reader.Read();

    ID3Tree *tree= reader.GenerateTree();

    std::ofstream out(argv[3]);
    tree->Print(out);

    CSVReader test;
    test.SetFileName(argv[2]);
    test.Read();

    double valid = tree->CheckAgainstDataset(test);
    cout << "Found " << valid*100 << "% correct answers!" << endl;

    if(tree != NULL)
        delete tree;
}
