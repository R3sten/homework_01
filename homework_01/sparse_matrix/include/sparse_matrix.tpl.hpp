#ifndef __SPARSE_MATRIX_TPL__
#define __SPARSE_MATRIX_TPL__
#include "sparse_matrix.hpp"

template <typename T>
const std::vector<int> &SparseMatrix<T>::getNonZeroEntriesColumns() const {
  return _columns;
}

template <typename T>
SparseMatrix<T>::SparseMatrix(const std::vector<T> &values,
                              const std::vector<int> &columns,
                              const int &height, const int &width)
    : _values(values), _columns(columns), _matrixHeight(height),
      _matrixWidth(width) {}

template <typename T> SparseMatrix<T>::~SparseMatrix<T>() = default;

template <typename T> int const &SparseMatrix<T>::getNumberOfRows() const {
  return _matrixHeight;
}

template <typename T> int const &SparseMatrix<T>::getNumberOfColumns() const {
  return _matrixWidth;
}

template <typename T> int SparseMatrix<T>::getNumberOfNonZeros() const {
  return _values.size();
}

template <typename T>
const std::vector<T> &SparseMatrix<T>::getNonZeroValues() const {
  return _values;
}

template <typename T> void SparseMatrix<T>::extendMatrixWidth(int newWidth) {
  _matrixWidth = newWidth;
}

template <typename T> void SparseMatrix<T>::extendMatrixHeight(int newHeight) {
  _matrixHeight = newHeight;
}

template <typename T>
bool SparseMatrix<T>::operator==(const SparseMatrix<T> &b) const {
  if (getNonZeroValues() == b.getNonZeroValues() &&
      getNonZeroEntriesColumns() == b.getNonZeroEntriesColumns() &&
      getNonZeroEntriesRows() == b.getNonZeroEntriesRows() &&
      getNumberOfRows() == b.getNumberOfRows() &&
      getNumberOfColumns() == b.getNumberOfColumns()) {
    return true;
  } else {
    return false;
  }
}

#endif /* __SPARSE_MATRIX_TPL__ */
