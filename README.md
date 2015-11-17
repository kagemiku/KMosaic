# KMosaic
KMosaic is a simple making mosaic library using OpenCV2.
You can use this very easily.

# Require
* C++11
* OpenCV2

# Usage
1. Include ImageConverter.h in your code

2. Prepare source cv::Mat and destination cv::Mat, and some information.
For example, if you want to convert an image which name is **image.png**...  
```cpp
std::string srcFilePath("image.png");
cv::Mat src     = cv::imread(srcFilePath);
cv::Mat dest    = src.clone();
```

And, if you want to convert it to 100-px square and 100-blocks mosaicing image...
```cpp
const int width     = 100;
const int heigh     = 100;
const int blockRows = 10;
const int blockCols = 10;
``` 

3. Call ImageConverter::convertImage method(this method is a **static** method).
```cpp 
ImageConverter::convertImage(src, dest, width, height, blockRows, blockCols);
```

# License
MIT License
