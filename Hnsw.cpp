#include "Vertex.h"
#include "Vdistance.h"
#include "DMinheap.h"
#include "Metadata.h"
#include "Vnode.h"
#include "Vlinkedlist.h"
#include "Vmap.h"
#include "Ventry.h"
#include "Vectordb.h"


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

template<typename T>
class Hnsw{
        public:
            int size;
            int num_vertices;
            vector<bool> vbindex_list;
            vector<Vertex> g_index;
            int entry_point;

            Vectordb<string> vector_db;
            DMinheap dmin;

            Hnsw(int s):size(s),num_vertices(0),g_index(s),vector_db(s),dmin(s),entry_point(0){}
            
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

            void insert_hnsw(T id,vector<float> v){
                int vx_max_level = this->random_level();
                int c_max_level = 0;

                Ventry<T> *temp = this->vector_db.retrieve_vectordb(id);
                if(temp == nullptr) 
                cout << "This entry already exists \n";
                else{
                    this->vdb.insert_vectordb(id,v);
                    int index = this->vdb.insert_pointer - 1;
                    Vertex vx = Vertex(index,vx_max_level,16);
                    if(this->num_vertices == 0){
                        this->g_index[this->num_vertices] = vx;
                        this->num_entries++;
                    }else{
                        int i = this->g_index[this->entry_point].level;
                        float min_dist = this->euclidean_distance(this->vector_db.db[this->g_index[this->entry_point].vdb_index].v,v);
                        Vdistance e = Vdistance(this->entry_point,min_dist);
                        int temp_d;

                        while(i >= 1){
                            for(int j=0;j < this->g_index[this->entry_point].layers[i].size();j++){
                                temp_d = this->euclidean_distance(this->vector_db.db[this->g_index[this->g_index[this->entry_point].layers[i][j]].vdb_index].v,v); 
                                if(temp_d < min_dist){
                                    min_dist = temp_d;
                                    e = Vdistance(this->g_index[this->entry_point].layers[i][j],min_dist);
                                }
                            }

                            i--;
                        }

                        dmin.insert_DMinheap(e.vertex_index,e.distance);
                        while(i < this->g_index[e.vertex_index].level){
                            int k = 0;
                            while(k < this->g_index[e.vertex_index].layers[i].size() ){
                                temp_d = this->euclidean_distance(this->vector_db.db[this->g_index[this->g_index[e.vertex_index].layers[i][k]].vdb_index].v,v);
                                e = Vdistance(this->g_index[e.vertex_index].layers[i][k],temp_d);
                                k++;
                            }

                            //fill-up layer
                            
                           
                           i++;
                        }


                    }
                }

                
            }
            
};

int main(){

    cout << "test \n";
}
