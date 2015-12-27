#include <gtest/gtest.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include "../sources/kmosaic.h"


class KMosaicTest : public ::testing::Test {
protected:
    const int width;
    const int height;
    int validBlockRows;
    int validBlockCols;
    int invalidBlockRows;
    int invalidBlockCols;

protected:
    KMosaicTest()
        :width(10)
        ,height(10)
    {
    }

    ~KMosaicTest()
    {
    }

    virtual auto SetUp() -> void
    {
        validBlockRows = 2;
        validBlockCols = 2;

        invalidBlockRows = 3;
        invalidBlockCols = 3;
    }

    virtual auto TearDown() -> void
    {
    }

    static auto SetUpTestCase() -> void
    {
    }

    static auto TearDownTestCase() -> void
    {
    }
};

TEST_F(KMosaicTest, ValidParameters)
{
    cv::Mat mat(cv::Size(width, height), CV_8UC3);
    ASSERT_NO_THROW(kg::KMosaic::makeMosaicImage(mat, width, height, validBlockRows, validBlockCols));
}

TEST_F(KMosaicTest, InvalidParameters)
{
    cv::Mat mat(cv::Size(width, height), CV_8UC3);
    ASSERT_THROW(kg::KMosaic::makeMosaicImage(mat, width, height, invalidBlockRows, invalidBlockCols), std::string);
    ASSERT_THROW(kg::KMosaic::makeMosaicImage(mat, width, height, validBlockRows, invalidBlockCols), std::string);
    ASSERT_THROW(kg::KMosaic::makeMosaicImage(mat, width, height, invalidBlockRows, validBlockCols), std::string);
}

TEST_F(KMosaicTest, ConvertedSize)
{
    cv::Mat originalMat(cv::Size(width, height), CV_8UC3);
    auto convertedMat =  kg::KMosaic::makeMosaicImage(originalMat, width, height, validBlockRows, validBlockCols);

    ASSERT_EQ(width, convertedMat.cols);
    ASSERT_EQ(height, convertedMat.rows);
}

