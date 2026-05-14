#ifndef MC_PRICER_H
#define MC_PRICER_H
#include <algorithm>
#include <vector>
#include <cmath>
#include "gbm_simulator.h"

class MCPricer {
    public:
        MCPricer(double S0, double K, double r, 
                 double sigma, double T, int N, 
                 int steps, int seed)
            : _K(K), _r(r), _T(T), _N(N), _simulator(S0, r, sigma, T, steps, seed)
        {

        }

        double price_call(){

            double payoff_sum = 0.0;
            

            for( int i = 0; i < _N; i++){
                std::vector<double> sim_vec = _simulator.simulate_path();
                payoff_sum += std::max(sim_vec.back() - _K, 0.0);
            }

            return (payoff_sum / _N) * std::exp( -_r * _T);
        }

    private:
        double _K, _r, _T;
        int _N;
        GBMSimulator _simulator;
};

#endif