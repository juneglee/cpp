#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;

// Function taking a function pointer as an argument
double compute_sum(double (*funcp)(double), double lo, double hi) {
    double sum = 0.0;

    // Add values returned by the pointed-to function '*funcp'
    int i;
    for (i = 0; i <= 100; i++) {
        // Use the function pointer 'funcp' to invoke the function
        double x = i / 100.0 * (hi - lo) + lo;
        double y = funcp(x);
        sum += y;
    }
    return sum / 101.0 * (hi - lo);
}

double square(double x) {
    return x * x;
}

void displayInBase(int64_t n, int64_t b) {
    const static std::string strNumSet
        = "0123456789ABCDEFGHIJILMNOPQRSTUVWXYZ";
    if (n > 0) {
        displayInBase(n / b, b);
        std::cout << strNumSet[n % b];
    }
}

int main(void) {
    double  sum;

    // 포인터 함수(function pointer)
    // Use standard library function 'sin()' as the pointed-to function
    sum = compute_sum(sin, 0.0, 1.0);
    printf("sum(sin): %g\n", sum);

    // Use standard library function 'cos()' as the pointed-to function
    sum = compute_sum(cos, 0.0, 1.0);
    printf("sum(cos): %g\n", sum);

    // Use user-defined function 'square()' as the pointed-to function
    sum = compute_sum(square, 0.0, 1.0);
    printf("sum(square): %g\n", sum);

    
    // 재귀함수(recursive function)
    int64_t nNum, nBase;
    cout << "Input number and base: ";
    cin >> nNum >> nBase;

    if (nBase >= 2 && nBase <= 36) {
        cout << " " << nNum << " (base 10) = ";
        displayInBase(nNum, nBase);
        cout << " (base " << nBase << ")" << endl;
    }
    else {
        cout << "The base must be in the range 2 << base << 36"
            << endl;
    }

    return 0;
}