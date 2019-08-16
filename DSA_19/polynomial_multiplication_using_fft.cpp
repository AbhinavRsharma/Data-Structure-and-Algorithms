#include<iostream>
#include<complex>
#include<vector>
#define PI 3.1415926

using namespace std;
typedef complex<double> cd;

vector<cd> fft(vector<cd> &a, int n){
    if(n == 1){
        vector<cd> y = {a[0], a[0]};
        return y;
    }
    
    cd w_2n = polar(1.0, (double)PI/n);
    
    cd w(1.0,0.0);
    vector<cd> y(2*n);
    vector<cd> a0(n/2);
    vector<cd> a1(n/2);

    for(int i=0;i<n/2;i++){
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    vector<cd> y0 = fft(a0, n/2);
    vector<cd> y1 = fft(a1, n/2);

    for(int i=0;i<n;i++){
        y[i] = y0[i] + w*y1[i];
        y[i+n] = y0[i] - w*y1[i];
        w = w*w_2n;
    }
    return y;
}

vector<cd> inv_fft(vector<cd> &a, int n){
    if(n == 1){
        vector<cd> y = {a[0]};
        return y;
    }
    
    cd w_n = polar(1.0, -(double)2*PI/n);
    
    cd w(1.0,0.0);
    vector<cd> y(n);
    vector<cd> a0(n/2);
    vector<cd> a1(n/2);

    for(int i=0;i<n/2;i++){
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    vector<cd> y0 = inv_fft(a0, n/2);
    vector<cd> y1 = inv_fft(a1, n/2);

    for(int i=0;i<n/2;i++){
        y[i] = y0[i] + w*y1[i];
        y[i+n/2] = y0[i] - w*y1[i];
        w = w*w_n;
    }
    return y;
}

int main(){
    int n=4;
    cd w_2n = polar( 1.0, (double)PI/n);
    vector<cd> a{9,-10,7,6};
    vector<cd> b{-5,4,0,-2};

    vector<cd>y_a = fft(a, 4);
    vector<cd>y_b = fft(b, 4);

    vector<cd> y(2*n);
    for(int i=0; i<2*n; i++)
        y[i] = y_a[i] * y_b[i];

    vector<cd> c = inv_fft(y, 2*n);
    
    for(int i=0; i<2*n ;i++)
        c[i] = c[i]/cd(2*n);

    for(cd x:y_a)
        cout << x << "   ";
        cout<< endl << endl;
    for(cd x:y_b)
        cout << x << "   ";
        cout<< endl << endl;
    for(cd x:c)
        cout << x << "   ";
        cout<< endl << endl;

    return 0;
}
