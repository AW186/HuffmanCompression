//
//  HuffTree.cpp
//  HuffMan
//
//  Created by Zihao Arthur Wang [STUDENT] on 11/26/19.
//  Copyright © 2019 Zihao Arthur Wang [STUDENT]. All rights reserved.
//

#include "HuffTree.hpp"
#include "HuffManHeader.hpp"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ArrayList.hpp"
void sortFirstTwoFromSmall(HuffTree** nodes, size_t size);

HuffTree::HuffTree(char *value, short *codes, char *codeSizes, int count) {
    if(count > 1) {
        ArrayList<char> *leftValuesList = new ArrayList<char>();
        ArrayList<short> *leftCodesList = new ArrayList<short>();
        ArrayList<char> *leftCodeSizesList = new ArrayList<char>();
        int leftSize = 0;
        ArrayList<char> *rightValuesList = new ArrayList<char>();
        ArrayList<short> *rightCodesList = new ArrayList<short>();
        ArrayList<char> *rightCodeSizesList = new ArrayList<char>();
        int rightSize = 0;
        for (int index = 0; index < count; index++) {
            if (codes[index] >= pow(2, codeSizes[index]-1)) {
                rightValuesList->append(value[index]);
                rightCodesList->append(codes[index]-pow(2, codeSizes[index]-1));
                rightCodeSizesList->append(codeSizes[index]-1);
                rightSize++;
            } else {
                leftValuesList->append(value[index]);
                leftCodesList->append(codes[index]);
                leftCodeSizesList->append(codeSizes[index]-1);
                leftSize++;
            }
        }
        leftTree = new HuffTree(leftValuesList->toArray(),
                            leftCodesList->toArray(),
                            leftCodeSizesList->toArray(),
                            leftSize);
        rightTree = new HuffTree(rightValuesList->toArray(),
                            rightCodesList->toArray(),
                            rightCodeSizesList->toArray(),
                            rightSize);
        
    } else {
        this->value = *value;
    }
}

HuffTree::HuffTree(HuffTree** nodes, size_t size) {
    if(size > 2) {
        sortFirstTwoFromSmall(nodes, size);
        HuffTree* newNode = new HuffTree(nodes[0], nodes[1]);
        nodes[0] = newNode;
        for (int index = 2; index < size; index++) {
            nodes[index-1] = nodes[index];
        }
        HuffTree* tree = new HuffTree(nodes, size-1);
        copy(tree);
    } else if (size == 2) {
        HuffTree* tree = new HuffTree(nodes[0], nodes[1]);
        copy(tree);
    } else {
        copy(nodes[0]);
    }
}

HuffTree::HuffTree(char *values, int *counts, size_t size) {
    if(size > 2) {
        HuffTree** leaves = (HuffTree **)malloc(size*sizeof(HuffTree *));
        for (int index = 0; index < size; index++) {
            leaves[index] = new HuffTree(values[index], counts[index]);
        }
        sortFirstTwoFromSmall(leaves, size);
        HuffTree* newNode = new HuffTree(leaves[0], leaves[1]);
        leaves[0] = newNode;
        for (int index = 2; index < size; index++) {
            leaves[index-1] = leaves[index];
        }
        HuffTree* tree = new HuffTree(leaves, size-1);
        copy(tree);
    } else if (size == 2) {
        HuffTree* tree = new HuffTree(new HuffTree(values[0], counts[0]), new HuffTree(values[1], counts[1]));
        copy(tree);
    } else {
        this->value = values[0];
        this->count = counts[0];
    }
}

void HuffTree::copy(HuffTree *tree) {
    this->leftTree = tree->leftTree;
    this->rightTree = tree->rightTree;
    this->count = tree->count;
    this->value = tree->value;
}

void sortFirstTwoFromSmall(HuffTree** nodes, size_t size) {
    for (int index = 0; index < 2; index++) {
        int smallest = index;
        for (int key = index+1; key < size; key++) {
            smallest = nodes[smallest]->count < nodes[key]->count ? smallest : key;
        }
        HuffTree* buffer = nodes[smallest];
        nodes[smallest] = nodes[index];
        nodes[index] = buffer;
    }
}

HuffTree::HuffTree(char value, int count) {
    this->value = value;
    this->count = count;
}

HuffTree::HuffTree(HuffTree* treeOne, HuffTree* treeTwo) {
    if (treeOne->count > treeTwo->count) { //small tree left
        leftTree = treeTwo;
        rightTree = treeOne;
    } else {
        leftTree = treeOne;
        rightTree = treeTwo;
    }
    count = leftTree->count+rightTree->count;
}

void encode(short *codes, char *codeSizes, int count, bool isLeft) {
    for (int index = 0; index < count; index++) {
        short plus = (isLeft ? 0 : 1)*pow(2, codeSizes[index]);
        codes[index] += plus;
        codeSizes[index]++;
    }
}

void HuffTree::getEncodeValues(char **values, short **codes, char **codeSizes, int *count) {
    if(leftTree != nullptr) {
        char *leftValues;
        short *leftCodes;
        char *leftCodeSizes;
        int leftCount;
        leftTree->getEncodeValues(&leftValues, &leftCodes, &leftCodeSizes, &leftCount);
        char *rightValues;
        short *rightCodes;
        char *rightCodeSizes;
        int rightCount;
        rightTree->getEncodeValues(&rightValues, &rightCodes, &rightCodeSizes, &rightCount);
        encode(leftCodes, leftCodeSizes, leftCount, true);
        encode(rightCodes, rightCodeSizes, rightCount, false);
        char *sumValues = (char *)malloc(sizeof(char)*(rightCount+leftCount));
        short *sumCodes = (short *)malloc(sizeof(short)*(rightCount+leftCount));
        char *sumCodeSizes = (char *)malloc(sizeof(char)*(rightCount+leftCount));
        memcpy(sumValues, leftValues, leftCount*sizeof(char));
        memcpy(sumValues+leftCount, rightValues, rightCount*sizeof(char));
        memcpy(sumCodes, leftCodes, leftCount*sizeof(short));
        memcpy(sumCodes+leftCount, rightCodes, rightCount*sizeof(short));
        memcpy(sumCodeSizes, leftCodeSizes, leftCount*sizeof(char));
        memcpy(sumCodeSizes+leftCount, rightCodeSizes, rightCount*sizeof(char));
        *values = sumValues;
        *codes = sumCodes;
        *codeSizes = sumCodeSizes;
        *count = leftCount+rightCount;
    } else {
        *values = (char *)malloc(sizeof(char));
        **values = this->value;
        *codes = (short *)malloc(sizeof(short));
        **codes = 0;
        *codeSizes = (char *)malloc(sizeof(char));
        **codeSizes = 0;
        *count = 1;
    }
}

char HuffTree::getValueForCode(short code, char length) {
    if (this->leftTree == nullptr) {
        return this->value;
    }
    return code > pow(2, length-1) ?
    this->rightTree->getValueForCode(code-pow(2, length-1), length-1) :
    this->leftTree->getValueForCode(code, length-1);
}



















