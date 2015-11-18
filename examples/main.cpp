#include <iostream>
#include <string>
#include "../KMosaic.h"
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

    cv::Mat dest = cv::Mat::zeros(cv::Size(width, height), CV_8UC3);
    try { 
        KMosaic::convertImage(src, dest, width, height, blockRows, blockCols);
    } catch ( const string& msg ) {
        cerr << msg << endl;
        exit(1);
    }

    // write some processes...
	
    return 0;
}
