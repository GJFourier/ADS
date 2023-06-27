#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "SparseMatrix.h"

SparseMatrix::SparseMatrix(const std::string input_file) {
  /* TODO: Your code here. */
    std::string s;
    int row, col;
    DataType data;
    std::ifstream file(input_file);
    file >> _row >> _col;
    std::getline(file, s);
    while(std::getline(file, s)){
        std::stringstream ss(s);
        ss >> row >> col >> data;
        mat[row][col] = data;
    }
    file.close();
}

void SparseMatrix::to_file(const std::string output_file) {
  /* TODO: Your code here. */
    std::ofstream file(output_file);
    rtoc::iterator iter1;
    ctod::iterator iter2;
    iter1 = mat.begin();
    file << _row << ' ' << _col << '\n';
    while(iter1 != mat.end()) {
        iter2 = iter1->second.begin();
        while (iter2 != iter1->second.end()){
            file << iter1->first << ' ' << iter2->first << ' ' << iter2->second << '\n';
            ++iter2;
        }
        ++iter1;
    }
    file.close();
}

SparseMatrix SparseMatrix::operator*(const SparseMatrix &right) {
  /* TODO: Your code here. */
    SparseMatrix result;
    if(getCol() != right._row){
        return result;
    }
    result.setRow(_row);
    result.setCol(right._col);
    rtoc::iterator iter_l1;
    rtoc::const_iterator iter_r1;
    ctod::iterator iter_l2;
    ctod::const_iterator iter_r2;
    int i, j, k;
    DataType x, y, z;
    iter_l1 = mat.begin();
    while(iter_l1 != mat.end()){
        iter_l2 = iter_l1->second.begin();
        i = iter_l1->first;
        while(iter_l2 != iter_l1->second.end()){
            x = iter_l2->second;
            k = iter_l2->first;
            iter_r1 = right.mat.find(k);
            if(iter_r1 != right.mat.end()){
                iter_r2 = iter_r1->second.begin();
                while(iter_r2 != iter_r1->second.end()){
                    j = iter_r2->first;
                    y = iter_r2->second;
                    z = x * y;
                    if(z != 0){
                        if(result.mat.count(i) == 0){
                            result.insert(i, j, z);
                        }
                        else{
                            if(result.mat[i].count(j) == 0 ){
                                result.insert(i, j, z);
                            }
                            else{
                                result.mat[i][j] += z;
                            }
                        }
                    }
                    ++iter_r2;
                }
            }
            ++iter_l2;
        }
        ++iter_l1;
    }
    return result;
}

void SparseMatrix::setRow(int r) {
    _row = r;
}

void SparseMatrix::setCol(int c) {
    _col = c;
}

void SparseMatrix::insert(int r, int c, int d) {
    mat[r][c] = d;
    ++num;
}

int SparseMatrix::getRow() {
    return _row;
}

int SparseMatrix::getCol() {
    return _col;
}

int SparseMatrix::getData(int r, int c) const {
    return (mat.at(r)).at(c);
}

SparseMatrix::SparseMatrix() {
    num = 0;
}

