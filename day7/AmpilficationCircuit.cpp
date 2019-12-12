#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

int digits (int no) {
    auto count = 0;
    while (no) {
        no /= 10;
        count++;
    }

    return count;
}

int extract (int no, int pos) {
    return no / (int) pow(10, pos) % 10;
}

int alter(bool &set, int phaseSetting, int input, std::vector<int>& v, int ip, int opcode, int pos1, int pos2, int posr, int &out) {
    switch (opcode) {
        case 1:
            v[posr] = v[pos1] + v[pos2];
            return ip + 4;
        case 2:
            v[posr] = v[pos1] * v[pos2];
            return ip + 4;
        case 3:
            if(!set) {
                v[pos1] = phaseSetting;
                set = true;
            }
            else {
                v[pos1] = input;
            }
            return ip + 2;
        case 4:
            out = v[pos1];
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

int test(bool &set, int phaseSetting, int input, std::vector<int>& v, int &out) {
    for (int i = 0; i < (int)v.size(); ) {
        int rc;

        auto opcode = extract(v[i], 0);
        if (opcode == 9)
            opcode += 10 * extract(v[i], 1);

        rc = alter(set, phaseSetting, input,
            v,
            i,
            opcode,
            mode(v, i + 1, extract(v[i],2)),
            mode(v, i + 2, extract(v[i],3)),
            mode(v, i + 3, extract(v[i],4)),
            out
            );
        if (rc == -1)
            return -1;

        i = rc;

        if (rc == 4)
            return rc;
    }

    return 0;
}

int main () {
    std::ifstream puzzle ("puzzle.in", std::ifstream::in);
    std::ifstream puzzle2 ("puzzle2.in", std::ifstream::in);

    std::vector<int> v, va, vb, vc, vd, ve;
    int outa, outb, outc, outd, oute;
    int maxThruster = 0;

    const int commas = 1;
    int n, rc;

    std::vector<int> sequence {0, 1, 2, 3, 4};

    while(!puzzle.eof()) {
        puzzle >> n;
        puzzle.ignore(commas, ',');
        v.push_back(n);
    }
    puzzle.close();

    do {
        va = v;
        vb = v;
        vc = v;
        vd = v;
        ve = v;

        bool set = false;
        test(set, sequence[0], 0, va, outa);

        set = false;
        test(set, sequence[1], outa, vb, outb);

        set = false;
        test(set, sequence[2], outb, vc, outc);

        set = false;
        test(set, sequence[3], outc, vd, outd);

        set = false;
        test(set, sequence[4], outd, ve, oute);

        if(oute > maxThruster)
            maxThruster = oute;

    } while (std::next_permutation(sequence.begin(), sequence.end()));


    std::cout << "Part One: " << maxThruster << std::endl;

    sequence.clear();
    sequence = {5, 6, 7, 8, 9};

    maxThruster = 0;

    do {
        oute = 0;

        va = v;
        vb = v;
        vc = v;
        vd = v;
        ve = v;

        bool setA = false;
        bool setB = false;
        bool setC = false;
        bool setD = false;
        bool setE = false;


        do {

            rc = test(setA, sequence[0], oute, va, outa);
            va.erase(va.begin(), va.begin() + rc);

            rc = test(setB, sequence[1], outa, vb, outb);
            vb.erase(vb.begin(), vb.begin() + rc);

            rc = test(setC, sequence[2], outb, vc, outc);
            vc.erase(vc.begin(), vc.begin() + rc);

            rc = test(setD, sequence[3], outc, vd, outd);
            vd.erase(vd.begin(), vd.begin() + rc);

            rc = test(setE, sequence[4], outd, ve, oute);
            ve.erase(ve.begin(), ve.begin() + rc);
        } while (rc != -1);

        if(oute > maxThruster)
            maxThruster = oute;

    } while (std::next_permutation(sequence.begin(), sequence.end()));

    std::cout << "Part Two: " << maxThruster << std::endl;

    return 0;
}
