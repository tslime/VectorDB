#ifndef VERTEX_H
#define VERTEX_H

#include<vector>

using std::vector;

class Vertex{
            public:
                int vector_index;
                int level;
                vector<vector<int>> layers;

                Vertex():vector_index(-1),level(-1),layers(0){}
                Vertex(int v_index,int l):vector_index(v_index),level(l),layers(l+1){}

};

#endif