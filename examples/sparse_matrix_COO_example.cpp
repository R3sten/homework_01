#include "sparse_matrix_COO.hpp"
#include <iostream>
#include <vector>

int main() {
  std::vector<int> rows{1, 6, 5, 3, 1};
  std::vector<int> columns{1, 2, 2, 1, 0};
  std::vector<double> values{1, 2.0, 4, 11.3, 0.1};
  SparseMatrixCOO testMatrix = SparseMatrixCOO(values, columns, rows);

  return 0;
}
