#include <iostream>
#include <cmath>
#include <iomanip>
#include <random>
#include <cassert>
#include <vector>

std::vector<double> rand_vector(){
    
    std::vector<double> random_vector;
    std::mt19937 engine(123);
    std::normal_distribution<double> dist(0.0, 1.0);
    
    for (int i = 0; i < 1000000; i++){
        double x = dist(engine);
        random_vector.push_back(x);
    }
    
    return random_vector;
}

double mean(const std::vector<double>& random_vector){

    assert(!random_vector.empty() && "Mean undefined for fewer than 1 return");

    double sum = 0.0;
    
    for (const double& x: random_vector){
        sum += x; 
    }

    
    return sum / static_cast<double>(random_vector.size());
}

double sample_variance(const std::vector<double>& random_vector, double mean_val){

    assert(random_vector.size() >= 2 && "Variance undefined for fewer than 2 returns");
    
    double sum_squared_deviations = 0.0;

    for (const double& x: random_vector){
        sum_squared_deviations += (x - mean_val) * (x - mean_val);
    }

    return sum_squared_deviations / static_cast<double>((random_vector.size() - 1));
}

double standard_deviation(const std::vector<double>& random_vector, double mean_val){

    return std::sqrt(sample_variance(random_vector, mean_val));
}

int main(){
    std::vector<double> local_random_vector = rand_vector();
    double mean_val = mean(local_random_vector);
    double std_dev = standard_deviation(local_random_vector, mean_val);

    assert(mean_val > -0.005 && mean_val < 0.005);
    assert(std_dev > 0.995 && std_dev < 1.005);

    double lower = -4.0;
    double bin_width = 0.5;
    int num_bins = 16;

    std::vector<int> counts(num_bins, 0);

    for (const double& x: local_random_vector){
        int bin_index = static_cast<int>(((x - lower) / bin_width));
        if (bin_index < 0){
            bin_index = 0;
        } else if(bin_index >= num_bins) {
            bin_index = num_bins - 1;
        }
        counts[bin_index]++;
    }

    for (int i = 0; i < num_bins; i++){
        double left_edge = lower + i * bin_width;
        int num_stars = counts[i] / 10000;
        std::cout << std::setw(5) << left_edge << " | ";
        for (int j = 0; j < num_stars; j++) std::cout << "*";
        std::cout << "\n";
    }

    std::cout << "\n";


    std::cout << std::fixed << std::setprecision(5) << "Sample Mean: " << mean_val << std::endl;
    std::cout << std::fixed << std::setprecision(5) << "Sample Standard Deviation: " << std_dev << std::endl;
    return 0;
}