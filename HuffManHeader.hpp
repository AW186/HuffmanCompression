//
//  HuffManHeader.hpp
//  HuffMan
//
//  Created by Zihao Arthur Wang [STUDENT] on 11/26/19.
//  Copyright © 2019 Zihao Arthur Wang [STUDENT]. All rights reserved.
//

#ifndef HuffManHeader_hpp
#define HuffManHeader_hpp

#include <stdio.h>
#include "HuffTree.hpp"
class HuffManHeader {
public:
    char *values;
    int count;
    HuffTree* tree;
    short *valueCodes;
    char *valueCodesSize;
    int *valueCounts;
    HuffManHeader(const char* path, bool wantEncode);
    char getCharForIndex(int index);
    int getIdentifierForIndex(int index);
    int getSizeOfHeader();
};

#endif /* HuffManHeader_hpp */
