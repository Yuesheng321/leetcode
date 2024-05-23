#include <iostream>
using namespace std;

double myPowDps(double x, int n) {
    if (n == 0)
    {
        return 1;
    }
    return x * myPowDps(x, n - 1);
}

double myPowBin(double x, int n) {
    if (n == 0)
    {
       return 1;
    }
    double res = myPowBin(x, n / 2);
    return n % 2 == 0 ? res * res : res * res * x;
    
}


double myPowQuick(double x, int n) {
    int res = 1;
    while(n > 0) {
        if(n % 2 == 0) {
        }
    }
}


int main() {
    cout << myPowDps(2.10000, 3) << endl;
    cout << myPowBin(2.10000, 3) << endl;

} 