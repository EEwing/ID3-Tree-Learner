#ifndef CSV_READER_H
#define CSV_READER_H

#include <string>

#include "ID3Tree.h"
#include "Attribute.h"

class ID3Tree;

class CSVReader {
  private:

    std::string    filename;
    int            numAttributes;
    int            numObjects;
    Attribute     *attributes;
    //bool         **data;
    //std::string   *attnames;

  public:

                CSVReader(void);
               ~CSVReader(void);

    void        SetFileName(std::string);
    bool        Read(void);

    Attribute  *GetAttribute(int);
    std::string GetAttributeName(int);

    int         GetNumberOfAttributes(void);
    int         GetNumberOfObjects(void);

    void        PrintData(void);

    ID3Tree    *GenerateTree(void);

};

#endif
