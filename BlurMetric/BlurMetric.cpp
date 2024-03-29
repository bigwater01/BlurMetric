// BlurMetric.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"

using cv::Mat;
using namespace std;


int main(int argc, char **argv)
{

	if (argc != 3)
	{
		cout << "invalid usage, try using 'blurMetric.exe [INPUT_IMAGE] [OUTPUT_IMAGE]'" << endl;
		return 0;
	}

	string fn_in = argv[1];
	string fn_out = argv[2];

	try
	{
		Mat image_in = cv::imread(fn_in);
		Mat image_out = blurMetric(image_in);

		return 0;
	}
	catch (int e)
	{
		return e;
	}

}

Mat blurMetric(Mat &image_in)
{
	float kernel[1][9] = { { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 } };
	Mat hh = Mat(1, 9, CV_32FC1, &kernel);
	hh = hh / 9;
	Mat hv = hh.t();

	Mat b_ver, b_hor;
	Mat input(image_in, CV_32FC3);
	const size_t rows = input.rows;
	const size_t cols = input.cols;

	filter2D(input, b_hor, -1, hh, cv::Point(-1, -1), 0, cv::BORDER_CONSTANT);
	filter2D(input, b_ver, -1, hv, cv::Point(-1, -1), 0, cv::BORDER_CONSTANT);

	Mat d_f_ver = cv::Mat::zeros(rows, cols, CV_32FC3);
	Mat d_f_hor = cv::Mat::zeros(rows, cols, CV_32FC3);

	for (int i = 0; i != rows; i++)
		for (int j = 0; j != cols - 1; j++)
			for (int k = 0; k != 3; k++)
				d_f_ver.at<float>(i, j, k) = cv::abs(input.at<float>(i, j, k) - input.at<float>(i, j + 1, k));

	for (int i = 0; i != rows - 1; i++)
		for (int j = 0; j != cols; j++)
			for (int k = 0; k != 3; k++)
				d_f_hor.at<float>(i, j, k) = cv::abs(input.at<float>(i, j, k) - input.at<float>(i + 1, j, k));

	Mat d_b_ver = cv::Mat::zeros(rows, cols, CV_32FC3);
	Mat d_b_hor = cv::Mat::zeros(rows, cols, CV_32FC3);

	for (int i = 0; i != rows; i++)
		for (int j = 0; j != cols - 1; j++)
			for (int k = 0; k != 3; k++)
				d_b_ver.at<float>(i, j, k) = cv::abs(d_f_ver.at<float>(i, j, k) - d_f_ver.at<float>(i, j + 1, k));

	for (int i = 0; i != rows - 1; i++)
		for (int j = 0; j != cols; j++)
			for (int k = 0; k != 3; k++)
				d_b_hor.at<float>(i, j, k) = cv::abs(d_f_hor.at<float>(i, j, k) - d_f_hor.at<float>(i + 1, j, k));

	Mat t_ver = d_f_ver - d_b_ver;
	Mat t_hor = d_f_hor - d_b_hor;

	for (int i = 0; i != rows; i++)
		for (int j = 0; j != cols; j++)
			for (int k = 0; k != 3; k++)
			{
				t_ver.at<float>(i, j, k) = max(0.0f, t_ver.at<float>(i, j, k));
				t_hor.at<float>(i, j, k) = max(0.0f, t_hor.at<float>(i, j, k));
			}


	float s_d_ver = 0.0f, s_d_hor = 0.0f, s_v_ver = 0.0f, s_v_hor = 0.0f;
	for (int i = 1; i != rows - 1; i++)
		for (int j = 1; j != cols - 1; j++)
		{
			s_d_ver += 
		}
}