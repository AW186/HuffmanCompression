//
//  BitWriter.hpp
//  HuffMan
//
//  Created by Zihao Arthur Wang [STUDENT] on 11/26/19.
//  Copyright © 2019 Zihao Arthur Wang [STUDENT]. All rights reserved.
//

#ifndef BitWriter_hpp
#define BitWriter_hpp

#include <stdio.h>

class BitWriter {
    int fileFd;
    ssize_t offset;
    int bitOffset;
    unsigned char buffer[8];
public:
    BitWriter(int fileFd);
    size_t bwrite(short num, char length);
    size_t bwrite(bool bit);
    void flush();
};

#endif /* BitWriter_hpp */
