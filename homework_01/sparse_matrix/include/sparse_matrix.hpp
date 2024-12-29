#ifndef __SPARSE_MATRIX__
#define __SPARSE_MATRIX__

#include <vector>

/// @brief An abstract class giving a common interface to sparse matrix storage
/// schemes implementations
class SparseMatrix {
protected:
  /// Nonzeros values contained in the matrix.
  std::vector<double> _values;
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
  SparseMatrix(const std::vector<double> &values,
               const std::vector<int> &columns, const int &height = 0,
               const int &width = 0);
  /// Desctructor.
  virtual ~SparseMatrix();

  /// Get matrix number of rows.
  const int &getNumberOfRows() const;
  /// Get matrix number of columns.
  const int &getNumberOfColumns() const;
  /// Get matrix number of nonzero elements.
  int getNumberOfNonZeros() const;

  /// @brief Consent to read or write a specific element of the matrix.
  /// @param i A positivie integer rappresenting the row index of the entry.
  /// @param j A positivie integer rappresenting the column index of the entry.
  /// @return A reference to the entry in the matrix at the position (i,j).
  virtual double &operator()(const int &i, const int &j) = 0;

  /// Cleans memory from allocated zero values
  virtual void eraseZeroEntries() = 0;

  /// Extendes matrix width to the given size
  void extendMatrixWidth(int newWidth);
  /// Extendes matrix height to the given size
  void extendMatrixHeight(int newHeight);

  /// @brief Computes the standard matrix-vector multiplication.
  /// @param x A vector of compatible size.
  /// @return A number representing product result.
  virtual std::vector<double> operator*(const std::vector<double> &x) = 0;

  /// @brief Prints the matrix to the standard output.
  virtual void printMatrix() = 0;
};

#endif /* __SPARSE_MATRIX__ */
