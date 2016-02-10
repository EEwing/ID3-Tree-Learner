#include "CSVReader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>

#include "utils.h"
#include "TreeBuilder.h"

using std::cout;
using std::endl;
using std::ifstream;

CSVReader::CSVReader() {
    numAttributes = 0;
    numObjects = 0;
    filename = "";
    attributes = NULL;
    //attnames = NULL;
}

CSVReader::~CSVReader() {
    if(attributes != NULL) {
        delete [] attributes;
    }

/*
    if(attnames == NULL) {
        delete [] attnames;
    }
*/
}

bool CSVReader::Read() {
    if(filename.empty())
        return false;

    ifstream fstream(filename.c_str());
    std::string line;
    int numLines = 0;

    while(std::getline(fstream, line))
        ++numLines;


    fstream.clear();
    fstream.seekg(0, fstream.beg);

    std::getline(fstream, line);

    std::vector<std::string> elems = split(line, ',');


    numObjects = numLines-1;
    numAttributes = elems.size();

    //cout << "Found " << numAttributes << " Attributes, and " << numObjects << " Objects, for " << numAttributes*numObjects << " total data points" << endl;

            
    if(attributes != NULL)
        delete [] attributes;

    attributes = new Attribute[numAttributes];

    for(int i=0; i<numAttributes; ++i) {
        attributes[i].SetName(elems[i]);
        attributes[i].SetNumObjects(numObjects);
    }

    for(int i=0; i<numObjects; ++i) {

        std::getline(fstream, line);
        elems = split(line, ',');

        if(elems.size() != numAttributes) {
            return false;
        }

        for(int j=0; j<numAttributes; ++j)
            attributes[j].GetData()[i] = elems[j] == "1" ? true: false;
    }
    for(int i=0; i<numAttributes; ++i)
        attributes[i].CalculateAttributeCount();

    return true;
}

void CSVReader::SetFileName(std::string filename_) {
    filename = filename_;
}

void CSVReader::PrintData(void){
    if(attributes == NULL) {
        cout << "Data not read yet!" << endl;
    } else {
        for(int i=0; i<numAttributes; ++i) {
            //cout << attributes[i].GetName() << ": info=" << attributes[i].GetInformation();
            //cout << attnames[i] << ": ";
            for(int j=0; j<numObjects; ++j) {
                cout << attributes[i].GetData()[j];
                //cout << data[i][j];
            }
            cout << endl;
        }
    }
}

Attribute *CSVReader::GetAttribute(int i) {
    if(attributes == NULL) return NULL;
    else return attributes + i;
}

std::string CSVReader::GetAttributeName(int i) {
    return attributes[i].GetName();
    //if(attnames == NULL) return "invalid-set";
    //else return attnames[i];
}

int CSVReader::GetNumberOfAttributes(void) {
    return numAttributes;
}

int CSVReader::GetNumberOfObjects(void) {
    return numObjects;
}

ID3Tree *CSVReader::GenerateTree(void) {

    ID3Tree *tree = new ID3Tree();


    BuildTree(tree, numAttributes, attributes);


    return tree;
}


