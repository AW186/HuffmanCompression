
//
//  ArrayList.hpp
//  AWDroper
//
//  Created by Zihao Arthur Wang [STUDENT] on 9/26/19.
//  Copyright © 2019 Zihao Arthur Wang [STUDENT]. All rights reserved.
//

#ifndef ArrayList_hpp
#define ArrayList_hpp

#include <stdio.h>
template <typename T>
class ArrayList {
public:
    class Node {
    public:
        Node* previousNode = NULL;
        Node* nextNode = NULL;
        T data;
        Node() {}
        Node(T data) {
            this->data = data;
        }
        void remove();
        void prolink(Node* node) {
            if (node != NULL) {
                node->previousNode = this;
            }
            this->nextNode = node;
        }
        void prelink(Node* node) {
            if (node != NULL) {
                node->nextNode = this;
            }
            this->previousNode = node;
        }
    };
    ~ArrayList() {
        Node* nNode;
        for(Node* node = this->rootNode; node != nullptr; node = nNode) {
            nNode = node->nextNode;
            delete node;
        }
    }
    Node* rootNode = new Node();
    void append(T data) {
        Node* node = new Node(data);
        node->prolink(this->rootNode->nextNode);
        node->prelink(this->rootNode);
    }
    bool contains(T element) {
        bool sum = false;
        for(Node* node = rootNode->nextNode; node != nullptr; node = node->nextNode) {
            sum = sum || node->data == element;
        }
        return sum;
    }
    T* toArray() {
        T *retval = (T *)malloc(sizeof(T)*count());
        int index = 0;
        for(Node* node = rootNode->nextNode; node != nullptr; node = node->nextNode) {
            retval[index++] = node->data;
        }
        return retval;
    }
    int removeAt(int index);
    int insert(T data, int index);
    int append(ArrayList<T> list);
    int insert(ArrayList<T> list, int index);
    int count() {
        int count = 0;
        for(Node* node = this->rootNode->nextNode; node != NULL; node = node->nextNode) {
            count++;
        }
        return count;
    }
    void forEach(void (*pf)(T));
    void forEachNode(void (*pf)(Node*));
};
#endif /* ArrayList_hpp */
