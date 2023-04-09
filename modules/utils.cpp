/*************************************************************************
 *
 *  Project
 *                        __  __ _______ _____  _  __
 *                       |  \/  |__   __|  __ \| |/ /
 *  ___  _ __   ___ _ __ | \  / |  | |  | |__) | ' /
 * / _ \| '_ \ / _ \ '_ \| |\/| |  | |  |  ___/|  <
 *| (_) | |_) |  __/ | | | |  | |  | |  | |    | . \
 * \___/| .__/ \___|_| |_|_|  |_|  |_|  |_|    |_|\_\
 *      | |
 *      |_|
 *
 *
 * Copyright (C) Akiel Aries, <akiel@akiel.org>, et al.
 *
 * This software is licensed as described in the file LICENSE, which
 * you should have received as part of this distribution. The terms
 * among other details are referenced in the official documentation
 * seen here : https://akielaries.github.io/openMTPK/ along with
 * important files seen in this project.
 *
 * You may opt to use, copy, modify, merge, publish, distribute
 * and/or sell copies of the Software, and permit persons to whom
 * the Software is furnished to do so, under the terms of the
 * LICENSE file. As this is an Open Source effort, all implementations
 * must be of the same methodology.
 *
 *
 *
 * This software is distributed on an AS IS basis, WITHOUT
 * WARRANTY OF ANY KIND, either express or implied.
 *
 ************************************************************************/

/*
 * Utilities implementations for different helper methods/functions
 * needed for openMTPK
 */
#include "../include/utils.hpp"
#include "../include/linalg/matrix.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

#include <string>
#include <tuple>
#include <vector>

using namespace mtpk;

// TODO: helper function to compute dimensions of the CSV file and
// pass into other functions
// std::string Data::read_csv(file_name, ??)

std::tuple<std::vector<std::vector<double>>, std::vector<double>> Data::load() {
    const int SIZE = 1; // k = 30

    std::vector<std::vector<double>> inputSet;
    std::vector<double> outputSet;

    setData(SIZE, "../../data/school_scores.csv",
            //"../../data/BreastCancer.csv",
            inputSet, outputSet);

    return {inputSet, outputSet};
}

void Data::setData(int k, std::string fileName,
                   std::vector<std::vector<double>> &inputSet,
                   std::vector<double> &outputSet) {
    // LinAlg alg;
    std::string inputTemp;
    std::string outputTemp;

    inputSet.resize(k);

    std::ifstream dataFile(fileName);
    if (!dataFile.is_open()) {
        std::cout << fileName << " failed to open." << std::endl;
    }

    std::string line;
    while (std::getline(dataFile, line)) {
        std::stringstream ss(line);

        for (int i = 0; i < k; i++) {
            std::getline(ss, inputTemp, ',');
            inputSet[i].push_back(std::stod(inputTemp));
            // inputSet(i, inputSet.cols) = std::stod(inputTemp);
        }

        std::getline(ss, outputTemp, ',');
        outputSet.push_back(std::stod(outputTemp));
        // outputSet(0, outputSet.cols) = std::stod(outputTemp);
    }
    // Matrix obj
    // inputSet = inputSet.T();

    dataFile.close();
}
void Data::printData(std::vector<std::string> inputName,
                     std::vector<std::vector<double>> inputSet) {
    // LinAlg alg;
    // inputSet = alg.transpose(inputSet);
    for (int i = 0; i < inputSet.size(); i++) {
        std::cout << inputName[i] << std::endl;
        for (int j = 0; j < inputSet[i].size(); j++) {
            std::cout << inputSet[i][j] << std::endl;
        }
    }
}

void Data::printData(std::vector<std::string> inputName, std::string outputName,
                     std::vector<std::vector<double>> inputSet,
                     std::vector<double> outputSet) {
    // LinAlg alg;
    // inputSet = alg.transpose(inputSet);
    for (int i = 0; i < inputSet.size(); i++) {
        std::cout << inputName[i] << std::endl;
        for (int j = 0; j < inputSet[i].size(); j++) {
            std::cout << inputSet[i][j] << std::endl;
        }
    }

    std::cout << outputName << std::endl;
    for (int i = 0; i < outputSet.size(); i++) {
        std::cout << outputSet[i] << std::endl;
    }
}
