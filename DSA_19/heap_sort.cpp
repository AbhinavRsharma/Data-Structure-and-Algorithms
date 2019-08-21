#include<iostream>
#include<stdlib.h>
using namespace std;
class max_heap{
    public:
        int* heap;
        int heap_size;

        int parent(int i){
            return (i-1)/2;
        }

        int left(int i){
            return 2*i+1;
        }

        int right(int i){
            return 2*i+2;
        }

        void heapify(int i){
            int max_i;
            if(left(i)<heap_size){
                if(heap[left(i)]>heap[i])
                    max_i = left(i);
                else max_i = i;

                if(right(i)<heap_size && heap[right(i)]>heap[max_i])
                    max_i = right(i);

                if(max_i == i)
                    return;
                int t = heap[max_i];
                heap[max_i] = heap[i];
                heap[i] = t;

                 heapify(max_i);
            }
            return;
        }

        void build_max_heap(){
            for(int i = parent(heap_size-1); i>=0; i--)
            heapify(i);
        }

        void heap_sort(){
            build_max_heap();
            int n = heap_size;
            while(heap_size>1){
                int t = heap[0];
                heap[0] = heap[heap_size-1];
                heap[heap_size-1] = t;
                heap_size--;
                heapify(0);
            }
            heap_size = n;
        }
};



int main(){
    max_heap a;
    cout<< "Enter no. of elements : ";
    cin>> a.heap_size;

    a.heap = (int*)malloc(a.heap_size*sizeof(int));
    cout<< "Enter elements :  "<<endl;

    for (int i = 0; i < a.heap_size; i++)
        cin>> a.heap[i];

    a.heap_sort();

    for (int i = 0; i < a.heap_size; i++)
        cout<< a.heap[i];
    return 0;
}
