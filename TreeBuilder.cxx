#include "TreeBuilder.h"

#include <cmath>
#include <iostream>

#include "Leaf.h"

using std::cout;
using std::endl;

double Information(int t, int f) {
    double tperc = (double)t/(t+f);
    double fperc = (double)f/(t+f);
/*
    cout << "tperc=" << tperc << ", fperc=" << fperc << endl;
    cout << "log2 true=" << log2(tperc) << ", log2 false=" << log2(fperc) << endl;
*/
    return (-tperc*log2(tperc)) + (-fperc*log2(fperc));
}

void BuildTree(ID3Tree *tree, int numAttributes, Attribute *atts) {
    Attribute **newAtts = new Attribute *[numAttributes];

    for(int i=0; i<numAttributes; ++i) {
        newAtts[i] = atts + i;
    }

    BuildTree(tree, numAttributes, newAtts);
    delete [] newAtts;
}

void BuildTree(ID3Tree *tree, int numAttributes, Attribute **atts) {
    if(tree == NULL) return;

    //cout << "Building tree with " << numAttributes << " Attributes" << endl;

    Attribute *last = atts[numAttributes-1];
   
    if(numAttributes < 3) { // attrib 1 = tree, attrib 2 = class attrib
        tree->SetAttribute(atts[0]);
        tree->SetLeftChild(new Leaf(last->GetName(), atts[0]->GetData()[0]));
        tree->SetRightChild(new Leaf(last->GetName(), atts[0]->GetData()[0]));
        return;
    }
   

    double I = Information(last->GetNumTrue(), last->GetNumFalse());

    //cout << "Found Needed bits: " << I << endl;

    // Find attribute to split on
    double     maxInfoGain = -1;
    Attribute *branchAtt = NULL;
    int        branchidx = -1;
    for(int i=0; i<numAttributes-1; ++i) {
        double gain = atts[i]->GetInformationGain(last);
        //cout << atts[i]->GetName() << ": gain=" << gain << endl;
        if(gain > maxInfoGain) {
            maxInfoGain      = gain;
            branchAtt = atts[i];
            branchidx = i;
        }
    }

    tree->SetAttribute(branchAtt);

    //cout << "Max Info Gain: " << branchAtt->GetName() << "=" << maxInfoGain << endl;

    Attribute *tmp;
    for(int i=branchidx; i<numAttributes-1; ++i) {
        tmp = atts[i];
        atts[i] = atts[i+1];
        atts[i+1] = tmp;
    }

    // partition data
    Attribute **left = new Attribute *[numAttributes-1];
    Attribute **right = new Attribute *[numAttributes-1];


    //int f=0, t=0;
    for(int i=0; i<numAttributes-1; ++i) {
        Attribute *newFalse = branchAtt->GetSubset(false, atts[i]);
        Attribute *newTrue = branchAtt->GetSubset(true, atts[i]);
        if(atts[i] == branchAtt) {
            cout << "Swap failed, this shouldn't happen! We'll probably fail" << endl;
            continue;
        }
        left[i] = newFalse;
        right[i] = newTrue;
    }

    Attribute *lastLeft = left[numAttributes-2];
    Attribute *lastRight = right[numAttributes-2];

    bool isLeftLeaf = lastLeft->GetNumFalse() == 0 || lastLeft->GetNumTrue() == 0;
    bool isRightLeaf = lastRight->GetNumFalse() == 0 || lastRight->GetNumTrue() == 0;

    if(isLeftLeaf) {
        tree->SetLeftChild(new Leaf(last->GetName(), left[numAttributes-2]->GetData()[0]));
    } else {
        tree->SetLeftChild(new ID3Tree()); // Could be a Leaf, we don't know
        BuildTree(tree->GetLeftChild(), numAttributes-1, left);
    }

    if(isRightLeaf) {
        tree->SetRightChild(new Leaf(last->GetName(), right[numAttributes-2]->GetData()[0]));
    } else {
        tree->SetRightChild(new ID3Tree()); // Could be a Leaf, we don't know
        BuildTree(tree->GetRightChild(), numAttributes-1, right);
    }

    delete [] left;
    delete [] right;

    // build sub-trees
}
