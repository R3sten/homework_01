#ifndef __SPARSE_MATRIX__
#define __SPARSE_MATRIX__

#include <vector>

/// @brief An abstract class giving a common interface to sparse matrix storage
/// schemes implementations
/// @tparam Type of the numbers that will be assigned into the matrix
template <typename T> class SparseMatrix {
protected:
  /// Nonzeros values contained in the matrix.
  std::vector<T> _values;
  /// Column matrix coordinates of nonzeros values.
  std::vector<int> _columns;

  /// Matrix's number of rows.
  int _matrixHeight;
  /// Matrix's number of columns.
  int _matrixWidth;

  /// @brief A map from matrix coordinates to internal vector index.
  /// @param i A non negative integer representing row index.
  /// @param j A non negative integer representing column index.
  /// @return The index of the element in _values which should be accessed.
  virtual int _getMatrixEntry(const int &i, const int &j) = 0;

public:
  /// Constructor.
  SparseMatrix(const std::vector<T> &values, const std::vector<int> &columns,
               const int &height = 0, const int &width = 0);
  /// Desctructor.
  virtual ~SparseMatrix();

  /// Get matrix number of rows.
  int const &getNumberOfRows() const;
  /// Get matrix number of columns.
  int const &getNumberOfColumns() const;
  /// Get matrix number of nonzero elements.
  int getNumberOfNonZeros() const;
  /// Get a vector containing nonzero matrix entries.
  const std::vector<T> &getNonZeroValues() const;
  /// Get a vector containing the column indices of nonzero matrix entries.
  const std::vector<int> &getNonZeroEntriesColumns() const;
  /// Get a vector containing the row indices of nonzero matrix entries.
  virtual std::vector<int> getNonZeroEntriesRows() const = 0;

  /// @brief Consent to read or write a specific element of the matrix.
  /// @param i A positivie integer rappresenting the row index of the entry.
  /// @param j A positivie integer rappresenting the column index of the entry.
  /// @return A reference to the entry in the matrix at the position (i,j).
  virtual T &operator()(const int &i, const int &j) = 0;

  /// Cleans memory from allocated zero values
  virtual void eraseZeroEntries() = 0;

  /// Extendes matrix width to the given size
  void extendMatrixWidth(int newWidth);
  /// Extendes matrix height to the given size
  void extendMatrixHeight(int newHeight);

  /// @brief Computes the standard matrix-vector multiplication. Inptu vector
  /// data should have the same type as matrix entries.
  /// @param x A vector of compatible size.
  /// @return A number representing product result.
  virtual std::vector<T> operator*(const std::vector<T> &x) const = 0;

  /// @brief Prints the matrix to the standard output.
  virtual void printMatrix() const = 0;

  /// @brief SparseMatrix equality comparison.
  /// @return True if nonzero values, their coordinates and matrices sizes are
  /// equal.
  bool operator==(const SparseMatrix &other) const;
};

#include "sparse_matrix.tpl.hpp"

#endif /* __SPARSE_MATRIX__ */
