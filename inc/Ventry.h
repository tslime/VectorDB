#ifndef VENTRY_H
#define VENTRY_H

#include "Metadata.h"

#include<string>
#include<vector>

using std::string;
using std::vector;

template<typename T>
class Ventry{

            public:
                T id;                 
                vector<float> v;
                Metadata *mt;

                Ventry(T i,int size):v(size),id(i),mt(nullptr){}    
};

#endif