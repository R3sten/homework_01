#ifndef __SPARSE_MATRIX_CSR__
#define __SPARSE_MATRIX_CSR__

#include "sparse_matrix.hpp"
#include "sparse_matrix_COO.hpp"
#include <vector>

/// @brief A class implementing Compressed Sparse Row Matrix storage scheme.
/// Values have to be allocated in the same order they appear in the matrix.
class SparseMatrixCSR : public SparseMatrix {
private:
  /// @brief Cumulative number of nonzero entries up to the i-throw (excluded).
  /// The size of this vector is m + 1, m being the number of rows of the
  /// matrix. By convention it is assumed that _rowIdx[0] = 0.
  std::vector<int> _rowIdx;

  int _getMatrixEntry(const int &i, const int &j) override;

public:
  /// Constructor.
  SparseMatrixCSR(const std::vector<double> &values,
                  const std::vector<int> &columns,
                  const std::vector<int> &rowIdx, const int &height = 0,
                  const int &width = 0);

  double &operator()(const int &i, const int &j) override;

  void eraseZeroEntries() override;

  std::vector<double> operator*(const std::vector<double> &x) override;

  void printMatrix() override;
};

#endif /* __SPARSE_MATRIX_CSR__ */
