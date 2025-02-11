#include "sparse_matrix_CSR.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

template <typename T>
SparseMatrixCSR<T>::SparseMatrixCSR(const std::vector<T> &values,
                                    const std::vector<int> &columns,
                                    const std::vector<int> &rowIdx,
                                    const int &height, const int &width)
    : SparseMatrix<T>(values, columns, height, width), _rowIdx(rowIdx) {
  // assigning matrix boudaries choosing between user input and nonzero entries
  // positions into the matrix
  _matrixHeight = rowIdx.size() - 1;
  if (height > _matrixHeight) {
    _matrixHeight = height;
  }
  _matrixWidth = *std::max_element(columns.begin(), columns.end()) + 1;
  if (width > _matrixWidth) {
    _matrixWidth = width;
  }
}

/// @copydoc SparseMatrix::_getMatrixEntry(const int &i, const int &j)
/// Needs data to be ordered as it appears into the matrix reading it from left
/// to right and upper down.
template <typename T>
int SparseMatrixCSR<T>::_getMatrixEntry(const int &i, const int &j) {
  int upperIndex = _rowIdx[i + 1];
  int lowerIndex = _rowIdx[i];
  for (int idx = lowerIndex; idx < upperIndex; ++idx) {
    if (_columns[idx] == j) {
      return idx;
    }
  }

  // creates the entry if does not exist
  for (unsigned int idx = i; idx < _rowIdx.size(); ++idx) {
    _rowIdx[i + 1] += 1;
  }
  int newEntryIndex = 0; // default value added to avoid compiler warning
  if (upperIndex == lowerIndex || j == _matrixWidth - 1) {
    newEntryIndex = upperIndex;
  } else {
    upperIndex += 1;
    for (int idx = lowerIndex; idx < upperIndex; ++idx) {
      if (_columns[idx] > j) {
        newEntryIndex = idx;
        break;
      }
    }
  }
  _values.insert(_values.begin() + newEntryIndex, 0);
  _columns.insert(_columns.begin() + newEntryIndex, j);
  return newEntryIndex;
}

/// @copydoc SparseMatrix::operator()(const int &i, const int &j)
/// @details  Throws an error if indices are out of bound.
template <typename T>
T &SparseMatrixCSR<T>::operator()(const int &i, const int &j) {
  if (i < 0 || i > _matrixHeight || j < 0 || j > _matrixWidth) {
    throw std::runtime_error("Indices out of bound.");
  }

  return _values[_getMatrixEntry(i, j)];
}

template <typename T> void SparseMatrixCSR<T>::eraseZeroEntries() {
  for (int idx = _values.size() - 1; idx >= 0; --idx) {
    if (_values[idx] == 0) {
      for (unsigned int i = 0; i < _rowIdx.size() - 1; ++i) {
        if (idx < _rowIdx[i + 1]) {
          for (unsigned int idx = i; idx < _rowIdx.size(); ++idx) {
            _rowIdx[i + 1] -= 1;
          }
          break;
        }
      }
      _values.erase(_values.begin() + idx);
      _columns.erase(_columns.begin() + idx);
    }
  }
}

template <typename T>
std::vector<T> SparseMatrixCSR<T>::operator*(const std::vector<T> &x) const {
  int xSize = x.size();
  if (xSize != _matrixWidth) {
    std::string errorText =
        "Input vector does not have compatible size. Expected: " +
        std::to_string(_matrixWidth) + ", actual: " + std::to_string(xSize) +
        ".";
    throw std::runtime_error(errorText);
  }
  std::vector<double> result(_matrixHeight, 0.0);
  for (unsigned int i = 0; i < _rowIdx.size() - 1; ++i) {
    for (int idx = _rowIdx[i]; idx < _rowIdx[i + 1]; ++idx) {
      for (int j = 0; j < _matrixWidth; ++j) {
        if (_columns[idx] == j) {
          result[i] += _values[idx] * x[j];
        }
      }
    }
  }
  return result;
}

template <typename T> void SparseMatrixCSR<T>::printMatrix() const {
  for (int i = 0; i < _matrixHeight; ++i) {
    for (int j = 0; j < _matrixWidth; ++j) {
      bool isZero = true;
      for (int idx = _rowIdx[i]; idx < _rowIdx[i + 1]; ++idx) {
        if (_columns[idx] == j) {
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

template <typename T>
std::vector<int> SparseMatrixCSR<T>::getNonZeroEntriesRows() const {
  std::vector<int> rows{};
  for (unsigned int i = 0; i < _rowIdx.size() - 1; ++i) {
    rows.insert(rows.begin() + _rowIdx[i], _rowIdx[i + 1] - _rowIdx[i], i);
  }
  const std::vector<int> constRows = rows;
  return constRows;
}

template <typename T>
SparseMatrixCOO<T> SparseMatrixCSR<T>::toCooridnateStorageScheme() {
  return SparseMatrixCOO<T>(_values, _columns, getNonZeroEntriesRows(),
                            _matrixHeight, _matrixWidth);
}
