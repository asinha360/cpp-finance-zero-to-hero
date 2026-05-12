#include <iostream>
#include <random>
#include <cmath>
#include <vector>

class NormalSampler {
public:
    NormalSampler(unsigned int seed, double mean, double stddev)
        : _engine(seed), _dist(mean, stddev)
    {
        
    }

    double draw() {
        return _dist(_engine);
    }

private:
    std::mt19937 _engine;
    std::normal_distribution<double> _dist;
};

class GBMSimulator {
public:
    GBMSimulator(double S0, double r, double sigma,
                 double T, int steps, unsigned int seed)
        : _S0(S0), _r(r), _sigma(sigma), _T(T), _steps(steps), _sampler(seed, 0.0, 1.0)

    {

    }

    std::vector<double> simulate_path(){

        std::vector<double> S_vec {};
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

int main () {

    GBMSimulator g ( 100, 0.05, 0.0, 1.0, 5, 42 );

    std::vector<double> main_vector = g.simulate_path();

    for ( double x: main_vector ){
        std::cout << x << std::endl;
    }

    return 0;

}