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

                Ventry():v(0),id({}),mt(nullptr){}
                Ventry(T i,vector<float> vector_representation):v(vector_representation),id(i),mt(new Ventry(" ",true)){}    
};

#endif