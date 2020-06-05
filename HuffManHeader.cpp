//
//  HuffManHeader.cpp
//  HuffMan
//
//  Created by Zihao Arthur Wang [STUDENT] on 11/26/19.
//  Copyright © 2019 Zihao Arthur Wang [STUDENT]. All rights reserved.
//

#include "HuffManHeader.hpp"
#include "ArrayList.hpp"
#include <math.h>
extern "C" {
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
}


void getValueCounts(char *values, int *valueCounts, int count, const char* path);
void getValueLists(char **values, int *count, const char* path);

HuffManHeader::HuffManHeader(const char* path, bool wantEncode) {
    if (wantEncode) {
        getValueLists(&values, &count, path);
        int *valueCounts = (int *)malloc(sizeof(int)*count);
        getValueCounts(values, valueCounts, count, path);
        tree = new HuffTree(values, valueCounts, count);
        tree->getEncodeValues(&values, &valueCodes, &valueCodesSize, &count);
    } else {
        int fd;
        if ((fd = open(path, O_RDWR)) < 0) {
            perror("open header");
        }
        short headerLength;
        int err = read(fd, &headerLength, sizeof(headerLength));
        values          = (char *)  malloc(headerLength*sizeof(char));
        valueCodes      = (short *) malloc(headerLength*sizeof(short));
        valueCodesSize  = (char *)  malloc(headerLength*sizeof(char));
        if (err > 0) {
            for(int index = 0; index <= headerLength; index++) {
                read(fd, values+index, sizeof(char));
                read(fd, valueCodes+index, sizeof(short));
                err = read(fd, valueCodesSize+index, sizeof(char));
            }
            if (err < 0) {
                perror("read");
            }
        } else {
            perror("read");
        }
        count = headerLength;
        tree = new HuffTree(values, valueCodes, valueCodesSize, count);
    }
}

void getValueCounts(char *values, int *valueCounts, int count, const char* path) {
    int fd;
    if ((fd = open(path, O_RDWR)) < 0) {
        perror("open getValueCount");
    }
    char character;
    bzero(valueCounts, sizeof(int)*count);
    while(read(fd, &character, 1) > 0) {
        for(int index = 0; index < count; index++) {
            valueCounts[index] += values[index] == character ? 1 : 0;
        }
    }
    close(fd);
}

void getValueLists(char **values, int *count, const char* path) {
    ArrayList<char>* list = new ArrayList<char>();
    int fd;
    if ((fd = open(path, O_RDWR)) < 0) {
        perror("open getValueList");
    }
    char character;
    while(read(fd, &character, 1) > 0) {
        if (list->contains(character)) {
        }
        if (!list->contains(character)) {
            list->append(character);
        }
    }
    char *retval = (char *)malloc(list->count());
    ArrayList<char>::Node* node = list->rootNode->nextNode;
    for(int index = 0; index < list->count(); index++) {
        retval[index] = node->data;
        node = node->nextNode;
    }
    *values = retval;
    *count = list->count();
    close(fd);
}


















