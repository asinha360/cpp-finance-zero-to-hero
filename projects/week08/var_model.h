#ifndef VAR_MODEL_H
#define VAR_MODEL_H

#include <vector>
#include <utility>

std::pair<double, double> historical_VaR(const std::vector<double>& log_returns);

std::pair<double, double> parametric_VaR(double mean, double stddev);

std::pair<double, double> monte_carlo_VaR(double mean, double sigma, int N, unsigned int seed);

double exceedance_frequency(const std::vector<double>& out_of_sample_vec, double var_threshold);

#endif