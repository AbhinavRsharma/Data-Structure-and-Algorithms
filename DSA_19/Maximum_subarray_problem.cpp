#include<iostream>
#include<stdlib.h>

      // // Here we use divide and conquer // //

class data{
    public:
        int sum;
        int i;
        int j;
};

data* divide_n_conquer(int* arr, int i, int j)
{
    if(i == j)
    {
        data* temp = new data;
        temp->sum = arr[i];
        temp->i = i;
        temp->j = j;
        return temp;
    }
    else
    {
        data* temp = new data;

        data* t1 = divide_n_conquer(arr, i, (i+j)/2);
        data* t2 = divide_n_conquer(arr, 1+(i+j)/2, j);

        int sum_l = 0, sum_r = 0, max_sum_l = arr[(i+j)/2], max_sum_r = arr[1+(i+j)/2];
        int cross_i = (i+j)/2, cross_j = 1+(i+j)/2;
        for(int k = (i+j)/2; k>=t1->i; k--){
            sum_l += arr[k];
            if(max_sum_l < sum_l){
                max_sum_l = sum_l;
                cross_i = k;
            }
        }
        for(int k = 1+(i+j)/2; k<=t2->j; k++){
            sum_r += arr[k];
            if(max_sum_r < sum_r){
                max_sum_r = sum_r;
                cross_j = k;
            }
        }
        temp->sum = max_sum_l + max_sum_r;
        temp->i = cross_i;
        temp->j = cross_j;

        if(temp->sum < t1->sum){
            temp->sum = t1->sum;
            temp->i = t1->i;
            temp->j = t1->j;
        }
        if(temp->sum < t2->sum){
            temp->sum = t2->sum;
            temp->i = t2->i;
            temp->j = t2->j;
        }

        return temp;
    }
    
}

int main()
{
    int n;
    std::cin>> n;

    int *arr = (int*)malloc(n* sizeof(int));
    for (int i = 0; i < n; i++)
        std::cin>> arr[i];
    
    data* result = divide_n_conquer(arr, 0, n-1);

    std::cout<<"Maximum sum is :: "<< result->sum << std::endl;
    std::cout<<"Maximum subarray is between index :: "<< result->i << " to " << result->j << std::endl;

    return 0;
}
