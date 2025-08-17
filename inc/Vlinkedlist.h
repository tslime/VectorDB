#ifndef VLINKEDLIST_H
#define VLINKEDLIST_H

#include "Vnode.h"

#include<string>

using std::string;

template<typename T>
class Vlinkedlist{

                public:
                        Vnode<T> *head;

                        Vlinkedlist():head(nullptr){}                     
};

#endif
