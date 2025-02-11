#ifndef __SPARSE_MATRIX_COO__
#define __SPARSE_MATRIX_COO__

#include "sparse_matrix.hpp"
#include "sparse_matrix_CSR.hpp"
#include <vector>

// Forward declaration of SparseMatrixCSR implementation
template <typename T> class SparseMatrixCSR;

/// @brief A class implementing Coordinate Sparse Matrix storage scheme.
/// @tparam Type of the numbers that will be assigned into the matrix. Default
/// type is set to double.
template <typename T = double> class SparseMatrixCOO : public SparseMatrix<T> {
private:
  using SparseMatrix<T>::_values;
  using SparseMatrix<T>::_columns;
  using SparseMatrix<T>::_matrixHeight;
  using SparseMatrix<T>::_matrixWidth;

  /// Row matrix coordinates of nonzeros values.
  std::vector<int> _rows;

  int _getMatrixEntry(const int &i, const int &j) override;

  /// Reorder @ref _values elements as they appear in the matrix.
  void _adjustNonZeroValuesStorageOrder();

public:
  /// Constructor.
  SparseMatrixCOO(const std::vector<T> &values, const std::vector<int> &columns,
                  const std::vector<int> &rows, const int &height = 0,
                  const int &width = 0);

  T &operator()(const int &i, const int &j) override;

  void eraseZeroEntries() override;

  std::vector<T> operator*(const std::vector<T> &x) const override;

  void printMatrix() const override;

  std::vector<int> getNonZeroEntriesRows() const override;

  /// @brief Creates a copy of the current sparse matrix stored with the
  /// Compressed Sparse Row storage scheme.
  /// @return A SparseMatrixCSR object with the same nonzero values.
  SparseMatrixCSR<T> toCompressedRowStorageScheme();
};

#include "sparse_matrix_COO.tpl.hpp"

#endif /* __SPARSE_MATRIX_COO__ */
