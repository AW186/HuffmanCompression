//
//  BitReader.hpp
//  HuffMan
//
//  Created by Zihao Arthur Wang [STUDENT] on 11/27/19.
//  Copyright © 2019 Zihao Arthur Wang [STUDENT]. All rights reserved.
//

#ifndef BitReader_hpp
#define BitReader_hpp

#include <stdio.h>

class BitReader {
    int fileFd;
    ssize_t offset;
    int bitOffset;
    unsigned char buffer;
public:
    BitReader(int fileFd);
    int bread();
};
#endif /* BitReader_hpp */
