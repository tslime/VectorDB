#ifndef VECTORDB_H
#define VECTORDB_H

#include "Ventry.h"
#include "Metadata.h"
#include "Vnode.h"
#include "Vlinkedlist.h"
#include "Vmap.h"
#include "Metadata.h"

#include<iostream>
#include<string>
#include<vector>
#include<random>
#include<cmath>
#include<deque>
#include<algorithm>

using std::cin;
using std::cout;
using std::end;
using std::string;
using std::vector;
using std::deque;
using std::mt19937;
using std::uniform_real_distribution;
using std::find;

template<typename T>
class Vectordb{
            public:
                int size;
                int num_entries;
                int insert_pointer;
                vector<Ventry<T>> db;
                Vmap<T> imap;
                deque<int> free_indexes;

                Vectordb(int s):db(s),num_entries(0),insert_pointer(0),size(s),imap(s){}

                void print_vector(vector<float> v){
                    cout << "[";
                    for(int i=0;i<v.size();i++){
                        if(i == v.size()-1)
                        cout << v[i]  << "]";
                        else cout << v[i] << ",";
                    }
                    
                }

                void print_vectordb(){
                    if(this->num_entries == 0)
                    cout << "The vector database is empty \n";
                    else{
                        for(int i=0;i<this->size;i++){
                        if(this->db[i].v.size() == 0)
                        cout << "This is slot "<< i << " and it is empty \n";
                        else{
                            cout << "This is slot "<< i << " and it has the following entry \n";
                            cout << "id: " << (this->db[i]).id << " || vector: ";
                            this->print_vector((this->db[i]).v);
                            cout << "\n \n"; 
                          } 
                        }
                    }
                }

                void resize_vectordb(){
                    vector<Ventry<T>> temp(2*(this->size));

                    for(int i=0;i<this->size;i++)
                    temp[i] = this->db[i];

                    this->db = temp;
                    this->size = temp.size();
                }

                vector<float> vector_generator_3D(float min,float max){
                    vector<float> r(3);
                    
                    for(int i=0;i<3;i++){
                        mt19937 gen(std::random_device{}());
                        uniform_real_distribution<float> temp(min,max);
                        float u = temp(gen);
                        r[i] = u;
                    }

                    return r;
                }

                void insert_vectordb(T i,vector<float> v){ 
                    if(!(this->free_indexes.empty())){
                        int ix = (this->free_indexes).front();
                        (this->free_indexes).pop_back();
                        this->db[ix] = Ventry<T>(i,v);
                        this->imap.insert_Vmap(i,ix);
                    }else{
                        
                        if(this->insert_pointer >= this->size)
                        this->resize_vectordb();
                    
                        this->db[this->insert_pointer] = Ventry<T>(i,v);
                        this->imap.insert_Vmap(i,insert_pointer);
                        this->insert_pointer++;
                    }
                    this->num_entries++;
                }

                void remove_vectordb(T i){
                    Vnode<T> *n = this->imap.retrieve_Vmap(i);

                    if(n == nullptr)
                    cout << "This entry does not exist \n";
                    else{
                        this->db[n->index] = Ventry<T>();
                        this->free_indexes.push_back(n->index);
                        this->imap.remove_Vmap(n->key);
                        this->num_entries--;
                    }
                }

                Ventry<T> *retrieve_vectordb(T id){
                    Ventry<T> *r = nullptr;

                    Vnode<T> *temp = this->imap.retrieve_Vmap(id);
                    if(temp != nullptr)
                    r = new Ventry<T>(id,this->db[temp->index].v);

                    return r;
                }

                void update_vectordb(T id,vector<float> new_v){
                    Vnode<T> *temp = this->imap.retrieve_Vmap(id);

                    if(temp == nullptr)
                    cout << "This entry does not exist \n";
                    else this->db[temp->index].v = new_v;
                }
};

#endif

/*

int main(){

    int n;
    cout << "Give me the size of your vector DB \n";
    cin >> n;
    Vectordb<string> vdb(n);

    cout <<"Give me your entries: \n";
    int i = 0;
    string name;
    while(i < 3){
        cin >> name;
        vdb.insert_vectordb(name,vdb.vector_generator_3D(0.0f,1.0f));
        i++;
    }

    cout << "\n";


    vdb.print_vectordb();

    cout << "\n";

    vdb.imap.print_Vmap();

    cout << "\n";
    
    int y = 0;
    string id;
    while(true){
        /*
        int t = vdb.num_entries;
        cout << "Would you like to remove an entry yes=1/no=0 \n";
        cin >> y;

        if(y){
            cout << "Give me the id of the entry that you would like to remove:\n";
            cin >> id;
            vdb.remove_vectordb(id);
        }

        if(vdb.num_entries < t){
            cout << "\n";
            vdb.print_vectordb();
            cout << "\n";
            vdb.imap.print_Vmap();
        }
        
        
        
        cout <<"\n";
        cout << "Give me another entry: \n";
        cin >> name;
        Ventry<string> *aux = vdb.retrieve_vectordb(name);
        if(aux == nullptr)
        cout << "This entry does not exist \n";
        else{
            cout << "This entry's ID is: " << aux->id << " and its vector is: ";
            vdb.print_vector(aux->v);
            cout << "\n";
        } 
        cout << "\n";

        vdb.print_vectordb();

        cout << "\n";
        vdb.imap.print_Vmap();
        cout << "\n";

    }

    cout << "\n";

    exit(1);
}*/