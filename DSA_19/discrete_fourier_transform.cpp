#include<iostream>
#include<stdlib.h>
#include<complex>
#include<math.h>
#include<iomanip>
#define PI 3.1415926535897932

using namespace std;
typedef complex<long double> cd;

cd* dft(cd* a, long int n){
    if(n == 1){
        cd* y = (cd*)malloc(sizeof(cd));
        y[0] = a[0];
        return y;
    }
    long double theta = 2.0*(long double)PI/(long double)n;
    cd w_n(cos(theta), sin(theta));
    
    cd w((long double)1.0,(long double)0.0);
    cd*  y = (cd*)malloc(n*sizeof(cd));
    cd*  a0 = (cd*)malloc((n/2)*sizeof(cd)); 
    cd*  a1 = (cd*)malloc((n/2)*sizeof(cd));

    for(long int i=0;i<n/2;i++){
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    cd* y0 = dft(a0, n/2);
    cd* y1 = dft(a1, n/2);

    for(long int i=0;i<n/2;i++){
        y[i] = y0[i] + w*y1[i];
        y[i+n/2] = y0[i] - w*y1[i];
        w = w*w_n;
    }
    free(a0);
    free(a1);
    free(y0);
    free(y1);
    return y;
    
}

int main(){
    long int t, n, N;
    long double re, im;
    cin>> t;

    while(t--){
        N=1;
        cin>> n;
        while(n>N){
                N *= 2;
        }

        cd* a = (cd*)malloc(N*sizeof(cd));
        for(long int i=0; i<n; i++){
            cin >> re >> im;
            a[i] = cd((long double)re, (long double)im);
        }

        for(long int i=n; i<N; i++)
            a[i] = cd((long double)0.0, (long double)0.0);

        cd* y = dft(a, N);
        
        for(int i=0; i<N; i++)
            cout << fixed << setprecision(3) << y[i] <<endl;
            
        free(a);
        free(y);
    }

    return 0;
}
