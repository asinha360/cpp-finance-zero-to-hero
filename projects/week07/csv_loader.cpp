#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <stdexcept>

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

        double price_sum = std::accumulate(price_vec.begin(), price_vec.end(), 0.0);
        double mean = price_sum / price_vec.size();
        std::cout << "Mean of Prices: " << mean << "\n";

    }   else{

        std::cerr << "Error: Division by 0" << "\n";
        return 1;

    }

    return 0;

}