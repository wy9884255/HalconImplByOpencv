#pragma once
#include "opencv2/opencv.hpp"
class ImageWriter {
public:
	static inline void WriteImg(const cv::Mat src, const std::string path) {
		cv::imwrite(path, src);
	}
private:
	ImageWriter();
};