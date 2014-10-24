#include <iostream>
#include "rotate_image.h"

SquareMatrix::SquareMatrix(unsigned int aSize) : size(aSize) {
    data = new int*[size];
    for (unsigned int i = 0; i < size; i++) {
        data[i] = NULL;
        data[i] = new int[size];
    }
}

SquareMatrix::SquareMatrix(const SquareMatrix& other) : SquareMatrix(other.size) {
    for (unsigned int i = 0; i < size; i++) {
        for (unsigned int j = 0; j < size; j++) {
            data[i][j] = other.data[i][j];
        }
    }
}

SquareMatrix::~SquareMatrix() {
    if (data) {
        for (unsigned int i = 0; i < size; i++) {
            if (data[i]) {
                delete [] data[i];
            }
        }
        delete [] data;
    }
}

unsigned int SquareMatrix::getSize() {
    return size;
}

int SquareMatrix::getCell(unsigned int row, unsigned int col) {
    if (row >= size || col >= size) {
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

void SquareMatrix::setCell(unsigned int row, unsigned int col, int val) {
    if (row >= size || col >= size) {
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

std::pair<unsigned int, unsigned int> SquareMatrix::rotate_cell_position(const std::pair<unsigned int, unsigned int>& pos) {
    unsigned int new_x = this->size - 1 - pos.second;
    unsigned int new_y = pos.first;
    return std::pair<unsigned int, unsigned int>(new_x, new_y);
}

void SquareMatrix::rotate_90_degrees() {
    if (!data) {
        throw std::runtime_error("data is not initialized");
    }
    
    for (int x = 0; x < size / 2; x++) {
        for (int y = 0; y < size / 2; y++) {
            std::pair<unsigned int, unsigned int> cell0(x, y);
            auto cell1 = rotate_cell_position(cell0);
            if (cell0 != cell1) {
                auto cell2 = rotate_cell_position(cell1);
                auto cell3 = rotate_cell_position(cell2);
                int val0 = getCell(x, y);
                int val1 = getCell(cell1.first, cell1.second);
                int val2 = getCell(cell2.first, cell2.second);
                int val3 = getCell(cell3.first, cell3.second);
                setCell(cell0.first, cell0.second, val3);
                setCell(cell1.first, cell1.second, val0);
                setCell(cell2.first, cell2.second, val1);
                setCell(cell3.first, cell3.second, val2);
            }
        }
    }
}

void SquareMatrix::print() {
//    char buffer[20] = "";
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            int val = getCell(x, y);
            std::cout << (val ? '*' : ' ');
            /*
            sprintf(buffer, "%8d", val);
            std::cout << buffer;
            if (x < size - 1) {
                std::cout << " ";
            }
             */
        }
        std::cout << '\n';
    }
}