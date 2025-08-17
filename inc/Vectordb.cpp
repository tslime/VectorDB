#include "Ventry.h"
#include "Metadata.h"

#include<iostream>
#include<string>
#include<vector>


using std::cin;
using std::cout;
using std::end;
using std::string;
using std::vector;

template<typename T>
class Vectordb{
            public:
                int size;
                int num_vectors;
                vector<Ventry<T>> db;

                Vectordb(int s):db(s),num_vectors(0),size(s){}

};

int main(){

    cout << "test \n";

    exit(1);
}