#include <iostream>
#include "mc_pricer.h"

int main () {

    MCPricer mc_pricer ( 100, 100, 0.05, 0.2, 1, 100000 );

    double price = mc_pricer.price_call();

    std::cout << price << '\n';

    return 0;
}