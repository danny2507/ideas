#include <iostream>
#include <cmath>
#include <functional>
#include <algorithm>
#include <vector>
using namespace std;

// Target function f(x)
double f(double x) {
    return sin(x);
}
// Fourth order derivative
double fourth_derivative(double x) {
    return sin(x);
}
// b is the upper bound, and a is the lower bound
double approximate(function<double(double)> func, double a, double b, int n) {
    if (n % 2 != 0) {
        cerr << "n must be even for this method to work";
        return -1;
    }
    double h = (b - a)/n;
    double sum = func(a) + func(b);
    // odd terms
    for(int i = 1; i<n ; i+=2) {
        sum += 4*func(a + i*h);
    }
    // even terms
    for(int i = 2; i<n ; i+=2) {
        sum += 2*func(a + i*h);
    }

    return (h/3)*sum; 

}
double calculate_error(function<double(double)> fourthDeriv, double a, double b, int n) {
    double h = (b -a )/n;
    vector<double> derivValues;

    // evaluate the fourth derivative at each step
    for(int i =0; i<=n; ++i) {
        double x = i*h + a;
        derivValues.push_back(fourth_derivative(x));

    }
    // select the max
    double maxFourthDeriv = *max_element(derivValues.begin(), derivValues.end());
    // calc the error
    double error = -((pow(h, 4))*(b-a)*(-1)*maxFourthDeriv/180);
    return error;
}
int main() {
    double a = 0.0;   // lower bound
    double b = M_PI;  // upper bound
    int n = 100;       // number of intervals (must be even)

    double exactValue = 2.0;  // Exact value of the integral of sin(x) from 0 to π

    double approxValue = approximate(f, a, b, n);
    if (approxValue != -1) {
        cout << "The integral of sin(x) from 0.0 to pi is approximately: " << approxValue << endl;
        cout << "Error: " << calculate_error(f, a, b, n) << endl;
    }

    return 0;
}
