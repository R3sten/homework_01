#include "sparse_matrix_COO.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

SparseMatrixCOO::SparseMatrixCOO(std::vector<int> &rows,
                                 std::vector<int> &columns,
                                 std::vector<double> &values)
    : _rows(rows), _columns(columns), _values(values) {
  _matrixWidth = *std::max_element(_columns.begin(), _columns.end()) + 1;
  _matrixHeight = *std::max_element(_rows.begin(), _rows.end()) + 1;
}

SparseMatrixCOO::SparseMatrixCOO(const SparseMatrixCOO &other)
    : _rows(other._rows), _columns(other._columns), _values(other._values),
      _matrixHeight(other._matrixHeight), _matrixWidth(other._matrixWidth) {}

SparseMatrixCOO::~SparseMatrixCOO() {}

const int &SparseMatrixCOO::getNumberOfRows() const { return _matrixHeight; }

const int &SparseMatrixCOO::getNumberOfColumns() const { return _matrixWidth; }

int SparseMatrixCOO::getNumberOfNonZeros() const {
  for (unsigned int i = 0; i < _values.size(); ++i) {
    std::cout << _values[i] << " ";
  }
  std::cout << std::endl;
  return _values.size();
}

SparseMatrixCOO &SparseMatrixCOO::operator=(const SparseMatrixCOO &other) {
  if (this != &other) {
    _rows = other._rows;
    _columns = other._columns;
    _values = other._values;
    _matrixHeight = other._matrixHeight;
    _matrixWidth = other._matrixWidth;
  }
  return *this;
}

int SparseMatrixCOO::_getMatrixEntry(const int &i, const int &j) {
  int lastIndex = _rows.size();
  for (int idx = 0; idx < lastIndex; ++idx) {
    if (_rows[idx] == i) {
      if (_columns[idx] == j) {
        return idx;
      }
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

void SparseMatrixCOO::extendMatrixWidth(int newWidth) {
  _matrixWidth = newWidth;
}

void SparseMatrixCOO::extendMatrixHeight(int newHeight) {
  _matrixHeight = newHeight;
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

SparseMatrixCOO::SparseMatrixCOOProxy::SparseMatrixCOOProxy(
    int idx, SparseMatrixCOO &matrix)
    : _idx(idx), _matrix(matrix) {}

SparseMatrixCOO::SparseMatrixCOOProxy::~SparseMatrixCOOProxy() {}

SparseMatrixCOO::SparseMatrixCOOProxy::operator double() const {
  return _matrix._values[_idx];
}

SparseMatrixCOO::SparseMatrixCOOProxy &
SparseMatrixCOO::SparseMatrixCOOProxy::operator=(const double &newEntry) {
  _matrix._values[_idx] = newEntry;
  return *this;
}

SparseMatrixCOO::SparseMatrixCOOProxy &
SparseMatrixCOO::SparseMatrixCOOProxy::operator=(
    const SparseMatrixCOOProxy &other) {
  _matrix._values[_idx] = other._matrix._values[other._idx];
  return *this;
}

/// Throws an error if indices are out of bound.
SparseMatrixCOO::SparseMatrixCOOProxy
SparseMatrixCOO::operator()(const int &i, const int &j) {
  if (i < 0 || i > _matrixHeight || j < 0 || j > _matrixWidth) {
    throw std::runtime_error("Indices out of bound.");
  }
  return SparseMatrixCOO::SparseMatrixCOOProxy(_getMatrixEntry(i, j), *this);
}
