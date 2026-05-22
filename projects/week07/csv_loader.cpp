#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <cassert>

std::vector<double> log_returns(const std::vector<double>& price_vec){
    std::vector<double> returns_vec {};
    for (int i = 0; i < static_cast<int>(price_vec.size()) - 1; i++){
        
        returns_vec.push_back(std::log(price_vec[i+1] / price_vec[i]));

    }
    return returns_vec;
}

double mean(const std::vector<double>& returns){

    assert(!returns.empty() && "Error: mean undefined for fewer than 1 return\n");
    
    double sum = 0.0;
    
    for (int i = 0; i < (int)returns.size(); i++){
        sum += returns[i];
    }
    
    return sum / returns.size();
}

double sample_variance(const std::vector<double>& returns, double mean_val){

    assert(returns.size() >= 2 && "Variance undefined for fewer than 2 returns\n");

    double sum_squared_deviations = 0.0;

    for (int i = 0; i < (int)returns.size(); i++){
        sum_squared_deviations += (returns[i] - mean_val) * (returns[i] - mean_val);
    }

    return sum_squared_deviations / (returns.size() - 1.00);
}

double standard_deviation(const std::vector<double>& returns, double mean_val){

    return std::sqrt(sample_variance(returns, mean_val));
}

int main() {

    std::ifstream file("data/prices.csv");
    std::string line;
    
    std::getline( file, line );

    std::vector<double> price_vec;

    while (std::getline( file, line ) ) {

        size_t pos = line.find( ',' );

        if ( pos == std::string::npos ) {
        
            std::cerr << "malformed row: " << line << "\n";
            continue;
        
        }

        std::string date = line.substr(0, pos);
        std::string price_str = line.substr(pos + 1);

        try{
        
            double price = std::stod(price_str);
            price_vec.push_back(price);
            std::cout << date << " -> " << price << "\n";
        
        }   catch (const std::invalid_argument& e){
            
            std::cerr << "malformed row: " << line << "\n";
        
        }

    }

    if (!price_vec.empty()){

        std::vector<double> log_vec = log_returns(price_vec);
        double log_mean = mean(log_vec);
        double std_dev = standard_deviation(log_vec, log_mean);

        std::cout << "Mean of Log Returns: " << log_mean << "\n" << "Standard Deviation of Log Returns: " << std_dev << "\n";

    }   else{

        std::cerr << "Error: Division by 0" << "\n";
        return 1;

    }

    return 0;

}