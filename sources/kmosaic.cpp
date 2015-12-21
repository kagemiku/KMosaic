#include "kmosaic.h"
#include <iostream>
#include <string>
#include <opencv2/imgproc/imgproc.hpp>


namespace kg {


KMosaic::~KMosaic()
{
}


auto KMosaic::resizeImage(const cv::Mat& source, cv::Mat& destination, int width, int height) -> void
{
    cv::resize(source, destination, destination.size(), 0, 0, cv::INTER_LINEAR);
}


auto KMosaic::calcMeanColor(const cv::Mat& source, int blockWidth, int blockHeight, int row, int col) -> KMosaic::RGB
{
    auto r = 0, g = 0, b = 0;
    for ( auto i = row*blockHeight; i < (row + 1)*blockHeight; i++ ) {
        for ( auto j = col*blockWidth; j < (col + 1)*blockWidth; j++ ) {
            auto baseIdx = source.step*i + COLOR_CHANNEL*j;
            r += source.data[baseIdx + RED_IDX];
            g += source.data[baseIdx + GREEN_IDX];
            b += source.data[baseIdx + BLUE_IDX];
        }
    }

    const auto numPixel = blockWidth*blockHeight;
    r = static_cast<int>(static_cast<double>(r)/static_cast<double>(numPixel));
    g = static_cast<int>(static_cast<double>(g)/static_cast<double>(numPixel));
    b = static_cast<int>(static_cast<double>(b)/static_cast<double>(numPixel));

    return RGB(r, g, b);
}

 
auto KMosaic::drawMeanColor(cv::Mat& destination, int blockWidth, int blockHeight, int row, int col, const RGB& color) -> void
{
    for ( auto i = row*blockHeight; i < (row + 1)*blockHeight; i++ ) {
        for ( auto j = col*blockWidth; j < (col + 1)*blockWidth; j++ ) {
            auto baseIdx = destination.step*i + COLOR_CHANNEL*j;
            destination.data[baseIdx + RED_IDX]     = color.r;
            destination.data[baseIdx + GREEN_IDX]   = color.g;
            destination.data[baseIdx + BLUE_IDX]    = color.b;
        }
    } 
}


auto KMosaic::dropTone(const cv::Mat& source, cv::Mat& destination, int blockRows, int blockCols) -> void
{
    const auto blockWidth   = destination.size().width/blockCols;
    const auto blockHeight  = destination.size().height/blockRows;
    for ( auto r = 0; r < blockRows; r++ ) {
        for ( auto c = 0; c < blockCols; c++ ) {
            const auto color = calcMeanColor(source, blockWidth, blockHeight, r, c);
            drawMeanColor(destination, blockWidth, blockHeight, r, c, color);
        }
    }
}


auto KMosaic::makeMosaicImage(const cv::Mat& source, int width, int height, int blockRows, int blockCols) throw (std::string) -> cv::Mat
{
    if ( width % blockCols != 0 || height % blockRows != 0 ) {
        throw std::string("invalid params");
    }

    auto tmp = cv::Mat(cv::Size(width, height), CV_8UC3);
    resizeImage(source, tmp, width, height);

    auto destination = tmp.clone();
    dropTone(tmp, destination, blockRows, blockCols);

    return destination;
}


}
