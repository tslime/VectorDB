#ifndef METADATA_H
#define METADATA_H

#include<string>

using std::string;

class Metadata{
            public:
                string label;
                string source;
                int64_t timestamp;
                float score;


                Metadata(string l,string s,int64_t t,float sc):label(l),source(s),timestamp(t),score(sc){}
};

#endif