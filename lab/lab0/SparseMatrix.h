#pragma once

#include <string>
#include <vector>
#include <map>
#define DataType int
typedef std::map<int , DataType> ctod;
typedef std::map<int, ctod> rtoc;
class SparseMatrix {
private:

  int _row;
  int _col;
  std::string _out;
  /* TODO: Add any necessary data structure here. */
  rtoc mat;

public:
  int num;
  SparseMatrix();

  SparseMatrix(const std::string input_file);

  void to_file(const std::string output_file);

  SparseMatrix operator*(const SparseMatrix &right);
  int getData(int r, int c)const;
  void setRow(int r);
  void setCol(int c);
  int getRow();
  int getCol();
  void insert(int r, int c, DataType d);
};