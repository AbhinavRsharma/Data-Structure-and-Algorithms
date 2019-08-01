#include<iostream>
#include<stdlib.h>

class node{
    public:
        int data;
        node* next;
};

node* new_node(int data)
{
    node* new_node = new node();
    new_node->data = data;
    new_node->next = NULL;
}

void push(int data, node** top)
{
    node* temp = new_node(data);
    temp->next = *top;
    *top = temp;
}

int pop(node** top)
{
    if(*top)
    {
        int temp = (*top)->data;
        *top = (*top)->next;
        return temp;
    }
    return -1;
}

int main() 
{
    int n, max=0;
    std::cin >> n;

    int* arr = (int*)malloc(n*sizeof(int));
    int* left_len = (int*)malloc(n*sizeof(int));
    int* right_len = (int*)malloc(n*sizeof(int));
    
    for (int i = 0; i < n; i++)
        std::cin>> arr[i];

    node* stack = NULL;

    int i=0, temp;
    while(i<n)
    {
        if(stack != NULL)
        {
            while(arr[i]<arr[stack->data] && stack!=NULL)
            {
                temp = pop(&stack);
                left_len[temp] = i-temp-1;
            }       
        }
        if(i==n-1)
        {
            while(stack != NULL)
            {
                temp = pop(&stack);
                left_len[temp] = i-temp;
            }
            left_len[n-1] = 0;
        }
        push(i,&stack);
        i++;
    }

    stack = NULL;
    i=n-1;
    while(i>=0)
    {
        if(stack != NULL)
        {
            while(arr[i]<arr[stack->data] && stack!=NULL)
            {
                temp = pop(&stack);
                right_len[temp] = temp-i-1;
            }       
        }
        if(i==0)
        {
            while(stack != NULL)
            {
                temp = pop(&stack);
                right_len[temp] = temp;
            }
            right_len[0] = 0;
        }
        push(i,&stack);
        i--;
    }

    for(int i=0; i<n; i++)
    {
        if(max<(arr[i]*(left_len[i]+right_len[i]+1)))
            max = arr[i]*(left_len[i]+right_len[i]+1);
    }
    std::cout<<max;
    
    return 0;
}