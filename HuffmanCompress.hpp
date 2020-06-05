//
//  HuffmanComprise.hpp
//  HuffMan
//
//  Created by Zihao Arthur Wang [STUDENT] on 11/27/19.
//  Copyright © 2019 Zihao Arthur Wang [STUDENT]. All rights reserved.
//

#ifndef HuffmanCompress_hpp
#define HuffmanCompress_hpp

#include <stdio.h>

/*
    this is the function that can compress file from src to dst
*/
void huffmanCompress(const char *dst, const char *src);

/*
 this is the function that can decode file from src to dst
*/
void huffmanDecode(const char *dst, const char *src);

#endif /* HuffmanComprise_hpp */
