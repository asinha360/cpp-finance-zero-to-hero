#include <iostream>
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

int main(){
    NormalSampler n(123, 0.0, 1.0);
    for(int i = 0; i < 5; i++){
        std::cout << n.draw() << std::endl;
    }

    NormalSampler n2(124, 0.0, 1.0);
    std::cout << n2.draw() << std::endl;

    return 0;
}