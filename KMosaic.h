#pragma once

#include <string>
#include <opencv2/core/core.hpp>


class KMosaic {
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

    static auto resizeImage(const cv::Mat& source, cv::Mat& destination, int width, int height) -> void;
    static auto calcMeanColor(const cv::Mat& source, int blockWidth, int blockHeight, int row, int col) -> RGB;
    static auto drawMeanColor(cv::Mat& destination, int blockWidth, int blockHeight, int row, int col, const RGB& color) -> void;
    static auto dropTone(const cv::Mat& source, cv::Mat& destination, int blockRows, int blockCols) -> void;

public:
    KMosaic() = delete;
    KMosaic(const KMosaic& rhs) = delete;
    ~KMosaic();
    auto operator=(const KMosaic& rhs) -> KMosaic* = delete;

    static auto makeMosaicImage(const cv::Mat& source, cv::Mat& destination, int width, int height, int blockRows, int blockCols) throw (std::string) -> void;
};

