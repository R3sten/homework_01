#include "sparse_matrix_COO.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

SparseMatrixCOO::SparseMatrixCOO(std::vector<int> &rows,
                                 std::vector<int> &columns,
                                 std::vector<double> &values)
    : _rows(rows), _columns(columns), _values(values) {
  _matrixWidth = *std::max_element(_columns.begin(), _columns.end()) + 1;
  _matrixHeight = *std::max_element(_rows.begin(), _rows.end()) + 1;
}
// SparseMatrixCOO::SparseMatrixCOO(double *matrix) {}

SparseMatrixCOO::~SparseMatrixCOO() {}

const int &SparseMatrixCOO::getNumberOfRows() const { return _matrixHeight; }

const int &SparseMatrixCOO::getNumberOfColumns() const { return _matrixWidth; }

int SparseMatrixCOO::getNumberOfNonZeros() const {
  std::cout << "rows:" << std::endl;
  for (double v : _rows) {
    std::cout << v << " ";
  }
  std::cout << std::endl;
  std::cout << "columns:" << std::endl;
  for (double v : _columns) {
    std::cout << v << " ";
  }
  std::cout << std::endl;
  std::cout << "values:" << std::endl;
  for (double v : _values) {
    std::cout << v << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  return _values.size();
}

double &SparseMatrixCOO::_getMatrixEntry(const int &i, const int &j) {
  std::cout << "Coordinates : " << i << " " << j << std::endl;
  std::cout << std::endl;
  std::cout << "Initial values: " << std::endl;
  std::cout << "rows:" << std::endl;
  for (double v : _rows) {
    std::cout << v << " ";
  }
  std::cout << std::endl;
  std::cout << "columns:" << std::endl;
  for (double v : _columns) {
    std::cout << v << " ";
  }
  std::cout << std::endl;
  std::cout << "values:" << std::endl;
  for (double v : _values) {
    std::cout << v << " ";
  }
  std::cout << std::endl;

  for (int idx = 0; idx < _rows.size(); ++idx) {
    if (_rows.at(idx) == i) {
      if (_columns.at(idx) == j) {
        return _values.at(idx);
      }
    }
  }
  // creates the entry if it does not exist
  _rows.push_back(i);
  _columns.push_back(j);
  _values.push_back(0.0);
  return _values.back();
}

void SparseMatrixCOO::_eraseNullEntry() {
  int idxToDelete = 0;
  for (int idx = 0; idx < _values.size(); ++idx) {
    if (_values.at(idx) == 0) {
      idxToDelete = idx;
    }
  }
  _values.erase(_values.begin() + idxToDelete);
  _rows.erase(_rows.begin() + idxToDelete);
  _columns.erase(_columns.begin() + idxToDelete);
}

// SparseMatrixCOO::SparseMatrixCOOProxy &SparseMatrixCOO::operator()(int i,
//                                                                    int j) {
//   return SparseMatrixCOO::SparseMatrixCOOProxy(getMatrixEntry(i, j));
// }

SparseMatrixCOO::SparseMatrixCOOProxy::SparseMatrixCOOProxy(
    double &matrixEntry, SparseMatrixCOO &matrixReference)
    : _matrixEntry(matrixEntry), _matrixReference(matrixReference) {}

SparseMatrixCOO::SparseMatrixCOOProxy::~SparseMatrixCOOProxy() {
  if (_matrixEntry == 0) {
    _matrixReference._eraseNullEntry();
  }
}

SparseMatrixCOO::SparseMatrixCOOProxy::operator double() const {
  return _matrixEntry;
}

SparseMatrixCOO::SparseMatrixCOOProxy &
SparseMatrixCOO::SparseMatrixCOOProxy::operator=(const double &newEntry) {
  std::cout << "Writing operator()= called" << std::endl;
  _matrixEntry = newEntry;
  return *this;
}

SparseMatrixCOO::SparseMatrixCOOProxy &
SparseMatrixCOO::SparseMatrixCOOProxy::operator=(
    const SparseMatrixCOOProxy &otherProxy) {
  std::cout << "Copy operator()= called" << std::endl;
  std::cout << "Matrix entry before: " << _matrixEntry << std::endl;
  std::cout << "Other entry: " << otherProxy._matrixEntry << std::endl;
  _matrixEntry = otherProxy._matrixEntry;
  std::cout << "Matrix entry after: " << _matrixEntry << std::endl;
  return *this;
}

/// Additional comments about the specific implementation.
/// @todo chiedi informazioni riguardo l'errore
SparseMatrixCOO::SparseMatrixCOOProxy
SparseMatrixCOO::operator()(const int &i, const int &j) {
  if (i < 0 || i > _matrixHeight || j < 0 || j > _matrixWidth) {
    throw std::runtime_error("Indices out of bound.");
  }
  return SparseMatrixCOO::SparseMatrixCOOProxy(_getMatrixEntry(i, j), *this);
}
