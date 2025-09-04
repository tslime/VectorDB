#ifndef VERTEX_H
#define VERTEX_H

#include<vector>
#include<cmath>

using std::vector;
using std::sqrt;

class Vertex{
            public:
                int vdb_index;
                int level;
                vector<vector<int>> layers;

                Vertex():vdb_index(-1),level(-1),layers(0){}
                Vertex(int v_index,int l,int M):vdb_index(v_index),level(l+1),layers(l+1){}
};

#endif