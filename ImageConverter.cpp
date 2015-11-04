#include "ImageConverter.h"
#include <iostream>
#include <string>
#include <opencv2/imgproc/imgproc.hpp>


ImageConverter::~ImageConverter(void)
{
}


void ImageConverter::resizeImage(const cv::Mat& source, cv::Mat& destination, int width, int height)
{
	cv::resize(source, destination, destination.size(), 0, 0, cv::INTER_LINEAR);
}


ImageConverter::RGB ImageConverter::calcMeanColor(const cv::Mat& source, int blockWidth, int blockHeight, int row, int col)
{
	int r = 0, g = 0, b = 0;
	for ( int i = row*blockHeight; i < (row + 1)*blockHeight; i++ ) {
		for ( int j = col*blockWidth; j < (col + 1)*blockWidth; j++ ) {
			int baseIdx = source.step*i + COLOR_CHANNEL*j;
			r += source.data[baseIdx + RED_IDX];
			g += source.data[baseIdx + GREEN_IDX];
			b += source.data[baseIdx + BLUE_IDX];
		}
	}

	const int numPixel = blockWidth*blockHeight;
	r = static_cast<int>(static_cast<double>(r)/static_cast<double>(numPixel));
	g = static_cast<int>(static_cast<double>(g)/static_cast<double>(numPixel));
	b = static_cast<int>(static_cast<double>(b)/static_cast<double>(numPixel));

	return RGB(r, g, b);
}

 
void ImageConverter::drawMeanColor(cv::Mat& destination, int blockWidth, int blockHeight, int row, int col, const RGB& color)
{
	for ( int i = row*blockHeight; i < (row + 1)*blockHeight; i++ ) {
		for ( int j = col*blockWidth; j < (col + 1)*blockWidth; j++ ) {
			int baseIdx = destination.step*i + COLOR_CHANNEL*j;
			destination.data[baseIdx + RED_IDX]		= color.r;
			destination.data[baseIdx + GREEN_IDX]	= color.g;
			destination.data[baseIdx + BLUE_IDX]	= color.b;
		}
	} 
}


void ImageConverter::dropTone(const cv::Mat& source, cv::Mat& destination, int blockRows, int blockCols)
{
	const int blockWidth	= destination.size().width/blockCols;
	const int blockHeight	= destination.size().height/blockRows;
	for ( int r = 0; r < blockRows; r++ ) {
		for ( int c = 0; c < blockCols; c++ ) {
			const RGB color = calcMeanColor(source, blockWidth, blockHeight, r, c);
			drawMeanColor(destination, blockWidth, blockHeight, r, c, color);
		}
	}
}


void ImageConverter::convertImage(const cv::Mat& source, cv::Mat& destination, int width, int height, int blockRows, int blockCols) throw (std::string)
{
	if ( width % blockCols != 0 || height % blockRows != 0 ) {
		throw std::string("invalid params");
	}

	cv::Mat tmp = destination.clone();
	resizeImage(source, tmp, width, height);
	dropTone(tmp, destination, blockRows, blockCols);
}
