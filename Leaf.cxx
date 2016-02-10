#include "Leaf.h"

#include <cstdlib>
#include <iostream>

#include "Attribute.h"

using std::cout;
using std::endl;

Leaf::Leaf(std::string name, bool val) {
    att = new Attribute();
    att->SetName(name);
    att->SetNumObjects(1);
    att->GetData()[0] = val;
    att->CalculateAttributeCount();
}

ID3Tree *Leaf::GetLeftChild(void) { return NULL; }
ID3Tree *Leaf::GetRightChild(void) { return NULL; }

bool Leaf::CheckAgainstObject(CSVReader &reader, int object) {
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
    //cout << "Checking attribute " << att->GetName() << ": self=" att->GetData()[0] << " them=" << val
    return val == att->GetData()[0];
}
