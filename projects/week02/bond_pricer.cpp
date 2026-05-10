#include <iostream>
#include <iomanip>
#include <cmath>

double couponValue(double F, double r){

    return F * r;

}

double PV(double F, double y, int n){
    
    return F / std::pow(1.0 + y, n);

}

int main(){

    double F;
    double r;
    double y;
    int n;
    double sumP = 0;

    std::cout   << "Enter Face Value: ";
    std::cin    >> F;
    std::cout   << "Enter Rate of Return: ";
    std::cin    >> r;
    std::cout   << "Enter Yield: ";
    std::cin    >> y;

    if (y == -1.0){
        std::cerr << "Error: y cannot be -1 (division by zero)\n";
        return 1;
    }

    std::cout   << "Enter Time Period: ";
    std::cin    >> n;

    if (n <= 0){
        std::cerr << "Error: n must be greater than 0 for sensible bond price calculation (time period must be positive)\n";
        return 1;
    }

    double C = couponValue(F, r);

    for (int i = 1; i <= n; i++){
        double P = PV(C, y, i);
        sumP = sumP + P;
    }

    sumP = sumP + PV(F, y, n);

    std::cout << std::fixed << std::setprecision(2) << sumP << "\n";
    return 0;
}