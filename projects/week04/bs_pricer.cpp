#include <iostream>
#include <cmath>
#include <iomanip>
#include <cassert>

double compute_d1(double S, double K, double r, double sigma, double T){
    assert(sigma > 0 && T > 0);
    return (std::log(S / K) + (r + ((sigma * sigma) / 2.0)) * T) / (sigma * std::sqrt(T));
}

double compute_d2(double d1, double sigma, double T){
    return d1 - (sigma * std::sqrt(T)); 
}

double normal_pdf(double x) {
    return std::exp(-0.5 * x * x) / std::sqrt(2.0 * M_PI);
}

double normal_cdf(double x){
    return 0.5 * (1.0 + std::erf(x / std::sqrt(2.0)));
}

double blackScholesCall(double S, double K, double r, double sigma, double T){
    double d1 = compute_d1(S, K, r, sigma, T);
    double d2 = compute_d2(d1, sigma, T);
    double N_d1 = normal_cdf(d1);
    double N_d2 = normal_cdf(d2);
    
    return (S * N_d1) - (K * std::exp(-r * T) * N_d2);
}

double blackScholesPut(double S, double K, double r, double sigma, double T){
    double d1 = compute_d1(S, K, r, sigma, T);
    double d2 = compute_d2(d1, sigma, T);
    double N_d1 = normal_cdf(-d1);
    double N_d2 = normal_cdf(-d2);
    
    return (K * std::exp(-r * T) * N_d2) - (S * N_d1);
}

double delta(double S, double K, double r, double sigma, double T){
    double d1 = compute_d1(S, K, r, sigma, T);
    return normal_cdf(d1);
}

double vega(double S, double K, double r, double sigma, double T){
    double d1 = compute_d1(S, K, r, sigma, T);
    return S * std::sqrt(T) * normal_pdf(d1);
}

void runTests() {
    double S = 100, K = 100, r = 0.05, sigma = 0.2, T = 1.0;
    double C = blackScholesCall(S, K, r, sigma, T);
    assert(std::abs(C - 10.45) < 0.01);

    double P = blackScholesPut(S, K, r, sigma, T);
    assert(std::abs(C - P - (S - K * std::exp(-r * T))) < 1e-10);

    double test_S[] =       {80, 100, 120, 4000, 3, 34, 800, 900, 9999, 100, 10, 495, 5949, 209, 100, 200, 400, 49, 90, 20};
    double test_K[] =       {100, 100, 80, 2000, 1, 31, 89, 90, 1000, 10, 393, 390, 1919, 199, 80, 40, 20, 40, 50, 60};
    double test_r[] =       {0.05, 0.04, 0.03, 0.02, 0.01, 0.10, 0.30, 0.13, 0.14, 0.30, 0.99, 0.44, 0.45, 0.55, 0.21, 0.40, 0.40, 0.54, 0.23, 0.34};
    double test_sigma[] =   {0.2, 0.4, 0.3, 0.9, 0.2, 0.4, 0.1, 0.6, 0.6, 0.4, 0.5, 0.3, 0.5, 0.3, 0.2, 0.2, 0.6, 0.6, 0.7, 0.4};
    double test_T[] =       {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

    for (int i = 0; i < 20; i++){
        double C = blackScholesCall(test_S[i], test_K[i], test_r[i], test_sigma[i], test_T[i]);
        double P = blackScholesPut(test_S[i], test_K[i], test_r[i], test_sigma[i], test_T[i]);
        assert(std::abs(C - P - (test_S[i] - test_K[i] * std::exp(-test_r[i] * test_T[i]))) < 1e-10);
    }
}

int main(){

    runTests();
    
    double S;
    double K;
    double r;
    double sigma;
    double T;

    std::cout << "Stock Price: ";
    std::cin >> S;
    std::cout << "Strike Price: ";
    std::cin >> K;
    std::cout << "Risk Free Rate: ";
    std::cin >> r;
    std::cout << "Sigma: ";
    std::cin >> sigma;
    std::cout << "Time to Expiry: ";
    std::cin >> T;

    double call_price = blackScholesCall(S, K, r, sigma, T);
    double delta_val = delta(S, K, r, sigma, T);
    double vega_val = vega(S, K, r, sigma, T);

    std::cout << std::endl;
    std::cout << std::fixed << std::setprecision(2) << "Call Price: " << call_price << std::endl;
    std::cout << std::fixed << std::setprecision(2) << "Delta: " << delta_val << std::endl;
    std::cout << std::fixed << std::setprecision(2) << "Vega: " << vega_val << std::endl;
    return 0;
}