#include <iostream>
#include <fstream>
#include <string>
#include <vector>

bool alter(std::vector<int>& v, int opcode, int pos1, int pos2, int posr) {
    switch (opcode) {
        case 1:
            v[posr] = v[pos1] + v[pos2];
            return true;
        case 2:
            v[posr] = v[pos1] * v[pos2];
            return true;
        case 99:
            return false;
        default:
            std::cerr << "Unknown opcode " << opcode << std::endl;
            return false;
    }
}

int restore_gravity(std::vector<int>& vc) {
    for (int i = 0; i < (int)vc.size(); i += 4) {
        bool rc = alter(vc, vc[i], vc[i + 1], vc[i + 2], vc[i + 3]);
        if (!rc)
            return vc[0];
    }

    return vc[0];
}

int main () {
    std::ifstream puzzle ("puzzle.in", std::ifstream::in);
    std::vector<int> v;
    std::vector<int> vc;
    const int commas = 1;
    int n;

    while(!puzzle.eof() && !puzzle.bad()) {
        puzzle >> n;
        puzzle.ignore(commas, ',');
        v.push_back(n);
    }
    puzzle.close();

    vc = v;

    // replacing values
    vc[1] = 12;
    vc[2] = 2;

    std::cout << "Part One: " << restore_gravity(vc) << std::endl;

    for (int noun = 0; noun < 99; noun++) {
        for (int verb = 0; verb < 99; verb++) {
            vc = v;
            vc[1] = noun;
            vc[2] = verb;

            restore_gravity(vc);

            if(vc[0] == 19690720) {
                goto exit;
            }
        }
    }

exit:
    std::cout << "Part Two: " << 100 * vc[1] + vc[2] << std::endl;

    return 0;
}
