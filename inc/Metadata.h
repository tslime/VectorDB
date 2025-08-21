#ifndef METADATA_H
#define METADATA_H

#include<string>

using std::string;

class Metadata{
            public:
                string tag;
                //string source;
                //int64_t timestamp;
                //float score;
                bool active;


                Metadata(string t):tag(t),active(true){}
};

#endif