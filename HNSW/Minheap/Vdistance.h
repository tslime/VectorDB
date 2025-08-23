#ifndef VDISTANCE_H
#define VDISTANCE_H

#include<vector>

class Vdistance{
            public:
                int index;
                float distance;

                Vdistance():index(-1),distance(-1){}
                Vdistance(int i,float d):index(i),distance(d){}
                    
};

#endif