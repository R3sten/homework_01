#include "sparse_matrix.hpp"

SparseMatrix::SparseMatrix(const std::vector<double> &values,
                           const std::vector<int> &columns, const int &height,
                           const int &width)
    : _values(values), _columns(columns), _matrixHeight(height),
      _matrixWidth(width) {}

SparseMatrix::~SparseMatrix() = default;

const int &SparseMatrix::getNumberOfRows() const { return _matrixHeight; }

const int &SparseMatrix::getNumberOfColumns() const { return _matrixWidth; }

int SparseMatrix::getNumberOfNonZeros() const { return _values.size(); }

void SparseMatrix::extendMatrixWidth(int newWidth) { _matrixWidth = newWidth; }

void SparseMatrix::extendMatrixHeight(int newHeight) {
  _matrixHeight = newHeight;
}