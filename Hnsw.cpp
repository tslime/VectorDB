#include "Vertex.h"
#include "Vdistance.h"
#include "DMinheap.h"


#include<iostream>
#include<malloc.h>
#include<vector>
#include<random>
#include<cmath>

using std::vector;
using std::cin;
using std::cout;
using std::end;
using std::floor;
using std::uniform_real_distribution;
using std::mt19937;


class Hnsw{
        public:
            int size;
            int num_vertices;
            vector<bool> vbindex_list;
            vector<Vertex> g_index;
            int entry_point;

            
            Hnsw(int s):size(s),num_vertices(0),g_index(s),entry_point(){}
            
            int random_level(){
                mt19937 gen(std::random_device{}());
                uniform_real_distribution<> udis(0.0,1.0);
                double ud = udis(gen);
                int num_layers = floor((-1)*log(ud)*(1/log(16)));

                return num_layers;
            }
            
            float euclidean_distance(vector<float> v1,vector<float> v2){
                    int temp = 0;
                    int cumulative_sum = 0;
                    for(int i=0;i<v1.size();i++){
                        temp += (v1[i] - v2[i]);
                        cumulative_sum += temp*temp; 
                    }

                    return sqrt(cumulative_sum);
            }

            void insert_hnsw(int v_index){
                int max_level = this->random_level();
                int c_max_level = 0;

                if(v_index >= (this->vbindex_list).size() || !(this->vbindex_list[v_index])){
                      Vertex v = Vertex(v_index,max_level,16);
                            if(this->num_vertices == 0){
                                this->g_index[this->num_vertices] = v;
                                this->entry_point = 0;
                                this->num_vertices++;
                            }else{
                                  c_max_level = (this->g_index[this->entry_point]).level;
                                  int i = max_level;
                                  while( c_max_level > 0){
                                    if(c_max_level > i)
                                    c_max_level--;
                                    else if(c_max_level < i)
                                         i--;
                                        else{
                                            
                                        }
                                  }

                            }
                            
                }else cout << "This vertex already exists \n";
                        
            }
            
};

int main(){

    cout << "test \n";
}
