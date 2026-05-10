#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

const std::vector<double> price_series = {103.5, 107.2, 105.8, 110.4, 108.9, 113.6, 111.2, 116.0, 114.5, 119.3
};

std::vector<double> returns_vector(const std::vector<double>& prices){
    std::vector<double> local_returns;
    
    for (int i = 1; i < (int)prices.size(); i++){
        
        double r = (prices[i] - prices[i - 1]) / prices[i - 1];          
        local_returns.push_back(r);
    }

    return local_returns;

}

double mean(const std::vector<double>& returns){

    if ((int)returns.size() <= 0) {
        std::cerr << "Error: mean undefined for fewer than 1 return\n";
        return 0.0;
    }
    double sum = 0.0;
    
    for (int i = 0; i < (int)returns.size(); i++){
        sum += returns[i];
    }
    
    return sum / returns.size();
}

double sample_variance(const std::vector<double>& returns, double mean_val){

    if ((int)returns.size() <= 1) {
        std::cerr << "Error: variance undefined for fewer than 2 returns\n";
        return 0.0;
    }
    double sum_squared_deviations = 0.0;

    for (int i = 0; i < (int)returns.size(); i++){
        sum_squared_deviations += (returns[i] - mean_val) * (returns[i] - mean_val);
    }

    return sum_squared_deviations / (returns.size() - 1.00);
}

double standard_deviation(const std::vector<double>& returns, double mean_val){

    return std::sqrt(sample_variance(returns, mean_val));
}

int main(){

    std::vector<double> ret_vec = returns_vector(price_series);
    double returns_mean = mean(ret_vec);

    std::cout << "Mean: " << std::fixed << std::setprecision(4) << returns_mean << "\n";
    std::cout << "Variance: " << std::fixed << std::setprecision(4) << sample_variance(ret_vec, returns_mean) << "\n";
    std::cout << "Standard Deviation: " << std::fixed << std::setprecision(4) << standard_deviation(ret_vec, returns_mean) << "\n";
}