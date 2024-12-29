#ifndef __SPARSE_MATRIX_COO__
#define __SPARSE_MATRIX_COO__

#include "sparse_matrix.hpp"
#include "sparse_matrix_CSR.hpp"
#include <vector>

/// @brief A class implementing Coordinate Sparse Matrix storage scheme.
class SparseMatrixCOO : public SparseMatrix {
private:
  /// Row matrix coordinates of nonzeros values.
  std::vector<int> _rows;

  int _getMatrixEntry(const int &i, const int &j) override;

public:
  /// Constructor.
  SparseMatrixCOO(const std::vector<double> &values,
                  const std::vector<int> &columns, const std::vector<int> &rows,
                  const int &height = 0, const int &width = 0);

  double &operator()(const int &i, const int &j) override;

  void eraseZeroEntries() override;

  std::vector<double> operator*(const std::vector<double> &x) override;

  void printMatrix() override;
};

#endif /* __SPARSE_MATRIX_COO__ */
