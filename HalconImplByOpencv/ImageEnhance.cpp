#include "ImageEnhance.h"
#include <opencv2/ximgproc.hpp>
void ImageEnhance::CoherenceEnhancingDiff(const cv::Mat src, cv::Mat& res, 
	const int sigma, const int rho, const double theta, 
	const int iter_num) {
	int col = src.cols;
	int row = src.rows;
	cv::Mat iter_img = src.clone();
	for (size_t i = 0; i < iter_num; i++)
	{		
		cv::Mat gray_img;
		cv::cvtColor(iter_img, gray_img, cv::COLOR_BGR2GRAY);
		cv::Mat eigen;
		cv::cornerEigenValsAndVecs(gray_img, eigen, rho, 3);
		std::vector<cv::Mat> split_vec;
		cv::split(eigen, split_vec);
		cv::Mat vec_x = split_vec[2];
		cv::Mat vec_y = split_vec[3];

		cv::Mat grad_x, grad_y, grad_xy;
		cv::Sobel(gray_img, grad_x, CV_32FC1, 2, 0, sigma);
		cv::Sobel(gray_img, grad_xy, CV_32FC1, 1, 1, sigma);
		cv::Sobel(gray_img, grad_y, CV_32FC1, 0, 2, sigma);

		cv::Mat grad(row, col, CV_32FC1, cv::Scalar(0, 0, 0));
		cv::Mat flag_mat(row, col, CV_8UC1, cv::Scalar(0, 0, 0));
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
			{
				auto x = vec_x.at<float>(i, j);
				auto y = vec_y.at<float>(i, j);
				auto g_x = grad_x.at<float>(i, j);
				auto g_y = grad_y.at<float>(i, j);
				auto g_xy = grad_xy.at<float>(i, j);

				auto calc = x * x * g_x + 2 * x * y * g_xy + y * y * g_y;
				grad.at<float>(i, j) = calc;
				flag_mat.at<uchar>(i, j) = calc < 0 ? 1 : 0;
			}
		}
		cv::Mat erode_img, dilate_img;
		cv::Mat se = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
		cv::erode(iter_img, erode_img, se);
		cv::dilate(iter_img, dilate_img, se);

		cv::Mat temp_img = erode_img;
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
			{
				if (flag_mat.at<uchar>(i, j) == 1) {
					temp_img.at<cv::Vec3b>(i, j) = dilate_img.at<cv::Vec3b>(i, j);
				}
			}
		}
		temp_img.convertTo(temp_img, CV_32FC3);
		iter_img.convertTo(iter_img, CV_32FC3);
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
			{
				iter_img.at<cv::Vec3f>(i, j)[0] = iter_img.at<cv::Vec3f>(i, j)[0] * (1.0 - theta) 
					+ temp_img.at<cv::Vec3f>(i, j)[0] * theta;
				iter_img.at<cv::Vec3f>(i, j)[1] = iter_img.at<cv::Vec3f>(i, j)[1] * (1.0 - theta) 
					+ temp_img.at<cv::Vec3f>(i, j)[1] * theta;
				iter_img.at<cv::Vec3f>(i, j)[2] = iter_img.at<cv::Vec3f>(i, j)[2] * (1.0 - theta) 
					+ temp_img.at<cv::Vec3f>(i, j)[2] * theta;
			}
		}   
		iter_img.convertTo(iter_img, CV_8UC3);
	}
	res = iter_img;
}