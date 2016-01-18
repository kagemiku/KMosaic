# KMosaic
[![Build Status](https://travis-ci.org/kagemiku/KMosaic.svg?branch=master)](https://travis-ci.org/kagemiku/KMosaic)

KMosaic is a simple making mosaic library using OpenCV2.
You can use this very easily.

# Require
* C++11
* OpenCV2

# Usage
#### 1. Include KMosaic.h in your code

#### 2. Prepare source cv::Mat and destination cv::Mat, and some information.
For example, if you want to convert it to 100-px square and 100-blocks mosaicing image...
```cpp
const int width     = 100;
const int heigh     = 100;
const int blockRows = 10;
const int blockCols = 10;
```

And, if you want to convert an image which name is **image.png**...
```cpp
std::string srcFilePath("image.png");
cv::Mat src     = cv::imread(srcFilePath);
```

#### 3. Call kg::KMosaic::makeMosaicImage method(this method is a **static** method).
```cpp
cv::Mat dest = kg::KMosaic::makeMosaicImage(src, width, height, blockRows, blockCols);
```

# Caution
Please don't forget link KMosaic.cpp when you compile your codes.

# Example
Please look at the source file **Main.cpp** in examples.

# Author
KAGE

# License
MIT License
