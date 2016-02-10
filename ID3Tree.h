#ifndef ID3_TREE_H
#define ID3_TREE_H

#include <ostream>

#include "Attribute.h"
#include "CSVReader.h"

class CSVReader;

class ID3Tree {
  protected:
    ID3Tree *left;
    ID3Tree *right;

    Attribute *att;

   virtual bool      CheckAgainstObject(CSVReader &, int);
   virtual void      Print(std::ostream &, int);

  public:

                     ID3Tree(void);
                    ~ID3Tree(void);

    virtual ID3Tree *GetLeftChild(void);
    virtual ID3Tree *GetRightChild(void);

    void             SetLeftChild(ID3Tree *);
    void             SetRightChild(ID3Tree *);

    Attribute       *GetAttribute(void);
    void             SetAttribute(Attribute *);

    void             Print(std::ostream &);

    double           CheckAgainstDataset(CSVReader &);

};

#endif
