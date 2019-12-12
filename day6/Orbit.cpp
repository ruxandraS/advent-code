#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

int computeMap(std::map<std::string, std::string> &orbitMap,
    std::map<std::string, int> &partialMap,
    std::string key,
    std::string value) {

    // final orbit
    if (orbitMap.find(value) == orbitMap.end()) {
        partialMap.insert({key, 1});
        return 1;
    }

    // find orbit in previously computed map
    auto searchP = partialMap.find(value);
    if (searchP != partialMap.end()) {
        partialMap[key] = 1 + searchP->second;
        return 1 + searchP->second;
    }

    // find value as key in the same map and add it to partial computation
    return 1 + computeMap(orbitMap, partialMap, value, orbitMap.find(value)->second);
}

void route(std::map<std::string, std::string> &orbitMap,
    std::vector<std::string> &path,
    std::string value) {

    // final orbit
    if (orbitMap.find(value) == orbitMap.end()) {
        path.push_back(value);
        return;
    }

    path.push_back(value);
    route(orbitMap, path, orbitMap.find(value)->second);
}

int main () {
    std::ifstream puzzle ("puzzle.in", std::ifstream::in);
    std::string line;

    std::string object, orbit;
    std::map<std::string, std::string> orbitMap;
    std::map<std::string, int> partialMap;
    auto orbits = 0;

    std::vector<std::string> myRoute;
    std::vector<std::string> santaRoute;
    std::vector<std::string> transferPoints;

    while(std::getline(puzzle, line)) {
        orbit = line.substr(0, line.find(')'));
        object = line.substr(line.find(')') + 1, line.size() - 1);

        orbitMap.insert({object, orbit});
    }
    puzzle.close();

    for (auto &[k,v]: orbitMap) {
        orbits += computeMap(orbitMap, partialMap, k, v);;
    }

    route(orbitMap, myRoute, orbitMap["YOU"]);
    route(orbitMap, santaRoute, orbitMap["SAN"]);

    for (auto m : myRoute)
        if(std::find(santaRoute.begin(), santaRoute.end(), m) == santaRoute.end())
                transferPoints.push_back(m);

    for (auto s : santaRoute)
        if(std::find(myRoute.begin(), myRoute.end(), s) == myRoute.end())
                transferPoints.push_back(s);

    std::cout << "Part One: " << orbits << std::endl;
    std::cout << "Part Two: " << transferPoints.size() << std::endl;

    return 0;
}
