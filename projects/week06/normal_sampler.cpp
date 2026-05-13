#include <iostream>
#include "normal_sampler.h"

int main(){
    NormalSampler n(123, 0.0, 1.0);
    for(int i = 0; i < 5; i++){
        std::cout << n.draw() << std::endl;
    }

    NormalSampler n2(124, 0.0, 1.0);
    std::cout << n2.draw() << std::endl;

    return 0;
}