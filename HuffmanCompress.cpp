//
//  HuffmanComprise.cpp
//  HuffMan
//
//  Created by Zihao Arthur Wang [STUDENT] on 11/27/19.
//  Copyright © 2019 Zihao Arthur Wang [STUDENT]. All rights reserved.
//

#include "HuffmanCompress.hpp"
#include "HuffManHeader.hpp"
#include "HuffTree.hpp"
#include "BitWriter.hpp"
#include "BitReader.hpp"
extern "C" {
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
}

void huffmanCompress(const char *dst, const char *src) {
    HuffManHeader *header = new HuffManHeader(src, true);
    int dstfd;
    if ((dstfd = open(dst, O_WRONLY | O_CREAT | O_TRUNC), 0777) < 0) {
        perror("can't open the file");
        exit(-1);
    }
    int contentSize = header->tree->count;
    short headerLength = header->count;
    write(dstfd, &headerLength, sizeof(headerLength));
    for (int index= 0; index < header->count; index++) {
        write(dstfd, &header->values[index], sizeof(char));
        write(dstfd, &header->valueCodes[index], sizeof(short));
        write(dstfd, &header->valueCodesSize[index], sizeof(char));
    }
    write(dstfd, &contentSize, sizeof(contentSize));
    int srcfd;
    if ((srcfd = open(src, O_RDONLY)) < 0) {
        perror("can't open the file");
        exit(-1);
    }
    BitWriter *writter = new BitWriter(dstfd);
    char character;
    int index = 0;
    while(read(srcfd, &character, 1) > 0) {
        for(int index = 0; index < header->count; index++) {
            if(header->values[index] == character) {
                writter->bwrite(header->valueCodes[index], header->valueCodesSize[index]);
            }
        }
    }
    writter->flush();
    close(srcfd);
    close(dstfd);
}
void huffmanDecode(const char *dst, const char *src) {
    HuffManHeader *header = new HuffManHeader(src, false);
    int srcfd;
    if ((srcfd = open(src, O_RDONLY)) < 0) {
        perror("can't open the file");
        exit(-1);
    }
    int dstfd;
    if ((dstfd = open(dst, O_WRONLY | O_CREAT | O_TRUNC), 0777) < 0) {
        perror("can't open the file");
        exit(-1);
    }
    lseek(srcfd, header->count*4+2, SEEK_SET);
    int contentSize;
    read(srcfd, &contentSize, sizeof(contentSize));
    BitReader *reader = new BitReader(srcfd);
    HuffTree *node = header->tree;
    int bit;
    int index = 0;
    while((bit = reader->bread()) >= 0) {
        node = bit == 0 ? node->leftTree : node->rightTree;
        if (node->leftTree == NULL) {
            write(dstfd, &node->value, 1);
            node = header->tree;
            if(++index >= contentSize) {
                break;
            }
        }
    }
    close(dstfd);
    close(srcfd);
}

















