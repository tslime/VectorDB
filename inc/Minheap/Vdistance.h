#ifndef VDISTANCE_H
#define VDISTANCE_H

#include<vector>

class Vdistance{
            public:
                int vertex_index;
                float distance;

                Vdistance():vertex_index(-1),distance(-1){}
                Vdistance(int i,float d):vertex_index(i),distance(d){}
                    
};

#endif