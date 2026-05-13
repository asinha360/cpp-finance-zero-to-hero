#ifndef NORMAL_SAMPLER_H
#define NORMAL_SAMPLER_H

#include <random>

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

#endif