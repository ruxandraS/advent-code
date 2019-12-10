#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <bits/stdc++.h>

struct Point {
    int x;
    int y;

    bool operator<(const Point &p) const {
        return std::tie(x, y) < std::tie(p.x, p.y);
    }

    bool operator==(const Point &p) const {
        return std::tie(x, y) == std::tie(p.x, p.y);
    }
};

int manhattan (Point p1, Point p2) {
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

std::vector<Point> intersections (std::vector<std::vector<Point>> paths)
{
    std::sort(paths[0].begin(), paths[0].end());
    std::sort(paths[1].begin(), paths[1].end());

    std::vector<Point> intersection;

    std::set_intersection(
        paths[0].begin(),
        paths[0].end(),
        paths[1].begin(),
        paths[1].end(),
        std::back_inserter(intersection));

    return intersection;
}

int main () {
    std::ifstream puzzle ("puzzle.in", std::ifstream::in);
    std::vector<std::vector<Point>> paths;
    std::string line;

    const int commas = 1;
    char c;
    int n, x, y;
    int l = 0;

    paths.resize(2);

    while(std::getline(puzzle, line)) {
        std::istringstream linestream(line);
        while(!linestream.eof()) {
            linestream >> c >> n;

            if(!paths[l].empty()) {
                auto front = paths[l].back();
                x = front.x;
                y = front.y;
            }
            else {
                x = 0;
                y = 0;
            }

            switch(c) {
                case 'L':
                    for(auto i = 1; i <= n; i++)
                        paths[l].push_back(Point{x - i, y});
                    break;
                case 'R':
                    for(auto i = 1; i <= n; i++)
                        paths[l].push_back(Point{x + i, y});
                    break;
                case 'U':
                    for(auto i = 1; i <= n; i++)
                        paths[l].push_back(Point{x, y + i});
                    break;
                case 'D':
                    for(auto i = 1; i <= n; i++)
                        paths[l].push_back(Point{x, y - i});
                    break;
            }

            linestream.ignore(commas, ',');
        }

        l++;
    }
    puzzle.close();

    std::vector<Point> intersection = intersections(paths);

    auto src = Point {0, 0};

    auto distance = INT_MAX;
    for (auto p : intersection) {
        if (p == src)
            continue;
        if(manhattan(src, p) < distance) {
            distance = manhattan(src, p);
        }
    }

    auto steps = INT_MAX;
    for (auto p : intersection) {
        auto sequence = 0;
        for (auto s : paths[0]) {
            sequence++;
            if(s == p)
                break;
        }
        for (auto s : paths[1]) {
            sequence++;
            if(s == p)
                break;
        }
        if(sequence < steps) {
            steps = sequence;
        }
    }

    std::cout << "Part One: " << distance << std::endl;
    std::cout << "Part Two: " << steps << std::endl;

    return 0;
}
