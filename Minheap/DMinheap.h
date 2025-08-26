#ifndef DMINHEAP_H
#define DMINHEAP_H

#include "Vdistance.h"

#include<iostream>
#include<vector>

using std::cin;
using std::cout;
using std::end;
using std::vector;

class DMinheap{
            public:
                  int size;
                  int num_elements;
                  vector<Vdistance> Minds;

                  DMinheap(int s):size(s),num_elements(0),Minds(s){}


                  void print_DMinheap(){
                    if(this->num_elements == 0)
                    cout << "Your heap is empty \n";
                    else{
                        cout << "Your distance heap contains the following: \n";
                        for(int i=0;i<this->num_elements;i++)
                        cout << Minds[i].distance << " ";

                        cout << "\n";
                    }
                  }

                  void resize_DMinheap(){
                    vector<Vdistance> temp(2*(this->size));

                    for(int i=0;i<this->size;i++)
                    temp[i] = this->Minds[i];

                    this->Minds = temp;
                    this->size = temp.size();
                  }

                  void insert_DMinheap(int ix,float d){
                    if(this->num_elements >= this->size)
                    this->resize_DMinheap();
                    
                    Vdistance vd = Vdistance(ix,d);
                    this->Minds[this->num_elements] = vd;
                    this->num_elements++;
                    this->bubbleUp(num_elements-1);
                  }

                  void bubbleUp(int num){
                    bool b = true;
                    int i;
                    while(b){
                        i = (num-1)/2;
                        if(i < 0)
                        b = false;
                        else{
                            if(this->Minds[i].distance > this->Minds[num].distance){
                            Vdistance temp = this->Minds[i];
                            this->Minds[i] = this->Minds[num];
                            this->Minds[num] = temp;
                            num = i;
                            }else b = false;
                        }
                    }
                  }

                  Vdistance* pop_DMinheap(){
                    Vdistance *r = nullptr;

                    if(this->num_elements > 0){
                        r = new Vdistance(this->Minds[0].g_index,this->Minds[0].distance);
                        this->Minds[0] = this->Minds[this->num_elements-1];
                        this->Minds[this->num_elements] = Vdistance();
                        this->num_elements--;
                        this->bubbleDown(0);
                    }

                    return r;
                  }

                void bubbleDown(int num){
                    
                    int left_child, right_child;
                    Vdistance temp;

                    bool b = true;
                    while(b){
                        left_child = 2*num + 1;
                        right_child = 2*num + 2;

                        if(left_child > this->num_elements && right_child > this->num_elements) 
                        b = false;
                        else{
                            if(right_child <= this->num_elements){
                                if(this->Minds[right_child].distance <= this->Minds[left_child].distance){
                                    if(this->Minds[right_child].distance < this->Minds[num].distance){
                                        temp = this->Minds[right_child];
                                        this->Minds[right_child] = this->Minds[num];
                                        this->Minds[num] = temp;
                                        num = right_child;
                                    }else b = false;
                                }else{
                                    if(this->Minds[left_child].distance < this->Minds[num].distance){
                                        temp = this->Minds[left_child];
                                        this->Minds[left_child] = this->Minds[num];
                                        this->Minds[num] = temp;
                                        num = left_child;
                                    }else b = false;
                                }
                            }else{
                                if(this->Minds[left_child].distance < this->Minds[num].distance){
                                    temp = this->Minds[left_child];
                                    this->Minds[left_child] = this->Minds[num];
                                    this->Minds[num] = temp;
                                    num = left_child;
                                }else b = false;
                            }
                        }
                    }
                }
};

#endif

/*
int main(){

    int n;
    cout << "Giv me the size of your distance heap \n";
    cin >> n;
    DMinheap mind(n);
    
    cout << "Give me your distances\n";
    int  i =0;
    int x;
    float d;
    while(i < n){
        cin >> x;
        cin >> d;
        mind.insert_DMinheap(x,d);
        i++;
    }
    
    cout << "\n";

    mind.print_DMinheap();

    cout << "\n";
    
    int y = 1;
    while(y){
        int k = mind.num_elements;
        cout << "Would you like to remove an entry 1=yes/no=0\n";
        cin >> y;
        if(y == 1)
        mind.pop_DMinheap();

        if(mind.num_elements < k)
        mind.print_DMinheap();
        
        cout << "\n";
    }
    
    exit(1);
}*/