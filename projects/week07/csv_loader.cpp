#include <iostream>
#include <fstream>
#include <string>

int main() {

    std::ifstream file("data/prices.csv");
    std::string line;
    
    std::getline( file, line );

    while (std::getline( file, line ) ) {

        size_t pos = line.find( ',' );

        if ( pos == std::string::npos ) {
            std::cerr << "malformed row: " << line << "\n";
            continue;
        }

        std::string date = line.substr( 0, pos);
        std::string price = line.substr( pos + 1 );
        std::cout << date << " -> " << price << "\n";
        
    }

    return 0;

}