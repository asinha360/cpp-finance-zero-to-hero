#ifndef CSV_LOADER_H
#define CSV_LOADER_H

#include <string>
#include <vector>

std::vector<double> log_returns(const std::vector<double>& price_vec);

double mean(const std::vector<double>& returns);

double sample_variance(const std::vector<double>& returns, double mean_val);

double standard_deviation(const std::vector<double>& returns, double mean_val);

std::vector<double> load_prices(const std::string& filepath);

#endif