#include "sparse_matrix_CSR.hpp"
#include <gtest/gtest.h>
#include <vector>

class SparseMatrixCSRTest : public testing::Test {
protected:
  // Called before every
  void SetUp() override {
    std::vector<double> values{0.1, 1, 11.3, 4, 2};
    std::vector<int> columns{0, 1, 1, 2, 2};
    std::vector<int> rowIdx{0, 0, 2, 2, 3, 3, 4, 5};
    testMatrix = new SparseMatrixCSR(values, columns, rowIdx, 7, 3);
  }

  // Called after every test
  void TearDown() override {
    delete testMatrix;
    testMatrix = nullptr;
  }

  // Resource shared by all tests.
  static SparseMatrixCSR *testMatrix;
};

SparseMatrixCSR *SparseMatrixCSRTest::testMatrix = nullptr;

TEST_F(SparseMatrixCSRTest, getNumberOfRows) {
  EXPECT_EQ(7, testMatrix->getNumberOfRows());
}

TEST_F(SparseMatrixCSRTest, getNumberOfColumns) {
  EXPECT_EQ(3, testMatrix->getNumberOfColumns());
}

TEST_F(SparseMatrixCSRTest, getNumberOfNonZeros) {
  EXPECT_EQ(5, testMatrix->getNumberOfNonZeros());
}

// testing operator() for reading, writing and coping matrix entries ->
TEST_F(SparseMatrixCSRTest, readNonZeroEntry) {
  EXPECT_EQ(2, (*testMatrix)(6, 2));
}

TEST_F(SparseMatrixCSRTest, writeNonZeroEntry) {
  (*testMatrix)(6, 2) = 3;
  EXPECT_EQ(3, (*testMatrix)(6, 2));
}

TEST_F(SparseMatrixCSRTest, copyNonZeroToNonZero) {
  (*testMatrix)(6, 2) = (*testMatrix)(5, 2);
  EXPECT_EQ(4, (*testMatrix)(6, 2));
}

TEST_F(SparseMatrixCSRTest, copyNonZeroToNonZeroDifferentMatrixs) {
  SparseMatrixCSR testMatrix2 = *testMatrix;
  (*testMatrix)(6, 2) = testMatrix2(5, 2);
  EXPECT_EQ(4, (*testMatrix)(6, 2));
}

TEST_F(SparseMatrixCSRTest, copyNonZeroToItself) {
  (*testMatrix)(5, 2) = (*testMatrix)(5, 2);
  EXPECT_EQ(4, (*testMatrix)(5, 2));
}

TEST_F(SparseMatrixCSRTest, readZeroEntry) {
  EXPECT_EQ(0, (*testMatrix)(6, 1));
}

TEST_F(SparseMatrixCSRTest, writeZeroEntry) {
  (*testMatrix)(5, 1) = 1;
  EXPECT_EQ(1, (*testMatrix)(5, 1));
}

TEST_F(SparseMatrixCSRTest, copyNonZeroToZero) {
  (*testMatrix)(0, 0) = (*testMatrix)(1, 1);
  EXPECT_EQ(1, (*testMatrix)(0, 0));
}

TEST_F(SparseMatrixCSRTest, copyNonZeroToZeroDifferentMatrixs) {
  SparseMatrixCSR testMatrix2 = *testMatrix;
  (*testMatrix)(0, 0) = testMatrix2(6, 2);
  EXPECT_EQ(2, (*testMatrix)(0, 0));
}

TEST_F(SparseMatrixCSRTest, copyZeroToNonZero) {
  (*testMatrix)(1, 1) = (*testMatrix)(4, 1);
  EXPECT_EQ(0, (*testMatrix)(1, 1));
}

TEST_F(SparseMatrixCSRTest, copyZeroToZero) {
  (*testMatrix)(4, 1) = (*testMatrix)(2, 1);
  EXPECT_EQ(0, (*testMatrix)(2, 1));
}

TEST_F(SparseMatrixCSRTest, copyZeroToItself) {
  (*testMatrix)(2, 1) = (*testMatrix)(2, 1);
  EXPECT_EQ(0, (*testMatrix)(2, 1));
}

TEST_F(SparseMatrixCSRTest, throwErrorIfInputIndicesAreOutOfBound) {
  const std::string expectedError = "Indices out of bound.";
  EXPECT_THROW(
      {
        try {
          (*testMatrix)(4, 8);
        } catch (const std::runtime_error &exc) {
          EXPECT_STREQ(expectedError.c_str(), exc.what());
          throw;
        }
      },
      std::runtime_error);
}

TEST_F(SparseMatrixCSRTest, removeNewMatryEntriesIfZero) {
  int initalNumberOfNonZeros = testMatrix->getNumberOfNonZeros();
  (*testMatrix)(6, 1) = (*testMatrix)(4, 2);
  testMatrix->eraseZeroEntries();
  EXPECT_EQ(initalNumberOfNonZeros, testMatrix->getNumberOfNonZeros());
}

TEST_F(SparseMatrixCSRTest, removeMatryEntryIfBecamedZero) {
  int initalNumberOfNonZeros = testMatrix->getNumberOfNonZeros();
  (*testMatrix)(1, 1) = (*testMatrix)(2, 2);
  testMatrix->eraseZeroEntries();
  EXPECT_EQ(initalNumberOfNonZeros - 1, testMatrix->getNumberOfNonZeros());
}

TEST_F(SparseMatrixCSRTest, keepNewMatryEntryIfNonZero) {
  int initalNumberOfNonZeros = testMatrix->getNumberOfNonZeros();
  (*testMatrix)(2, 2) = (*testMatrix)(1, 1);
  testMatrix->eraseZeroEntries();
  EXPECT_EQ(initalNumberOfNonZeros + 1, testMatrix->getNumberOfNonZeros());
}

// <- end testing operator()

TEST_F(SparseMatrixCSRTest, extendMatrixHeight) {
  int newHeight = 10;
  testMatrix->extendMatrixHeight(newHeight);
  EXPECT_EQ(newHeight, testMatrix->getNumberOfRows());
}

TEST_F(SparseMatrixCSRTest, extendMatrixWidth) {
  int newWidth = 10;
  testMatrix->extendMatrixWidth(newWidth);
  EXPECT_EQ(newWidth, testMatrix->getNumberOfColumns());
}

TEST_F(SparseMatrixCSRTest, throwErrorVectorSizeIsNotCompatible) {
  std::vector<double> testVector{1, 2, 3, 4};
  const std::string expectedError =
      "Input vector does not have compatible size. Expected: " +
      std::to_string(testMatrix->getNumberOfColumns()) +
      ", actual: " + std::to_string(testVector.size()) + ".";
  EXPECT_THROW(
      {
        try {
          (*testMatrix) * testVector;
        } catch (const std::runtime_error &exc) {
          EXPECT_STREQ(expectedError.c_str(), exc.what());
          throw;
        }
      },
      std::runtime_error);
}

TEST_F(SparseMatrixCSRTest, productOutputSize) {
  std::vector<double> testVector{1, 2, 3};
  std::vector<double> resultVector = (*testMatrix) * testVector;
  EXPECT_EQ(testMatrix->getNumberOfRows(), resultVector.size());
}

TEST_F(SparseMatrixCSRTest, productResult) {
  std::vector<double> testVector{1, 2, 3};
  std::vector<double> expectedResult{0, 2.1, 0, 22.6, 0, 12, 6};
  std::vector<double> resultVector = (*testMatrix) * testVector;
  EXPECT_EQ(expectedResult, resultVector);
}

TEST_F(SparseMatrixCSRTest, printMatrix) {
  std::string expectedOutput = "     0      0      0 \n"
                               "   0.1      1      0 \n"
                               "     0      0      0 \n"
                               "     0   11.3      0 \n"
                               "     0      0      0 \n"
                               "     0      0      4 \n"
                               "     0      0      2 \n";
  testing::internal::CaptureStdout();
  testMatrix->printMatrix();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(expectedOutput, output);
}