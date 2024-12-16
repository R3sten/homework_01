#ifndef __SPARSE_MATRIX_COO__
#define __SPARSE_MATRIX_COO__

#include <vector>

/// @brief A class implementing Coordinate Sparse Matrix storage scheme.
class SparseMatrixCOO {
private:
  /// Row matrix coordinates of nonzeros values.
  std::vector<int> _rows;
  /// Column matrix coordinates of nonzeros values.
  std::vector<int> _columns;
  /// Nonzeros values contained in the matrix.
  std::vector<double> _values;

  /// Matrix's number of rows.
  int _matrixHeight;
  /// Matrix's number of columns.
  int _matrixWidth;

  /// @brief A map from matrix coordinates to internal vector index.
  /// @param i A non negative integer representing row index.
  /// @param j A non negative integer representing column index.
  /// @return The index of the element in _values which should be accessed.
  int _getMatrixEntry(const int &i, const int &j);

protected:
  /// @brief A proxy class necessary for accessing throught the same interface a
  /// SparseMatrixCOO element for both reading and writing.
  class SparseMatrixCOOProxy {
  private:
    ///  An internal index to the selected matrix element.
    int _idx;
    /// A reference to the matrix class to which the entry belongs.
    SparseMatrixCOO &_matrix;

  public:
    /// Constructor.
    SparseMatrixCOOProxy(int idx, SparseMatrixCOO &matrix);
    /// Default destructor.
    ~SparseMatrixCOOProxy();

    /// Reading operator.
    operator double() const;

    /// Writing operator.
    /// @param newEntry Value to be added to the matrix at the (i, j) position.
    /// @return A reference to the specified matrix element.
    SparseMatrixCOOProxy &operator=(const double &newEntry);

    /// Copy assignment operator.
    /// @param other The matrix element to be copied to the left matrix
    /// element instance.
    /// @return A reference to the left matrix element.
    SparseMatrixCOOProxy &operator=(const SparseMatrixCOOProxy &otherProxy);
  };

public:
  /// Constructor.
  SparseMatrixCOO(std::vector<int> &rows, std::vector<int> &columns,
                  std::vector<double> &values);
  /// Copy constructor.
  SparseMatrixCOO(const SparseMatrixCOO &otherMatrix);
  /// Defalut destructor.
  ~SparseMatrixCOO();

  /// Get matrix number of rows.
  const int &getNumberOfRows() const;
  /// Get matrix number of columns.
  const int &getNumberOfColumns() const;
  /// Get matrix number of nonzero elements.
  int getNumberOfNonZeros() const;

  /// Copy assignment operator.
  SparseMatrixCOO &operator=(const SparseMatrixCOO &otherMatrix);

  /// @brief Consent to read or write a specific element of the matrix.
  /// @param i A positivie integer rappresenting the row index of the entry.
  /// @param j A positivie integer rappresenting the column index of the entry.
  /// @return A reference to the entry in the matrix at the position (i, j).
  SparseMatrixCOOProxy operator()(const int &i, const int &j);

  /// Cleans matrix from allocated zero values
  void eraseZeroEntries();

  /// Extendes matrix width to the given size
  void extendMatrixWidth(int newWidth);
  /// Extendes matrix height to the given size
  void extendMatrixHeight(int newHeight);

  /// @brief Computes the standard matrix-vector multiplication.
  /// @param x A vector of compatible size.
  /// @return A number representing product result.
  std::vector<double> operator*(const std::vector<double> &x);

  /// @brief Prints the matrix to the standard output.
  void printMatrix();
};

#endif /* __SPARSE_MATRIX_COO__ */
