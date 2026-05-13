#include <iostream>
#include <vector>
#include "gbm_simulator.h"

int main () {

    GBMSimulator g ( 100, 0.05, 0.0, 1.0, 5, 42 );

    std::vector<double> main_vector = g.simulate_path();

    for ( double x: main_vector ){
        std::cout << x << std::endl;
    }

    return 0;

}