#ifndef __SPARSE_MATRIX_COO_TPL__
#define __SPARSE_MATRIX_COO_TPL__
#include "sparse_matrix_COO.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

template <class T>
SparseMatrixCOO<T>::SparseMatrixCOO(const std::vector<T> &values,
                                    const std::vector<int> &columns,
                                    const std::vector<int> &rows,
                                    const int &height, const int &width)
    : SparseMatrix<T>(values, columns, height, width), _rows(rows) {

  // assigning matrix boudaries choosing between user input and nonzero entries
  // positions into the matrix
  _matrixHeight = *std::max_element(rows.begin(), rows.end()) + 1;
  if (height > _matrixHeight) {
    _matrixHeight = height;
  }
  _matrixWidth = *std::max_element(columns.begin(), columns.end()) + 1;
  if (width > _matrixWidth) {
    _matrixWidth = width;
  }
}

/// @copydoc SparseMatrix::operator()(const int &i, const int &j)
/// @details Throws an error if indices are out of bound.
template <class T>
T &SparseMatrixCOO<T>::operator()(const int &i, const int &j) {
  if (i < 0 || i > _matrixHeight || j < 0 || j > _matrixWidth) {
    throw std::runtime_error("Indices out of bound.");
  }
  return _values[_getMatrixEntry(i, j)];
}

template <class T>
int SparseMatrixCOO<T>::_getMatrixEntry(const int &i, const int &j) {
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

template <class T> void SparseMatrixCOO<T>::_adjustNonZeroValuesStorageOrder() {
  int size = _rows.size();
  int s = 0;
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      for (int k = 0; k < size; ++k) {
        if (_rows[k] == i && _columns[k] == j) {
          std::swap(_values[s], _values[k]);
          std::swap(_columns[s], _columns[k]);
          std::swap(_rows[s], _rows[k]);
          s += 1;
        }
      }
    }
  }
}

template <class T> void SparseMatrixCOO<T>::eraseZeroEntries() {
  for (int idx = _values.size() - 1; idx >= 0; --idx) {
    if (_values[idx] == 0) {
      _values.erase(_values.begin() + idx);
      _rows.erase(_rows.begin() + idx);
      _columns.erase(_columns.begin() + idx);
    }
  }
}

template <class T>
std::vector<T> SparseMatrixCOO<T>::operator*(const std::vector<T> &x) const {
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

template <class T> void SparseMatrixCOO<T>::printMatrix() const {
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

template <class T>
std::vector<int> SparseMatrixCOO<T>::getNonZeroEntriesRows() const {
  return _rows;
}

template <class T>
SparseMatrixCSR<T> SparseMatrixCOO<T>::toCompressedRowStorageScheme() {
  std::vector<int> rowIdx{0};
  int k = 0;
  _adjustNonZeroValuesStorageOrder();
  for (int i = 0; i < SparseMatrix<T>::getNumberOfRows(); ++i) {
    for (unsigned int j = k; j < _rows.size(); ++j) {
      if (_rows[j] == i) {
        k += 1;
      } else {
        break;
      }
    }
    rowIdx.insert(rowIdx.begin() + (i + 1), k);
  }
  return SparseMatrixCSR<T>(_values, _columns, rowIdx, _matrixHeight,
                            _matrixWidth);
}

#endif /* __SPARSE_MATRIX_COO_TPL__ */
