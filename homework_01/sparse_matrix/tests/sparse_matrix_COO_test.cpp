#include "sparse_matrix_COO.hpp"
#include <gtest/gtest.h>
#include <vector>

class SparseMatrixCOOTest : public testing::Test {
protected:
  // Called before every
  void SetUp() override {
    std::vector<int> rows{1, 6, 5, 3, 1};
    std::vector<int> columns{1, 2, 2, 1, 0};
    std::vector<double> values{1, 2.0, 4, 11.3, 0.1};
    testMatrix = new SparseMatrixCOO(rows, columns, values);
  }

  // Called after every test
  void TearDown() override {
    delete testMatrix;
    testMatrix = nullptr;
  }

  // Resource shared by all tests.
  static SparseMatrixCOO *testMatrix;
};

SparseMatrixCOO *SparseMatrixCOOTest::testMatrix = nullptr;

TEST_F(SparseMatrixCOOTest, getNumberOfRows) {
  EXPECT_EQ(7, testMatrix->getNumberOfRows());
}

TEST_F(SparseMatrixCOOTest, getNumberOfColumns) {
  EXPECT_EQ(3, testMatrix->getNumberOfColumns());
}

TEST_F(SparseMatrixCOOTest, getNumberOfNonZeros) {
  EXPECT_EQ(5, testMatrix->getNumberOfNonZeros());
}

// testing operator() for reading, writing and coping matrix entries ->
TEST_F(SparseMatrixCOOTest, readNonZeroEntry) {
  EXPECT_EQ(2, (*testMatrix)(6, 2));
}

TEST_F(SparseMatrixCOOTest, writeNonZeroEntry) {
  (*testMatrix)(6, 2) = 3;
  EXPECT_EQ(3, (*testMatrix)(6, 2));
}

TEST_F(SparseMatrixCOOTest, copyNonZeroToNonZero) {
  (*testMatrix)(6, 2) = (*testMatrix)(5, 2);
  EXPECT_EQ(4, (*testMatrix)(6, 2));
}

TEST_F(SparseMatrixCOOTest, copyNonZeroToItself) {
  (*testMatrix)(5, 2) = (*testMatrix)(5, 2);
  EXPECT_EQ(4, (*testMatrix)(5, 2));
}

TEST_F(SparseMatrixCOOTest, readZeroEntry) {
  EXPECT_EQ(0, (*testMatrix)(6, 1));
}

TEST_F(SparseMatrixCOOTest, writeZeroEntry) {
  (*testMatrix)(5, 1) = 1;
  EXPECT_EQ(1, (*testMatrix)(5, 1));
}

TEST_F(SparseMatrixCOOTest, copyNonZeroToZero) {
  //!!SE nell'input dell'operatore di copy c'è const
  //!!Con (1,1) o con (6,2) NON funziona ma con (5,2) e (3,1), (1,0) SI ?!?!
  //!!indipendentemente dalla null entry su cui scrivo
  (*testMatrix)(0, 0) = (*testMatrix)(1, 1);
  EXPECT_EQ(1, (*testMatrix)(0, 0));
}

TEST_F(SparseMatrixCOOTest, copyZeroToNonZero) {
  (*testMatrix)(1, 1) = (*testMatrix)(4, 1);
  EXPECT_EQ(0, (*testMatrix)(1, 1));
}

TEST_F(SparseMatrixCOOTest, copyZeroToZero) {
  (*testMatrix)(4, 1) = (*testMatrix)(2, 1);
  EXPECT_EQ(0, (*testMatrix)(4, 1));
}

TEST_F(SparseMatrixCOOTest, copyZeroToItself) {
  (*testMatrix)(2, 1) = (*testMatrix)(2, 1);
  EXPECT_EQ(0, (*testMatrix)(2, 1));
}

TEST_F(SparseMatrixCOOTest, throwErrorIfIndicesAreOutOfBound) {
  EXPECT_THROW(
      {
        try {
          (*testMatrix)(4, 8);
        } catch (const std::runtime_error &exc) {
          EXPECT_STREQ("Indices out of bound.", exc.what());
          throw;
        }
      },
      std::runtime_error);
}

TEST_F(SparseMatrixCOOTest, removeNewMatryEntryIfZero) {
  int initalNumberOfNonZeros = testMatrix->getNumberOfNonZeros();
  (*testMatrix)(6, 1) = (*testMatrix)(4, 2);
  EXPECT_EQ(initalNumberOfNonZeros, testMatrix->getNumberOfNonZeros());
}

TEST_F(SparseMatrixCOOTest, removeMatryEntryIfBecamedZero) {
  int initalNumberOfNonZeros = testMatrix->getNumberOfNonZeros();
  (*testMatrix)(1, 1) = (*testMatrix)(2, 2);
  EXPECT_EQ(initalNumberOfNonZeros - 1, testMatrix->getNumberOfNonZeros());
}

TEST_F(SparseMatrixCOOTest, keepNewMatryEntryIfNonZero) {
  int initalNumberOfNonZeros = testMatrix->getNumberOfNonZeros();
  (*testMatrix)(2, 2) = (*testMatrix)(1, 1);
  EXPECT_EQ(initalNumberOfNonZeros + 1, testMatrix->getNumberOfNonZeros());
}

// <- end testing operator()
