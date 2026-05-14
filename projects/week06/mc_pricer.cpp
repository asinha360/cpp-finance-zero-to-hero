#include <iostream>
#include <cassert>
#include "mc_pricer.h"

int main () {

    MCPricer mc_pricer ( 100, 100, 0.05, 0.2, 1, 100000, 252, 42 );

    auto [price, stddev] = mc_pricer.price_call();

    double se = stddev / std::sqrt(100000.0);
    double low = price - (3 * se); double high = price + (3 * se);
    assert(10.4502 > low && 10.4502 < high);

    std::cout << price << '\n';

    return 0;
}