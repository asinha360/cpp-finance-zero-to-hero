#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>

int main(){

    double FV   = 1000;
    double r    = 0.05;
    double n    = 5;

    assert(r > -1);

    double PV = FV / std::pow(1.0 + r, n);

    std::cout << "Present Value: " << std::setprecision(2) << std::fixed << PV << std::endl;
    return 0;

}