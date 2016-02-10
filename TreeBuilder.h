#ifndef TREE_BUILDER_H
#define TREE_BUILDER_H

#include "ID3Tree.h"

double Information(int p, int n);

void BuildTree(ID3Tree *, int, Attribute *);
void BuildTree(ID3Tree *, int, Attribute **);

#endif
