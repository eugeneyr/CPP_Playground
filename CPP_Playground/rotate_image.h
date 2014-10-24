//
//  rotate_image.h
//  CPP_Playground
//
//  Created by Yevhen Yaremenko on 10/23/14.
//  Copyright (c) 2014 Yevhen Yaremenko. All rights reserved.
//

#ifndef __CPP_Playground__rotate_image__
#define __CPP_Playground__rotate_image__

#include <stdio.h>
#include <exception>
#include <stdexcept>
#include <utility>

class SquareMatrix {
private:
    unsigned int size;
    int** data;
    
    std::pair<unsigned int, unsigned int> rotate_cell_position(const std::pair<unsigned int, unsigned int>& pos);

public:
    SquareMatrix(unsigned int aSize);
    
    SquareMatrix(const SquareMatrix& other);
    
    virtual ~SquareMatrix();
    
    unsigned int getSize();
    
    int getCell(unsigned int row, unsigned int col);
    
    void setCell(unsigned int row, unsigned int col, int val);
    
    void rotate_90_degrees();
    
    void print();
};

#endif /* defined(__CPP_Playground__rotate_image__) */
