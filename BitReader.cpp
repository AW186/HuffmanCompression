//
//  BitReader.cpp
//  HuffMan
//
//  Created by Zihao Arthur Wang [STUDENT] on 11/27/19.
//  Copyright © 2019 Zihao Arthur Wang [STUDENT]. All rights reserved.
//

#include "BitReader.hpp"
#include <math.h>
extern "C" {
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
}

BitReader::BitReader(int fileFd) {
    this->fileFd = fileFd;
    read(fileFd, &buffer, 1);
    bitOffset = 0;
}

int BitReader::bread() {
    int retval = buffer >= pow(2, 7-offset) ? 1 : 0;
    buffer -= buffer >= pow(2, 7-offset) ? pow(2, 7-offset) : 0;
    offset++;
    if(offset >= 8) {
        offset = 0;
        if(read(fileFd, &buffer, 1) <= 0) {
            return -1;
        }
    }
    return retval;
}

