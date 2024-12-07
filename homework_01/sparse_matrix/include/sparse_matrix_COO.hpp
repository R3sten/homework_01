#ifndef __SPARSE_MATRIX_COO__
#define __SPARSE_MATRIX_COO__

#include <vector>

class SparseMatrixCOO {
private:
  /// @brief Row matrix coordinates of nonzeros values
  std::vector<int> _rows;
  /// @brief Column matrix coordinates of nonzeros values
  std::vector<int> _columns;
  /// @brief Nonzeros values contained in the matrix
  std::vector<double> _values;

  /// @brief Matrix's number of rows
  int _matrixHeight;
  /// @brief Matrix's number of columns
  int _matrixWidth;

  double &_getMatrixEntry(const int &i, const int &j);
  void _eraseNullEntry();

protected:
  // TODO: define externally
  /// @brief A proxy class necessary for accessing throught the same interface a
  /// %SparseMatrix element for both reading and writing.
  class SparseMatrixCOOProxy {
  private:
    /// @brief A reference to the selected matrix element
    double &_matrixEntry;
    /// @brief A reference to the matrix class that gives access its functions
    SparseMatrixCOO &_matrixReference;

  public:
    SparseMatrixCOOProxy(double &matrixEntry, SparseMatrixCOO &matrixReference);
    ~SparseMatrixCOOProxy();

    /// @brief Reading operator
    operator double() const;

    /// @brief Writing operator.
    /// @param newEntry Value to be added to the matrix at the (i, j) position.
    /// @return A reference to the specified matrix element.
    SparseMatrixCOOProxy &operator=(const double &newEntry);

    /// @brief Copy assignment operator.
    /// @param otherProxy The matrix element to be copied to the left matrix
    /// element instance.
    /// @return A reference to the left matrix element.
    SparseMatrixCOOProxy &operator=(SparseMatrixCOOProxy &otherProxy);
    //! The input is not const becouse that gives copy errors
    //!! It took a day for me to find that out :(
  };

public:
  SparseMatrixCOO(std::vector<int> &rows, std::vector<int> &columns,
                  std::vector<double> &values);
  // SparseMatrixCOO(double *matrix);
  ~SparseMatrixCOO();

  const int &getNumberOfRows() const;
  const int &getNumberOfColumns() const;
  int getNumberOfNonZeros() const;

  /// @brief The operator() consent to read or write a specific element of the
  /// matrix.
  /// @param i A positivie integer rappresenting the row index of the entry.
  /// @param j A positivie integer rappresenting the column index of the entry.
  /// @return A reference to the entry in the matrix at the position (i, j).
  SparseMatrixCOOProxy operator()(const int &i, const int &j);

  /// @brief Computes the standard matrix-vector product.
  /// @tparam I Type of the elements into input vector.
  /// @tparam R Type of the product output; by default is set to %double.
  /// @param x A vector of compatible size.
  /// @return A number representing product result.
  // template <typename I, typename R = double> R &operator*(const vector<I>
  // &x);

  /// @brief Prints the matrix to the standard output.
  // virtual void printMatrix() = 0;
};

#endif /* __SPARSE_MATRIX_COO__ */
