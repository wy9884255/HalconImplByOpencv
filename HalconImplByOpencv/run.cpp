#include <iostream>
#include "opencv2/opencv.hpp"
#include <opencv2\imgproc\types_c.h>
#include "ImageEnhance.h"
#include "ImageWriter.h"

#ifdef _DEBUG
#pragma comment(lib,"..\\ThirdParty\\opencv\\lib\\opencv_world450d.lib")
#else
#pragma comment(lib,"..\\ThirdParty\\opencv\\lib\\opencv_world450.lib")
#endif

int main()
{
    std::string output_str = "F://res.png";
    auto src = cv::imread("F://halcon_example//fingerprint.png");
    cv::Mat res;
    ImageEnhance::CoherenceEnhancingDiff(src, res);
    ImageWriter::WriteImg(res, output_str);
}
