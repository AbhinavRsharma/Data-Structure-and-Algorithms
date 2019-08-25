#include<iostream>
#include<stdlib.h>
#include<complex>
#include<math.h>
#include<iomanip>
#define PI 3.141592653589793238462643383

using namespace std;
typedef complex<long double> cd;

cd* fft(cd* a, long int n){
    if(n == 1){
        cd* y = (cd*)malloc(2*sizeof(cd));
        y[0] = a[0];
        y[1] = a[0];
        return y;
    }
    long double theta = (long double)PI/(long double)n;
    cd w_2n(cos(theta), sin(theta));
    
    cd w((long double)1.0,(long double)0.0);
    cd*  y = (cd*)malloc(2*n*sizeof(cd));
    cd*  a0 = (cd*)malloc((n/2)*sizeof(cd)); 
    cd*  a1 = (cd*)malloc((n/2)*sizeof(cd));

    for(long int i=0;i<n/2;i++){
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    cd* y0 = fft(a0, n/2);
    cd* y1 = fft(a1, n/2);

    for(long int i=0;i<n;i++){
        y[i] = y0[i] + w*y1[i];
        y[i+n] = y0[i] - w*y1[i];
        w = w*w_2n;
    }
    free(a0);
    free(a1);
    free(y0);
    free(y1);
    return y;
    
}

cd* inv_dft(cd* a, long int n){
    if(n == 1){
        cd* y = (cd*)malloc(sizeof(cd));
        y[0] = a[0];
        return y;
    }
    long double theta = 2.0*(long double)PI/(long double)n;
    cd w_n(cos(theta), sin(-theta));
    
    cd w((long double)1.0,(long double)0.0);
    cd*  y = (cd*)malloc(n*sizeof(cd));
    cd*  a0 = (cd*)malloc((n/2)*sizeof(cd)); 
    cd*  a1 = (cd*)malloc((n/2)*sizeof(cd));

    for(long int i=0;i<n/2;i++){
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    cd* y0 = inv_dft(a0, n/2);
    cd* y1 = inv_dft(a1, n/2);

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
        cd* b = (cd*)malloc(N*sizeof(cd));
        for(long int i=0; i<n; i++){
            cin >> re >> im;
            a[i] = cd((long double)re, (long double)im);
        }
        for(long int i=0; i<n; i++){
            cin >> re >> im;
            b[i] = cd((long double)re, (long double)im);
        }

        for(long int i=n; i<N; i++){
            a[i] = cd((long double)0.0, (long double)0.0);
            b[i] = cd((long double)0.0, (long double)0.0);
        }

        
        cd* y = (cd*)malloc(2*N*sizeof(cd));
        cd* y0 = fft(a, N);
        cd* y1 = fft(b, N);
        
        for(int i=0; i<2*N; i++)
            y[i] = y0[i]*y1[i];
        
        cd* c = inv_dft(y, 2*N);
        
        for(int i=0; i<2*N; i++)
            c[i] = c[i]*(cd(1.0/(2*(long double)N), 0.0));
        
        for(int i=0; i<2*N; i++){
            re = (long double)(((int)(real(c[i])*10000.0))/10000.0);
            im = (long double)(((int)(imag(c[i])*10000.0))/10000.0);
            c[i] = cd(re, im);
            
        }
        for(int i=0; i<2*N; i++)
            cout << fixed << setprecision(3) << c[i] <<endl;
            
        free(a);
        free(b);
        free(c);
        free(y);
        free(y0);
        free(y1);
    }

    return 0;
}
