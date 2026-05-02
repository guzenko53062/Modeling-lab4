#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

vector<double> gauss(double mean, double dev, int n) {
    vector<double> values;
    values.reserve(n);
    double u, v, s;
    
    cerr << "generating values... \n";
    
    while (values.size() < n) {
        do {
            u = 2.0 * rand() / RAND_MAX - 1.0;
            v = 2.0 * rand() / RAND_MAX - 1.0;
            s = u * u + v * v;
        } while (s > 1.0 || s == 0.0);

        double r = sqrt(-2.0 * log(s) / s);
        
        if (values.size() < n)
            values.push_back(r * v * dev + mean);
        if (values.size() < n)
            values.push_back(r * u * dev + mean);
    }
    
    cerr << "generation finished... \n";
    return values;
}
 
 
int histogram(const vector<double>& gen, double minVal, double maxVal, int cols) {
    vector<int> height(cols, 0);
    double range = maxVal - minVal;
    int before = 0, after = 0;

    for (double val : gen) {
        if (val < minVal) {
            before++;
        } else if (val >= maxVal) {
            after++;
        } else {
            int bin = static_cast<int>((val - minVal) / range * cols);
            if (bin >= cols) bin = cols - 1;
            height[bin]++;
        }
    }

    double binWidth = range / cols;
    for (int i = 0; i < cols; i++) {
        double centerX = minVal + binWidth * (i + 0.5);
        printf("%f\t%d\t%f\n", centerX, height[i], binWidth);
    }
    
    if (before + after > 0)
        printf("# values outside range: <%g (%d), >=%g (%d)\n", 
               minVal, before, maxVal, after);
    
    return 0;
}



int main() {
    srand(static_cast<unsigned>(time(NULL)));
    
    int n;
    double mean, dev;
    
    cerr << "Введите количество значений: "; cin >> n;
    cerr << "Введите mean: "; cin >> mean;
    cerr << "Введите dev: "; cin >> dev;
    
    vector<double> values = gauss(mean, dev, n);
    
    cerr << "generated " << values.size() << " values\n";
    
    double minVal = mean - 3 * dev;
    double maxVal = mean + 3 * dev;
    
    cerr << "creating histogram (range: [" << minVal << ", " << maxVal << "])... \n";
    
    histogram(values, minVal, maxVal, 30);
    
    cerr << "End.. \n";
    return 0;
}

