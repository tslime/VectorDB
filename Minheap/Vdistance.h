#ifndef VDISTANCE_H
#define VDISTANCE_H

#include<vector>

class Vdistance{
            public:
                int g_index;
                float distance;

                Vdistance():g_index(-1),distance(-1){}
                Vdistance(int i,float d):g_index(i),distance(d){}
                    
};

#endif