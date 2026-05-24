#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <utility>
#include "var_model.h"
#include "normal_sampler.h"
#include "csv_loader.h"


std::pair<double, double> historical_VaR(const std::vector<double>& returns){

    std::vector<double> returns_sorted = returns;
    std::sort(returns_sorted.begin(), returns_sorted.end());

    int n = static_cast<int>(returns_sorted.size());
    int idx_95 = (n * 5 / 100) - 1;
    int idx_99 = (n * 1 / 100) - 1;
    assert(idx_95 >= 0 && idx_99 >= 0 && "Not enough returns for VaR calculation");
    
    double hist_VaR_95 = returns_sorted[idx_95];
    double hist_VaR_99 = returns_sorted[idx_99];

    std::pair<double, double> hist_VaR_pair = {hist_VaR_95, hist_VaR_99};
    return hist_VaR_pair;

}

std::pair<double, double> parametric_VaR(double mean, double stddev){
    
    double para_VaR_95 = mean + (-1.645) * stddev;
    double para_VaR_99 = mean + (-2.326) * stddev;

    std::pair<double, double> para_VaR_pair = {para_VaR_95, para_VaR_99};
    return para_VaR_pair;
}

std::pair<double, double> monte_carlo_VaR(double mean, double sigma, int N, unsigned int seed){
    NormalSampler n(seed, mean, sigma);
    std::vector<double> mc_returns {};

    for (int i = 0; i < N; i++){
        mc_returns.push_back(n.draw());
    }

    std::sort(mc_returns.begin(), mc_returns.end());

    int n_mc = static_cast<int>(mc_returns.size());
    int idx_95 = (n_mc * 5 / 100) - 1;
    int idx_99 = (n_mc * 1 / 100) - 1;
    assert(idx_95 >= 0 && idx_99 >= 0 && "Not enough returns for VaR calculation");
    

    double mc_VaR_95 = mc_returns[idx_95];
    double mc_VaR_99 = mc_returns[idx_99];

    std::pair<double, double> mc_VaR_pair = {mc_VaR_95, mc_VaR_99};
    return mc_VaR_pair;
}

int main(){

    std::vector<double> price_vec = load_prices("data/prices.csv");
    std::vector<double> log_return_vec = log_returns(price_vec);
    double mean_val = mean(log_return_vec);
    double std_dev_val = standard_deviation(log_return_vec, mean_val);

    std::pair<double, double> hist_VaR_pair = historical_VaR(log_return_vec);
    std::pair<double, double> para_VaR_pair = parametric_VaR(mean_val, std_dev_val);
    std::pair<double, double> mc_VaR_pair = monte_carlo_VaR(mean_val, std_dev_val, 100000, 123);

    auto [hvar95, hvar99] = hist_VaR_pair;
    std::cout << "The Historical Simulation VaRs are: " << "\n";
    std::cout << "95% VaR: " << hvar95 << "  ||  " << "99% VaR: " << hvar99 << "\n";

    auto [pvar95, pvar99] = para_VaR_pair;
    std::cout << "The Parametric Simulation VaRs are: " << "\n";
    std::cout << "95% VaR: " << pvar95 << "  ||  " << "99% VaR: " << pvar99 << "\n";

    auto [mcvar95, mcvar99] = mc_VaR_pair;
    std::cout << "The Monte Carlo Simulation VaRs are: " << "\n";
    std::cout << "95% VaR: " << mcvar95 << "  ||  " << "99% VaR: " << mcvar99 << "\n";

    return 0;
}