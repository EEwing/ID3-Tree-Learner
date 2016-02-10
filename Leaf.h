#ifndef LEAF_H
#define LEAF_H

#include <iostream>

#include "ID3Tree.h"

class Leaf : public ID3Tree {
  protected:
    virtual bool     CheckAgainstObject(CSVReader &, int);
  public:
                     Leaf(std::string, bool);
    virtual ID3Tree *GetLeftChild(void);
    virtual ID3Tree *GetRightChild(void);
};

#endif
