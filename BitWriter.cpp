//
//  BitWriter.cpp
//  HuffMan
//
//  Created by Zihao Arthur Wang [STUDENT] on 11/26/19.
//  Copyright © 2019 Zihao Arthur Wang [STUDENT]. All rights reserved.
//

#include "BitWriter.hpp"
#include <unistd.h>
#include <math.h>
#include <string.h>

BitWriter::BitWriter(int fileFd) {
    this->fileFd = fileFd;
    bitOffset = 0;
}
size_t BitWriter::bwrite(short num, char length) {
    for(int index = 0; index < length; index++) {
        bwrite(num >= pow(2, length-index-1));
        num -= num >= pow(2, length-index-1) ? pow(2, length-index-1) : 0;
    }
    return 0;
}
unsigned char bitsToByte(const unsigned char byte[8]) {
    unsigned char value = 0;
    for(int index = 0; index < 8; index++) {
        value += byte[index] == 1 ? pow(2, 7-index) : 0;
    }
    return value;
}
void BitWriter::flush() {
    unsigned char byte = bitsToByte(this->buffer);
    write(fileFd, &byte, 1);
    bzero(buffer, 8);
    bitOffset = 0;
}
size_t BitWriter::bwrite(bool bit) {
    buffer[bitOffset] = bit ? 1 : 0;
    bitOffset++;
    if (bitOffset >= 8) {
        unsigned char byte = bitsToByte(this->buffer);
        write(fileFd, &byte, 1);
        bzero(buffer, 8);
        bitOffset = 0;
    }
    return 0;
}
