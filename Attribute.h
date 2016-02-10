#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <string>

class Attribute {
  private:
     std::string    name;
     bool          *data;
     int            numObjects;
     int            attCount[2];
     double         GetEntropy(Attribute *);
  public:
                    Attribute(void);
                   ~Attribute(void);

     void           SetNumObjects(int);
     int            GetNumObjects(void);

     bool          *GetData(void);
     void           SetName(std::string);
     std::string    GetName(void);
     double         GetInformationGain(void);

     int            GetNumFalse(void);
     int            GetNumTrue(void);

     void           CalculateAttributeCount(void);
     double         GetInformationGain(Attribute *);

     Attribute     *GetSubset(bool, Attribute *);

     void           Print(void);
};

#endif
