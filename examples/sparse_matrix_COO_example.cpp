#include "sparse_matrix_COO.hpp"
#include <iostream>
#include <vector>

int main() {
  std::vector<int> rows{1, 6, 5, 3, 1};
  std::vector<int> columns{1, 2, 2, 1, 0};
  std::vector<double> values{1, 2.0, 4, 11.3, 0.1};
  SparseMatrixCOO testMatrix = SparseMatrixCOO(values, columns, rows);

  //!!SE nell'input dell'operatore di copy c'è const
  //!!Con (1,1) o con (6,2) NON funziona ma con (5,2) e (3,1), (1,0) SI ?!?!
  //!!indipendentemente dalla null entry su cui scrivo
  testMatrix(0, 0) = testMatrix(6, 2);
  std::cout << "Valore atteso: " << 1 << std::endl
            << "Valore misurato: " << testMatrix(0, 0) << std::endl;

  return 0;
}
