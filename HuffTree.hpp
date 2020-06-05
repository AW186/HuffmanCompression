//
//  HuffTree.hpp
//  HuffMan
//
//  Created by Zihao Arthur Wang [STUDENT] on 11/26/19.
//  Copyright © 2019 Zihao Arthur Wang [STUDENT]. All rights reserved.
//

#ifndef HuffTree_hpp
#define HuffTree_hpp

#include <stdio.h>



class HuffTree {
public:
    HuffTree* leftTree;
    HuffTree* rightTree;
    int count = 0;
    char value = '\0';
    void copy(HuffTree* tree);
    HuffTree(char *value, short *codes, char *codeSizes, int count);
    HuffTree(HuffTree* treeOne, HuffTree* treeTwo);
    HuffTree(char value, int count);
    HuffTree(char *values, int *counts, size_t size);
    HuffTree(HuffTree** nodes, size_t size);
    void getEncodeValues(char **values, short **codes, char **codeSizes, int *count);
    char getValueForCode(short code, char length);
    
};

#endif /* HuffTree_hpp */
