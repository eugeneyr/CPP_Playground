//
//  zeroify_matrix.cpp
//  CPP_Playground
//
//  Created by Yevhen Yaremenko on 10/23/14.
//  Copyright (c) 2014 Yevhen Yaremenko. All rights reserved.
//

#include "zeroify_matrix.h"
#include <iostream>
#include <math.h>

Matrix::Matrix(unsigned int aSizeX, unsigned int aSizeY) : sizeX(aSizeX), sizeY(aSizeY) {
    data = new double*[sizeX];
    for (unsigned int i = 0; i < sizeY; i++) {
        data[i] = new double[sizeY];
    }
}

Matrix::Matrix(const Matrix& other) : Matrix(other.sizeX, other.sizeY) {
    for (unsigned int i = 0; i < sizeX; i++) {
        for (unsigned int j = 0; j < sizeY; j++) {
            data[i][j] = other.data[i][j];
        }
    }
}

Matrix::~Matrix() {
    if (data) {
        for (unsigned int i = 0; i < sizeX; i++) {
            if (data[i]) {
                delete [] data[i];
            }
        }
        delete [] data;
    }
}

double Matrix::getCell(unsigned int row, unsigned int col) {
    if (row >= sizeX || col >= sizeY) {
        throw std::out_of_range("Row or col are out of range");
    }
    if (!data) {
        throw std::runtime_error("data is not initialized");
    }
    auto aRow = data[row];
    if (aRow) {
        return aRow[col];
    }
    throw std::runtime_error("row is absent");
}

void Matrix::setCell(unsigned int row, unsigned int col, double val) {
    if (row >= sizeX || col >= sizeY) {
        throw std::out_of_range("Row or col are out of range");
    }
    if (!data) {
        throw std::runtime_error("data is not initialized");
    }
    auto aRow = data[row];
    if (aRow) {
        aRow[col] = val;
    } else {
        throw std::runtime_error("row is absent");
    }
}

void Matrix::print() {
    static char buffer[32];
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            double val = getCell(x, y);
            sprintf(buffer, "%.4f", val);
            std::cout << buffer;
            if (x < sizeX - 1) {
                std::cout << " ";
            }
        }
        std::cout << '\n';
    }
}

void Matrix::zeroify() {
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            double val = getCell(i, j);
            if (fabs(val) < 0.000000001) {
                setCell(i, j, 0.0);
            }
        }
    }
    Matrix copy(*this);
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            double val = getCell(i, j);
            if (val == 0.0) {
                for (int i1 = 0; i1 < sizeX; i1++) {
                    if (i1 != i) {
                        copy.setCell(i1, j, 0.0);
                    }
                }
                for (int j1 = 0; j1 < sizeY; j1++) {
                    if (j1 != j) {
                        copy.setCell(i, j1, 0.0);
                    }
                }
            }
        }
    }
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            double val = copy.getCell(i, j);
            setCell(i, j, val);
        }
    }
}
