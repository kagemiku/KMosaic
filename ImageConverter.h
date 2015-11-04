#pragma once

#include <string>
#include <opencv2/core/core.hpp>


class ImageConverter {
private:
	enum {
		COLOR_CHANNEL = 3,
		RED_IDX = 2, GREEN_IDX = 1, BLUE_IDX = 0,
	};

	typedef struct RGB {
		int r;
		int g;
		int b;
		RGB(int r_, int g_, int b_) :r(r_), g(g_), b(b_) { }
	} RGB;

private:
	ImageConverter(void);
	ImageConverter(const ImageConverter& rhs);

	static void resizeImage(const cv::Mat& source, cv::Mat& destination, int width, int height);
	static RGB calcMeanColor(const cv::Mat& source, int blockWidth, int blockHeight, int row, int col);
	static void drawMeanColor(cv::Mat& destination, int blockWidth, int blockHeight, int row, int col, const RGB& color);
	static void dropTone(const cv::Mat& source, cv::Mat& destination, int blockRows, int blockCols);

public:
	~ImageConverter(void);

	static void convertImage(const cv::Mat& source, cv::Mat& destination, int width, int height, int blockRows, int blockCols) throw (std::string);
};

