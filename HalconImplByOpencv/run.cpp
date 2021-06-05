#include <iostream>
#include "opencv2/opencv.hpp"
#include <opencv2\imgproc\types_c.h>
#include "ImageEnhance.h"
#include "ImageWriter.h"

int main()
{
    std::string output_str = "F://res.png";
    auto src = cv::imread("F://halcon_example//fingerprint.png");
    cv::Mat res;
    ImageEnhance::CoherenceEnhancingDiff(src, res);
    ImageWriter::WriteImg(res, output_str);
}
