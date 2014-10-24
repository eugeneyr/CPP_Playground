//
//  zeroify_matrix.h
//  CPP_Playground
//
//  Created by Yevhen Yaremenko on 10/23/14.
//  Copyright (c) 2014 Yevhen Yaremenko. All rights reserved.
//

#ifndef __CPP_Playground__zeroify_matrix__
#define __CPP_Playground__zeroify_matrix__

#include <stdio.h>
#include <exception>
#include <stdexcept>
#include <utility>

class Matrix {
private:
    unsigned int sizeX;
    unsigned int sizeY;
    double** data;
    
public:
    Matrix(unsigned int aSizeX, unsigned int aSizeY);
    
    Matrix(const Matrix& other);
    
    virtual ~Matrix();
    
    unsigned int getSizeX() { return sizeX; }
    unsigned int getSizeY() { return sizeY; }
    
    double getCell(unsigned int row, unsigned int col);
    
    void setCell(unsigned int row, unsigned int col, double val);
    
    void zeroify();
    
    void print();
};

#endif /* defined(__CPP_Playground__zeroify_matrix__) */
