#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

int digits (int no) {
    int count;
    while (no) {
        no /= 10;
        count++;
    }

    return count;
}

int extract (int no, int pos) {
    return no / (int) pow(10, pos) % 10;
}

int alter(std::vector<int>& v, int ip, int opcode, int pos1, int pos2, int posr) {
    switch (opcode) {
        case 1:
            v[posr] = v[pos1] + v[pos2];
            return ip + 4;
        case 2:
            v[posr] = v[pos1] * v[pos2];
            return ip + 4;
        case 3:
            int in;
            std::cin >> in;
            v[pos1] = in;
            return ip + 2;
        case 4:
            std::cout << v[pos1];
            return ip + 2;
        case 5:
            return (v[pos1] != 0) ? v[pos2] : ip + 3;
        case 6:
            return (v[pos1] == 0) ? v[pos2] : ip + 3;
        case 7:
            v[posr] = (v[pos1] < v[pos2]) ? 1 : 0;
            return ip + 4;
        case 8:
            v[posr] = (v[pos1] == v[pos2]) ? 1 : 0;
            return ip + 4;
        case 99:
            return -1;
        default:
            std::cerr << "Unknown opcode " << opcode << std::endl;
            return -1;
    }
}

int mode(const std::vector<int>& v, int pos, int type) {
    return (type == 0) ? v[pos] : pos;
}

void test(std::vector<int>& vc) {
    for (int i = 0; i < (int)vc.size(); ) {
        int rc;

        auto opcode = extract(vc[i], 0);
        if (opcode == 9)
            opcode += 10 * extract(vc[i], 1);

        rc = alter(vc, i,
            opcode,
            mode(vc, i + 1, extract(vc[i],2)),
            mode(vc, i + 2, extract(vc[i],3)),
            mode(vc, i + 3, extract(vc[i],4))
            );
        if (rc == -1)
            return;

        i = rc;
    }
}

int main () {
    std::ifstream puzzle ("puzzle.in", std::ifstream::in);
    std::ifstream puzzle2 ("puzzle2.in", std::ifstream::in);

    std::vector<int> v;
    const int commas = 1;
    int n;

    while(!puzzle.eof()) {
        puzzle >> n;
        puzzle.ignore(commas, ',');
        v.push_back(n);
    }
    puzzle.close();

    std::cout << "Enter 1: ";
    test(v);
    std::cout << std::endl << std::endl;

    v.clear();
    while(!puzzle2.eof()) {
        puzzle2 >> n;
        puzzle2.ignore(commas, ',');
        v.push_back(n);
    }
    puzzle2.close();

    std::cout << "Enter 5: ";
    test(v);
    std::cout << std::endl;

    return 0;
}
