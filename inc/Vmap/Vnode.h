#ifndef VNODE_H
#define VNODE_H

#include<string>

using std::string;

template<typename T>
class Vnode{

            public:

                    T key;
                    int index;                
                    Vnode<T> *next;

                    Vnode(T k,int ix):key(k),index(ix),next(nullptr){}
};

#endif
