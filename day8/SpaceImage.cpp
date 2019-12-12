#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include <cstdlib>

#define WIDTH 25
#define HEIGHT 6

#define BLACK 0
#define WHITE 1
#define TRANSPARENT 2

int to_int (char c) {
    return c - '0';
}

int countZeros(const std::vector<std::vector<int>> &layer) {
    int count = 0;
    for (int i = 0; i < (int)layer.size(); i++)
        for (int j = 0; j < (int)layer[i].size(); j++)
            if (layer[i][j] == 0)
                count++;

    return count;
}

void countNonZeros(const std::vector<std::vector<int>> &layer, int &ones, int &twos) {
    for (int i = 0; i < (int)layer.size(); i++)
        for (int j = 0; j < (int)layer[i].size(); j++) {
            if (layer[i][j] == WHITE) {
                ones++;
                continue;
            }
            if (layer[i][j] == TRANSPARENT) {
                twos++;
            }
        }
}

void computeImage(std::vector<std::vector<int>> &image, std::vector<std::vector<std::vector<int>>> &layers) {
    for (int l = 1; l < (int)layers.size(); l++)
        for (int i = 0; i < (int)layers[l].size(); i++)
            for (int j = 0; j < (int)layers[l][i].size(); j++)
                if (image[i][j] == TRANSPARENT && layers[l][i][j] != TRANSPARENT)
                    image[i][j] = layers[l][i][j];
}

int main () {
    std::ifstream puzzle ("puzzle.in", std::ifstream::in);
    std::ofstream image ("image.pbm", std::ofstream::out);
    std::vector<std::vector<std::vector<int>>> layers;
    std::vector<std::vector<int>> imageData;

    char pixel;

    int r = 0, c = 0, capacity = 0, layer = 0;
    int ones = 0, twos = 0;

    // init layers
    layers.resize(layer + 1);

    layers[layer].resize(HEIGHT);
    for (int i = 0; i < (int)layers[layer].size(); i++)
        layers[layer][i].resize(WIDTH);


    // read from file
    while(puzzle.get(pixel)) {
        if (capacity == WIDTH * HEIGHT) {
            layer++;

            layers.resize(layer + 1);

            layers[layer].resize(HEIGHT);
            for (int i = 0; i < (int)layers[layer].size(); i++)
                layers[layer][i].resize(WIDTH);

            r = 0;
            c = 0;
            capacity = 0;
        }

        if (r < HEIGHT) {
            if (c >= WIDTH) {
                r++;
                c = 0;
            }

            layers[layer][r][c] = to_int(pixel);
            capacity++;
            c++;
        }

    }
    puzzle.close();

    layer = 0;
    for (int l = 0; l < (int)layers.size(); l++) {
        if (countZeros(layers[l]) <= countZeros(layers[layer]))
            layer = l;
    }

    countNonZeros(layers[layer], ones, twos);

    std::cout << "Part One: " << ones * twos << std::endl;

    imageData = layers[0];
    computeImage(imageData, layers);

    image << "P1\n";
    image << WIDTH << " " << HEIGHT << "\n";
    image << "1\n";
    for (int i = 0; i < (int)imageData.size(); i++){
        for (int j = 0; j < (int)imageData[i].size(); j++)
            image << imageData[i][j] << " ";
        image << "\n";
    }

    image.close();

    return 0;
}
