#include "ImageConverter.h"
#include <iostream>
#include <string>
#include <opencv2/imgproc/imgproc.hpp>


ImageConverter::~ImageConverter()
{
}


auto ImageConverter::resizeImage(const cv::Mat& source, cv::Mat& destination, int width, int height) -> void
{
	cv::resize(source, destination, destination.size(), 0, 0, cv::INTER_LINEAR);
}


auto ImageConverter::calcMeanColor(const cv::Mat& source, int blockWidth, int blockHeight, int row, int col) -> ImageConverter::RGB
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

 
auto ImageConverter::drawMeanColor(cv::Mat& destination, int blockWidth, int blockHeight, int row, int col, const RGB& color) -> void
{
	for ( auto i = row*blockHeight; i < (row + 1)*blockHeight; i++ ) {
		for ( auto j = col*blockWidth; j < (col + 1)*blockWidth; j++ ) {
			auto baseIdx = destination.step*i + COLOR_CHANNEL*j;
			destination.data[baseIdx + RED_IDX]		= color.r;
			destination.data[baseIdx + GREEN_IDX]	= color.g;
			destination.data[baseIdx + BLUE_IDX]	= color.b;
		}
	} 
}


auto ImageConverter::dropTone(const cv::Mat& source, cv::Mat& destination, int blockRows, int blockCols) -> void
{
	const auto blockWidth	= destination.size().width/blockCols;
	const auto blockHeight	= destination.size().height/blockRows;
	for ( auto r = 0; r < blockRows; r++ ) {
		for ( auto c = 0; c < blockCols; c++ ) {
			const auto color = calcMeanColor(source, blockWidth, blockHeight, r, c);
			drawMeanColor(destination, blockWidth, blockHeight, r, c, color);
		}
	}
}


auto ImageConverter::convertImage(const cv::Mat& source, cv::Mat& destination, int width, int height, int blockRows, int blockCols) throw (std::string) -> void
{
	if ( width % blockCols != 0 || height % blockRows != 0 ) {
		throw std::string("invalid params");
	}

	auto tmp = destination.clone();
	resizeImage(source, tmp, width, height);
	dropTone(tmp, destination, blockRows, blockCols);
}
