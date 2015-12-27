#include <iostream>
#include <string>
#include "../sources/kmosaic.h"
#include <opencv2/highgui/highgui.hpp>
using namespace std;


auto main() -> int
{
    const int width     = 100;
    const int height    = 100;
    const int blockRows = 10;
    const int blockCols = 10;

    string srcFilePath("image.png");
    cv::Mat src = cv::imread(srcFilePath);
    if ( src.empty() ) {
        cerr << srcFilePath << " can't be read." << endl;
        exit(1);
    }

    cv::Mat dest;
    try {
        dest = kg::KMosaic::makeMosaicImage(src, width, height, blockRows, blockCols);
    } catch ( const string& msg ) {
        cerr << msg << endl;
        exit(1);
    }

    const string windowName("Result");
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
    cv::imshow(windowName, dest);
    cv::waitKey(0);

    return 0;
}
