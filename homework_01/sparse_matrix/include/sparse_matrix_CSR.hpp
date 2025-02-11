#ifndef __SPARSE_MATRIX_CSR__
#define __SPARSE_MATRIX_CSR__

#include "sparse_matrix.hpp"
#include "sparse_matrix_COO.hpp"
#include <vector>

// Forward declaration of SparseMatrixCOO implementation
template <typename T> class SparseMatrixCOO;

/// @brief A class implementing Compressed Sparse Row Matrix storage scheme.
/// Values have to be allocated in the same order they appear in the matrix.
/// @tparam Type of the numbers that will be assigned into the matrix. Default
/// type is set to double.
template <typename T = double> class SparseMatrixCSR : public SparseMatrix<T> {
private:
  /// @brief Cumulative number of nonzero entries up to the i-throw (excluded).
  /// The size of this vector is m + 1, m being the number of rows of the
  /// matrix. By convention it is assumed that _rowIdx[0] = 0.
  std::vector<int> _rowIdx;

  int _getMatrixEntry(const int &i, const int &j) override;

  using SparseMatrix<T>::_values;
  using SparseMatrix<T>::_columns;
  using SparseMatrix<T>::_matrixHeight;
  using SparseMatrix<T>::_matrixWidth;

public:
  /// Constructor.
  SparseMatrixCSR(const std::vector<T> &values, const std::vector<int> &columns,
                  const std::vector<int> &rowIdx, const int &height = 0,
                  const int &width = 0);

  T &operator()(const int &i, const int &j) override;

  void eraseZeroEntries() override;

  std::vector<T> operator*(const std::vector<T> &x) const override;

  void printMatrix() const override;

  std::vector<int> getNonZeroEntriesRows() const override;

  /// @brief Creates a copy of the current sparse matrix stored with the
  /// Coordinate storage scheme.
  /// @return A SparseMatrixCOO object with the same nonzero values.
  SparseMatrixCOO<T> toCooridnateStorageScheme();
};

#include "sparse_matrix_CSR.tpl.hpp"

#endif /* __SPARSE_MATRIX_CSR__ */
