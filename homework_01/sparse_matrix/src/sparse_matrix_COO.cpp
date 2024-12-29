#include "sparse_matrix_COO.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

SparseMatrixCOO::SparseMatrixCOO(const std::vector<double> &values,
                                 const std::vector<int> &columns,
                                 const std::vector<int> &rows,
                                 const int &height, const int &width)
    : SparseMatrix(values, columns, height, width), _rows(rows) {

  _matrixHeight = *std::max_element(_rows.begin(), _rows.end()) + 1;
  if (height > _matrixHeight) {
    _matrixHeight = height;
  }
  _matrixWidth = *std::max_element(_columns.begin(), _columns.end()) + 1;
  if (width > _matrixWidth) {
    _matrixWidth = width;
  }
}

int SparseMatrixCOO::_getMatrixEntry(const int &i, const int &j) {
  int lastIndex = _rows.size();
  for (int idx = 0; idx < lastIndex; ++idx) {
    if (_rows[idx] == i && _columns[idx] == j) {
      return idx;
    }
  }
  // creates the entry if does not exist
  _rows.push_back(i);
  _columns.push_back(j);
  _values.push_back(0.0);
  return lastIndex;
}

void SparseMatrixCOO::eraseZeroEntries() {
  for (int idx = _values.size() - 1; idx >= 0; --idx) {
    if (_values[idx] == 0) {
      _values.erase(_values.begin() + idx);
      _rows.erase(_rows.begin() + idx);
      _columns.erase(_columns.begin() + idx);
    }
  }
}

std::vector<double> SparseMatrixCOO::operator*(const std::vector<double> &x) {
  int xSize = x.size();
  if (xSize != _matrixWidth) {
    std::string errorText =
        "Input vector does not have compatible size. Expected: " +
        std::to_string(_matrixWidth) + ", actual: " + std::to_string(xSize) +
        ".";
    throw std::runtime_error(errorText);
  }
  std::vector<double> result(_matrixHeight, 0.0);
  for (int j = 0; j < _matrixWidth; ++j) {
    for (unsigned int idx = 0; idx < _columns.size(); ++idx) {
      if (_columns[idx] == j) {
        result[_rows[idx]] += _values[idx] * x[j];
      }
    }
  }
  return result;
}

void SparseMatrixCOO::printMatrix() {
  for (int i = 0; i < _matrixHeight; ++i) {
    for (int j = 0; j < _matrixWidth; ++j) {
      bool isZero = true;
      for (unsigned int idx = 0; idx < _columns.size(); ++idx) {
        if (_columns[idx] == j && _rows[idx] == i) {
          std::cout.width(6);
          std::cout.precision(6);
          std::cout << _values[idx];
          std::cout << " ";
          isZero = false;
        }
      }
      if (isZero) {
        std::cout.width(6);
        std::cout << "0";
        std::cout << " ";
      }
    }
    std::cout << std::endl;
  }
}

/// @copydoc SparseMatrix::operator()(const int &i, const int &j)
/// @details Throws an error if indices are out of bound.
double &SparseMatrixCOO::operator()(const int &i, const int &j) {
  if (i < 0 || i > _matrixHeight || j < 0 || j > _matrixWidth) {
    throw std::runtime_error("Indices out of bound.");
  }
  return _values[_getMatrixEntry(i, j)];
}
