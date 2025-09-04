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
            vector<Vertex> vgraph;
            vector<bool> visited_vlist;
            int entry_point;

            Vectordb<T> vector_db;
            DMinheap dmin;

            Hnsw(int s):size(s),num_vertices(0),vgraph(s),vector_db(s),visited_vlist(s),dmin(s),entry_point(0){}

            void print_hnsw(){
                if(this->num_vertices == 0)
                cout << "The hnsw graph is empty \n";
                else{
                    for(int i=0;i<this->num_vertices;i++){
                        cout << "Vertex "<< i <<" with vdb_index "<< this->vgraph[i].vdb_index << " and layers: \n";
                        for(int j=0;j<this->vgraph[i].layers.size();j++){
                            
                            if(this->vgraph[i].layers[j].size() == 0)
                            cout << "Layer "<< j << " empty \n";
                            else{
                                cout << "Layer "<< j <<" with indices: ";
                                int k = 0;
                                while(k < this->vgraph[i].layers[j].size()){
                                    cout << this->vgraph[i].layers[j][k] << " "; 
                                    k++;
                                }
                                cout << "\n";
                            }
                        }
                         cout << "\n\n";
                    }
                }
            }
            
            int random_level(){
                static thread_local mt19937 gen(std::random_device{}());
                static thread_local uniform_real_distribution<> udis(0.0,1.0);
                double ud = udis(gen);
                int num_layers = (int)floor(-log(ud)*(1/log(16)));

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

            void resize_vlist(int new_size){
                vector<bool> temp(new_size);

                for(int i=0;i<this->visited_vlist.size();i++)
                temp[i] = this->visited_vlist[i];

                this->visited_vlist = temp;
            }

            void visited_vertices(int v_index){
                if(v_index >= this->visited_vlist.size())
                this->resize_vlist(2*v_index);
                
                this->visited_vlist[v_index] = true;
            }

            Vdistance greedy_descent(int e_point,vector<float> new_v){

                int i = this->vgraph[e_point].level-1;
                int entry_vdb_index = this->vgraph[e_point].vdb_index;

                float min_dist = this->euclidean_distance(this->vector_db.db[entry_vdb_index].v,new_v);
                Vdistance e = Vdistance(e_point,min_dist);
                int temp_d;

                int recover_vdb_index;
                while(i >= 1){
                    for(int j=0;j < this->vgraph[e_point].layers[i].size();j++){
                    recover_vdb_index = this->vgraph[this->vgraph[e_point].layers[i][j]].vdb_index;
                    temp_d = this->euclidean_distance(this->vector_db.db[recover_vdb_index].v,new_v); 
                    if(temp_d < min_dist){
                        min_dist = temp_d;
                        e = Vdistance(this->vgraph[e_point].layers[i][j],min_dist);
                            }
                        }

                        i--;
                    }
                return e;
            }

            void computed_and_push(int e,int la,vector<float> new_v){
                int temp_distance = 0;
                int recover_vdb_index;

                int i = 0;
                while(i < this->vgraph[e].layers[la].size()){
                    if( !(this->visited_vlist[this->vgraph[e].layers[la][i]])){
                    this->visited_vlist[this->vgraph[e].layers[la][i]] = true;
                    recover_vdb_index = this->vgraph[this->vgraph[e].layers[la][i]].vdb_index;
                    temp_distance = this->euclidean_distance(this->vector_db.db[recover_vdb_index].v,new_v);
                    this->dmin.insert_DMinheap(this->vgraph[e].layers[la][i],temp_distance);
                    }
                    i++;
                }
            }

            DMinheap collect_vertices(Vdistance minv,vector<float> new_v,int la,int efConstruction){
                DMinheap result(this->num_vertices);
                
                this->dmin.insert_DMinheap(minv.vertex_index,minv.distance);
                this->computed_and_push(minv.vertex_index,la,new_v);

                int i = 0;
                while(i < efConstruction && this->dmin.num_elements > 0){
                    Vdistance *t = this->dmin.pop_DMinheap();
                    result.insert_DMinheap(t->vertex_index,t->distance);
                    this->computed_and_push(t->vertex_index,la,new_v);    
                    i++;
                }
    
                return result;
            }


            void fill_layers(DMinheap h,Vertex& new_v,int la,int la_M){
                
                int i = 0;
                Vdistance *e;
                while(h.num_elements > 0 && i < la_M){
                    e = h.pop_DMinheap();
                    new_v.layers[la].push_back(e->vertex_index);
                    if(this->vgraph[e->vertex_index].layers[la].size() < la_M)
                    this->vgraph[e->vertex_index].layers[la].push_back(this->num_vertices);

                    i++;
                }
            }

            void insert_hnsw(T id,vector<float> v){
                int vx_max_level = this->random_level();
                int c_max_level = 0;

                //cout << "Max layers is: "<< vx_max_level << "\n";

                Ventry<T> *temp = this->vector_db.retrieve_vectordb(id);
                if(temp != nullptr) 
                cout << "This entry already exists \n";
                else{
                    this->vector_db.insert_vectordb(id,v);
                    int index = this->vector_db.insert_pointer - 1;
                    Vertex vx = Vertex(index,vx_max_level,16);
                    if(this->num_vertices == 0){
                        this->vgraph[this->num_vertices] = vx;
                        this->num_vertices++;
                    }else{
                        int min_l = 0;
                        Vdistance min_d_v = this->greedy_descent(this->entry_point,v);

                        if(this->vgraph[min_d_v.vertex_index].layers.size() >= vx.layers.size())
                        min_l = vx.layers.size();
                        else min_l = this->vgraph[min_d_v.vertex_index].layers.size();

                        int i = 0;
                        while(i < min_l){
                            DMinheap r = this->collect_vertices(min_d_v,this->vector_db.db[this->vector_db.insert_pointer-1].v,i,100);
                            this->fill_layers(r,vx,i,16);
                            i++;
                        }

                        if(vx.layers.size() > this->vgraph[this->entry_point].layers.size())
                        this->entry_point = this->num_vertices - 1;
                    
                        this->vgraph[this->num_vertices] = vx;
                        this->num_vertices++;
                    }
                }
            }
};



int main(){
    
    int n;
    cout << "Give me the size of your graph \n";
    cin >> n;
    Hnsw<string> vg(n);
    cout << "\n";

    vector<float> t1 = vg.vector_db.vector_generator_3D(0.0f,1.0f);

    vg.insert_hnsw("coco",t1);

    vector<float> t2 = vg.vector_db.vector_generator_3D(0.0f,1.0f);

    vg.insert_hnsw("toto",t2);

    vector<float> t3 = vg.vector_db.vector_generator_3D(0.0f, 1.0f);
    
    vg.insert_hnsw("lulu", t3);


    cout << "\n";
    vg.print_hnsw();
    cout << "\n";

    //vg.vector_db.print_vectordb();

    //cout << "\n";
}
