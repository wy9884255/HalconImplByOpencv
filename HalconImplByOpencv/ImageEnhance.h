#pragma once
#include "opencv2/opencv.hpp"
class ImageEnhance {
public:
	/// <summary>
	/// 各项异性扩散（Anisotropic diffusion）增强图像连贯性,保持图像细节特征的同时减少噪声
	/// https://www.mvtec.com/doc/halcon/13/en/coherence_enhancing_diff.html
	/// test_img "fingerprint.png"
	/// </summary>
	static void CoherenceEnhancingDiff(const cv::Mat src, cv::Mat& res,
		const int sigma = 19, const int rho = 19, const double theta = 0.7,
		const int iter_num = 4);

private:
	ImageEnhance();
};
