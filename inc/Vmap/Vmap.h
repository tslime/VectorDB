#ifndef VMAP_H
#define VMAP_H

#include "Vnode.h"
#include "Vlinkedlist.h"


#include<iostream>
#include<malloc.h>
#include<string>
#include<vector>
#include<type_traits>

using std::cin;
using std::cout;
using std::end;
using std::string;
using std::vector;
using std::is_same_v;

template<typename T>
class Vmap{
         
         public:
                int size;
                int num_indexes;
                vector<Vlinkedlist<T>> slots;

                Vmap(int s):slots(s),size(s),num_indexes(0){}
                
                void print_Vmap(){
                    if(this->num_indexes == 0)
                    cout << "The vector map is empty \n";
                    else{
                        for(int i=0;i<this->size;i++){
                            if(this->slots[i].head == nullptr)
                            cout << "This is slot " << i << " and it is empty \n";
                            else{
                                cout << "This is slot " << i << " and it contains the following: \n";
                                Vnode<T> *aux = this->slots[i].head;
                                while(aux != nullptr){
                                    cout << "Key: " << aux->key << " Index: " << aux->index << " || ";
                                    aux = aux->next;
                                }
                                cout << " \n";
                            }
                        }
                    }
                }


                int hashcode(T k){
                    int code = 0;
                    int temp = 0;

                    if constexpr(is_same_v<T,string>){
                        for(int i=0;i<k.length();i++)
                        temp += k[i] - '0';
                        
                        code = ((temp << 4)^temp)%this->size;

                    }else if constexpr(is_same_v<T,int>){
                     code = ((k << 4)^k)%this->size;    
                    }
                    
                    return code;
                }

                void resize_Vmap(){
                    Vmap<T> temp(2*this->size);

                    for(int i=0;i<this->size;i++){
                        if(this->slots[i].head != nullptr){
                            Vnode<T> *aux = this->slots[i].head;
                            while(aux != nullptr){
                                temp.insert_Vmap(aux->key,aux->index);
                                aux = aux->next;
                            }
                        }
                    }

                    this->slots = temp.slots;
                    this->size = temp.slots.size();
                }

                void insert_Vmap(T k,int ix){
                    
                    int load = ((float)this->num_indexes/(float)this->size)*100;

                    //cout << "num indexes " << this->num_indexes << "\n";
                    //cout << "this is the load "<< load << "\n";

                    if( load >= 70 )
                    this->resize_Vmap();

                    int hcode = hashcode(k);

                    if(this->slots[hcode].head == nullptr){
                        this->slots[hcode].head = new Vnode<T>(k,ix);
                        this->num_indexes++;
                    }else{
                        Vnode<T> *aux = this->slots[hcode].head;
                        bool b = (aux->key == k);
                        while(aux->next != nullptr && !b){
                            aux = aux->next;
                            if(aux->key == k)
                            b = true;
                        }

                        if(!b){
                            aux->next = new Vnode<T>(k,ix);
                            this->num_indexes++;
                        }
                        
                    }
                }

                
                void remove_Vmap(T k){
                    if(this->num_indexes > 0){
                        int hcode = hashcode(k);

                        Vnode<T> *aux = this->slots[hcode].head;
                        Vnode<T> *temp = nullptr;
                        bool b = false;
                        while(aux != nullptr && !b){
                            if(aux->key == k)
                            b = true;
                            else{
                                temp = aux;
                                aux = aux->next;
                            }
                        }

                        if(b){
                            if(temp == nullptr)
                            this->slots[hcode].head = this->slots[hcode].head->next;
                            else temp->next = aux->next;
                            this->num_indexes--;
                        }
                    }
                }


                Vnode<T> *retrieve_Vmap(T k){
                    Vnode<T> *r = nullptr;
                    bool b = false;

                    if(this->num_indexes > 0){
                        int hcode = hashcode(k);
                        Vnode<T> *aux = this->slots[hcode].head;
                        if(aux != nullptr){
                        b = (aux->key == k);
                        while(aux->next != nullptr && !b){
                            aux = aux->next;
                            b = (aux->key == k);   
                         }
                       }
                        
                        if(b)
                        r = new Vnode<T>(aux->key,aux->index);
                    }

                    return r;
                }
};      


#endif

/*
int main(){

    int n;
    cout << "Give me the size of your vector map \n";
    cin >> n;
    Vmap<string> vm(n);

    int x = 0;
    string k_e;
    int ind;
    cout << "Give me your entries: \n";
    while(x < n){
        cin >> k_e;
        cin >> ind;
        vm.insert_Vmap(k_e,ind);
        x++;
    }

    cout << "\n";

    vm.print_Vmap();

    cout << "\n";

    string d;
    Vnode<string> *result;
    while(true){
      int s = vm.num_indexes;
      cout << "Give me the entry you want to search \n";
      cin >> d;
      result = vm.retrieve_Vmap(d);
      if(result == nullptr)
      cout << "This entry does not exist \n";
      else cout << "Your value is: "<< result->index;

      cout << "\n";  
      
    }

    exit(1);
}*/