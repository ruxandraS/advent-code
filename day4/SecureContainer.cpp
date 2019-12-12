#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

int digitCount (int no) {
    auto count = 0;
    while(no) {
        no /= 10;
        count++;
    }

    return count;
}

int extract (int no, int pos) {
    return no / (int)pow(10, pos) % 10;
}

bool doubled (int no) {
    auto digits = digitCount(no);
    for (auto i = 0; i < digits - 1; i++)
        if (extract(no, i) == extract(no, i + 1))
            return true;

    return false;
}

bool doubledRestricted (int no) {
    auto digits = digitCount(no);

    for (auto i = 0; i < digits - 1; i++) {
        if (i == 0) {
            if (extract(no, i) == extract(no, i + 1) && extract(no, i + 1) != extract(no, i + 2))
                return true;
        }
        else if (i == digits - 2) {
            if (extract(no, i - 1) != extract(no, i) && extract(no, i) == extract(no, i + 1))
                return true;
        }
        else {
            if (extract(no, i - 1) != extract(no, i) && extract(no, i) == extract(no, i + 1) &&
                extract(no, i + 1) != extract(no, i + 2))
                return true;
        }
    }

    return false;
}

bool increasing (int no) {
    auto digits = digitCount(no);
    for (auto i = 0; i < digits - 1; i++)
        if (extract(no, i) < extract(no, i + 1))
            return false;

    return true;
}


int main () {
    std::ifstream puzzle ("puzzle.in", std::ifstream::in);
    std::ofstream rest ("rest.out", std::ifstream::out);
    std::ofstream all ("all.out", std::ifstream::out);

    std::string mass;
    int lower, higher;

    auto passwdCombo = 0;
    auto passwdComboRestricted = 0;

    while(!puzzle.eof()) {
        puzzle >> lower;
        puzzle.ignore(1, '-');
        puzzle >> higher;
    }
    puzzle.close();

    std::cout << lower << " " << higher << std::endl;

    for (auto key = lower; key <= higher; key++)
        if (increasing(key) && doubled(key)) {
            all << key << std::endl;
            passwdCombo++;
        }

    for (auto key = lower; key <= higher; key++)
        if (increasing(key) && doubledRestricted(key)){
            rest << key << std::endl;
            passwdComboRestricted++;
        }


    std::cout << "Part One: " << passwdCombo << std::endl;
    std::cout << "Part Two: " << passwdComboRestricted << std::endl;

    return 0;
}
