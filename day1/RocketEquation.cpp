#include <iostream>
#include <fstream>
#include <string>

int findFuel(int mass) {
    return mass / 3 - 2;
}

int findFuelTotal(int mass) {
    auto fuel = findFuel(mass) ;

    if (fuel < 0)
        return 0;
    return fuel + findFuelTotal(fuel);
}

int main () {
    std::ifstream puzzle ("puzzle.in", std::ifstream::in);
    std::string mass;

    auto fuel = 0;
    auto fuelTotal = 0;

    while(std::getline(puzzle, mass)) {
        fuel += findFuel(std::stoi(mass, nullptr, 10));
        fuelTotal += findFuelTotal(std::stoi(mass, nullptr, 10));
    }
    puzzle.close();

    std::cout << "Part One: " << fuel << std::endl;
    std::cout << "Part Two: " << fuelTotal << std::endl;

    return 0;
}
