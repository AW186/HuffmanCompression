//
//  ArrayList.cpp
//  AWDroper
//
//  Created by Zihao Arthur Wang [STUDENT] on 9/26/19.
//  Copyright © 2019 Zihao Arthur Wang [STUDENT]. All rights reserved.
//

#include "ArrayList.hpp"


template<typename T>
void ArrayList<T>::Node::remove(){
    if (this->nextNode != nullptr) {
        nextNode->prelink(this->previousNode);
    }
    delete this;
}

template<typename T>
int ArrayList<T>::insert(T data, int index) {
    Node* node = new Node(data);
    node->prolink(this->rootNode->nextNode);
    node->prelink(this->rootNode);
}

template<typename T>
void ArrayList<T>::forEachNode(void (*pf)(Node*)) {
    for(Node* node = rootNode->nextNode; node != nullptr; node = node->nextNode) {
        pf(node);
    }
}

template<typename T>
void ArrayList<T>::forEach(void (*pf)(T)) {
    for(Node* node = rootNode->nextNode; node != nullptr; node = node->nextNode) {
        pf(node->data);
    }
}


    
    
    
    
    
    
    











