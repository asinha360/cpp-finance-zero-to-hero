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

        std::pair<double, double> price_call(){

            double payoff_sum = 0.0;
            double payoff_sq_sum = 0.0;

            for( int i = 0; i < _N; i++){
                std::vector<double> sim_vec = _simulator.simulate_path();
                double p = std::max(sim_vec.back() - _K, 0.0);
                payoff_sum += p;
                payoff_sq_sum += p * p;
            }
            double variance = (payoff_sq_sum / _N) - ( (payoff_sum / _N) * (payoff_sum / _N));
            double stddev    = sqrt(variance);
            return {(payoff_sum / _N) * std::exp( -_r * _T), stddev * std::exp( -_r * _T)};
        }

    private:
        double _K, _r, _T;
        int _N;
        GBMSimulator _simulator;
};

#endif