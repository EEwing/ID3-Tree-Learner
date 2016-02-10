#include "Attribute.h"

#include <cstdlib>
#include <iostream>

#include "TreeBuilder.h"

using std::cout;
using std::endl;

Attribute::Attribute(void) {
    data = NULL;
    name = "";
}

Attribute::~Attribute(void) {
    if (data != NULL)
        delete [] data;
}

bool *Attribute::GetData(void) {
    return data;
}

void Attribute::SetNumObjects(int numObjects_) {
    numObjects = numObjects_;
    data = new bool[numObjects];
}

void Attribute::SetName(std::string name_) {
    name = name_;
}

std::string Attribute::GetName(void) {
    return name;
}

void Attribute::CalculateAttributeCount(void) {
    attCount[0] = attCount[1] = 0;
    for(int j=0; j<numObjects; ++j) {
        if(data[j])
            ++attCount[1];
        else
            ++attCount[0];
    }
    //cout << "Attribute: " << name << endl << "\t0=" << attCount[0] << ", 1=" << attCount[1] << endl;
}
int Attribute::GetNumTrue(void) {
    return attCount[1];
}

int Attribute::GetNumFalse(void) {
    return attCount[0];
}

double Attribute::GetEntropy(Attribute *last) {

    Attribute *trueAtt = GetSubset(true, last);
    Attribute *falseAtt = GetSubset(false, last);

    int f[2] = {falseAtt->GetNumFalse(), falseAtt->GetNumTrue()};
    int t[2] = {trueAtt->GetNumFalse(), trueAtt->GetNumTrue()};

/*
    for(int i=0; i<numObjects; ++i) {
        if(data[i] == true && last->GetData()[i] == true)
            ++t[1];
        else if(data[i] == true && last->GetData()[i] == false)
            ++t[0];
        else if(data[i] == false && last->GetData()[i] == true)
            ++f[1];
        else// (data[i] == false && last->GetData()[i] == false)
            ++f[0];
    }
    cout << tt << " vs " << t[1] << endl;
    cout << tf << " vs " << t[0] << endl;
    cout << ft << " vs " << f[1] << endl;
    cout << ff << " vs " << f[0] << endl;
    t[0] = tf;
    t[1] = tt;
    f[0] = ff;
    f[1] = ft;
*/
    double sum = 0;
    if(f[0] == 0 || f[1] == 0) {
        //cout << "Calculating Entropy of a leaf" << endl;
        return 0;
    }
    if(t[0] == 0 || t[1] == 0) {
        //cout << "Calculating Entropy of a leaf" << endl;
        return 0;
    }
    sum = ((double)GetNumFalse()/numObjects)*Information(f[0], f[1]);
    sum += ((double)GetNumTrue()/numObjects)*Information(t[0], t[1]);
/*
    cout << "First sum: " << sum << endl;
    sum = 0;
    for(int i=0; i<2; ++i) {
        sum += ( (double)(t[i]+f[i]) / numObjects )*Information(t[i], f[i]);
    }
    cout << "Second sum: " << sum << endl;
*/
    //cout << name << ": entropy=" << sum << endl;
    //cout << name << ": entropy=" << sum << " numObjects=" << numObjects << " i0=" << Information(f[0], f[1]) << " i1=" << Information(t[0], t[1]) << endl;
    return sum;
}

double Attribute::GetInformationGain(Attribute *last) {
    if(last->GetNumTrue() == 0 || last->GetNumFalse() == 0)
        return 0.;
    return Information(last->GetNumTrue(), last->GetNumFalse()) - GetEntropy(last);
}

Attribute *Attribute::GetSubset(bool value, Attribute *other) {
    int numElements = value ? GetNumTrue() : GetNumFalse();
    Attribute *rtn = new Attribute();

    rtn->SetNumObjects(numElements);
    rtn->SetName(other->GetName());

    int j=0;
    for(int i=0; i<numObjects; ++i) {
        if(GetData()[i] == value)
            rtn->GetData()[j++] = other->GetData()[i];
    }
    rtn->CalculateAttributeCount();
    return rtn;
}

void Attribute::Print(void) {
    cout << "Attribute: " << name << endl;
    for(int i=0; i<numObjects; ++i) {
        cout << data[i];
    }
    cout << endl;
}

int Attribute::GetNumObjects(void) {
    return numObjects;
}
