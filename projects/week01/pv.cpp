#include <iostream>
#include <iomanip>
#include <cmath>

int main() {

    double FV = 1000;
    double r  = 0.05;
    int n     = 3;

    if (r == -1.0){
        std::cerr << "Error: r cannot be -1 (division by zero)\n";
        return 1;
    }

    double PV = FV / std::pow(1.0 + r, n);

    std::cout << std::fixed << std::setprecision(2) << PV << "\n";
    return 0;

}