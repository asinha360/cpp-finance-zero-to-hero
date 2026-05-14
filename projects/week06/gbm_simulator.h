#ifndef GBM_SIMULATOR_H
#define GBM_SIMULATOR_H

#include <cmath>
#include <vector>
#include "normal_sampler.h"

class GBMSimulator {
public:
    GBMSimulator(double S0, double r, double sigma,
                 double T, int steps, unsigned int seed)
        : _S0(S0), _r(r), _sigma(sigma), _T(T), _steps(steps), _sampler(seed, 0.0, 1.0)

    {

    }

    std::vector<double> simulate_path(){

        std::vector<double> S_vec; 
        S_vec.reserve(_steps + 1);
        S_vec.push_back(_S0);
        double dt = _T / _steps;
        
        for ( int i = 0 ; i < _steps ; i++) {
            S_vec.push_back ( S_vec [i] * std::exp ( ( _r - ( _sigma * _sigma ) / 2 ) * ( dt ) + ( _sigma * std::sqrt ( dt ) * _sampler.draw())));
        }

        return S_vec;

    };

private:
    double _S0, _r, _sigma, _T;
    int _steps;
    NormalSampler _sampler;
};

#endif