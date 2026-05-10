#include <iostream>
#include <cmath>
#include <iomanip>

double coupon_payment (double F, double r) {
    return F * r;
}

double discounted_payment (double cashflow, double y, int n) {
    return cashflow / std::pow(1.00 + y, n);
}

int main () {

    double F;
    double r;
    double y;
    int n;

    std::cout << "Face Value: ";
    std::cin >> F;
    std::cout << "Coupon Rate: ";
    std::cin >> r;
    std::cout << "Yield Rate: ";
    std::cin >> y;

    if (y == -1.00) {
        std::cerr << "The yield rate cannot be -1 (division by 0)" << std::endl;
        return 1;
    }

    std::cout << "Time Period: ";
    std::cin >> n;

    if (n <= 0) {
        std::cerr << "The time period cannot be less than or equal to 0 (contextually inaccurate)"  << std::endl;
        return 1;
    }

    double C = coupon_payment(F, r);
    double bond_price = 0.00;

    for (int i = 1; i <= n; i++) {
        bond_price += discounted_payment(C, y, i);
    }

    bond_price += discounted_payment(F, y, n);

    std::cout << std::fixed << std::setprecision(2) << "Real Bond Price: " << bond_price<< std::endl;
    return 0;
}