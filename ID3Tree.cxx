#include "ID3Tree.h"

#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;

ID3Tree::ID3Tree(void) {
    left = NULL;
    right = NULL;
}

ID3Tree::~ID3Tree(void) {
    if(left != NULL)
        delete left;
    if(right != NULL)
        delete right;
}

ID3Tree *ID3Tree::GetLeftChild(void) {
    return left;
}

ID3Tree *ID3Tree::GetRightChild(void) {
    return right; 
}

Attribute *ID3Tree::GetAttribute(void) {
    return att;
}

void ID3Tree::SetAttribute(Attribute *att_) {
    att = att_;
}

void ID3Tree::SetLeftChild(ID3Tree *left_) {
    left = left_;
}

void ID3Tree::SetRightChild(ID3Tree *right_) {
    right = right_;
}

void ID3Tree::Print(std::ostream &stream) {
    Print(stream, 0);
}

void ID3Tree::Print(std::ostream &stream, int numTabs) {
    for(int i=0; i<numTabs; ++i)
        stream << "| ";

    if(left->att->GetNumObjects() == 1) {
        stream << att->GetName() << " = 0 : " << left->att->GetData()[0] << endl;
    } else {
        stream << att->GetName() << " = 0 :" << endl;
        left->Print(stream, numTabs+1);
    }

    for(int i=0; i<numTabs; ++i)
        stream << "| ";
    
    if(right->att->GetNumObjects() == 1) {
        stream << att->GetName() << " = 1 : " << right->att->GetData()[0] << endl;
    } else {
        stream << att->GetName() << " = 1 :" << endl;
        right->Print(stream, numTabs+1);
    }
}

bool ID3Tree::CheckAgainstObject(CSVReader &reader, int object) {
    int attidx = -1;
    for(int j=0; j<reader.GetNumberOfAttributes(); ++j) {
        if(att->GetName() == reader.GetAttribute(j)->GetName()) {
            attidx = j;
            break;
        }
    }
    if(attidx == -1) {
        cout << "Attribute " << att->GetName() << " not found!" << endl;
        return false;
    }
    bool val = reader.GetAttribute(attidx)->GetData()[object];
    if(val)
        return right->CheckAgainstObject(reader, object);
    else
        return left->CheckAgainstObject(reader, object);

}

double ID3Tree::CheckAgainstDataset(CSVReader &reader) {
    int correct= 0;
    for(int i=0; i<reader.GetNumberOfObjects(); ++i) {
        bool rtn = CheckAgainstObject(reader, i);
        if(rtn) ++correct;
    }
    if(correct != reader.GetNumberOfObjects())
        cout << "Missed " << reader.GetNumberOfObjects()-correct << " objects" << endl;
    return (double)correct/reader.GetNumberOfObjects();
}
