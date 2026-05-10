#include <iostream>
#include <iomanip>
#include <cmath>

double bondPrice(double F, double r, double y, int n) {

    if (y == -1.0){
        std::cerr << "Error: y cannot be -1 (division by zero)\n";
        return 1;
    }

    if (n <= 0){
        std::cerr << "Error: n must be greater than 0 for sensible bond price calculation (time period must be positive)\n";
        return 1;
    }

    double price = 0.00;
    double C = F * r;

    for (int i = 1; i <= n; i++) {
        double P = C / std::pow(1.0 + y, i);
        price += P;
    }
    price += (F / std::pow(1.0 + y, n));
    return price;
}

double ytm(double market_price, double F, double r, int n){
    double low = 0.0;
    double high = 1.0;
    double mid = 0.0;

    while (high - low >= 1e-7){
        mid = (low + high) / 2;
        double f_mid = bondPrice(F, r, mid, n) - market_price;
        if (f_mid > 0){
            low = mid;
        } else {
            high = mid;
        }
    }
    return mid;
}

int main(){

    double F;
    double r;
    int n;
    double market_price;

    std::cout   << "Enter Face Value: ";
    std::cin    >> F;
    std::cout   << "Enter Rate of Return: ";
    std::cin    >> r;
    std::cout   << "Enter Time Period: ";
    std::cin    >> n;
    std::cout   << "Enter Market Price: ";
    std::cin    >> market_price;

    double y = ytm(market_price, F, r, n);

    std::cout << std::fixed << std::setprecision(2) << "The Yield to Maturity is: " << y << "\n";
    return 0;
}