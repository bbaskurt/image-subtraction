#include <iostream>
#include "image_subtraction.h"
#include "file_operations.h"
#include <fstream>
#include "test.h"

#include <opencv2/highgui/highgui.hpp>

/*
* TODO:
*      - Use log file instead of console output for error message 
*      - Use Google or Boost test instead of manual testing. (They are not used to prevent 3rd party dependency)
*/

void display_image(const imageoperations::Image& _img, const std::string& _win_name)
{
	//uint8_t* newImg = new uint8_t[1200 * 540];
	uint16_t *src_ptr = _img.GetData();
	for (int i = 0; i < 1200 * 540; i++)
	{
		src_ptr[i] = src_ptr[i] * 255;
		//std::cout << new_value << " ";
		//newImg[i] = new_value;
	}
	cv::Mat display_image1(cv::Size(540, 1200), CV_16UC1, &_img.GetData()[0], cv::Mat::AUTO_STEP);
	//cv::Mat display_image1(cv::Size(540, 1200), CV_16U, newImg, cv::Mat::AUTO_STEP);
	cv::imwrite("test_image_16.png", display_image1);
	cv::imshow(_win_name, display_image1);
	cv::waitKey(0);
}

bool validate_parameters(int argc, char** argv, std::string& file_name1, std::string& file_name2, size_t& width, size_t& height, std::string& result_name)
{
	if (argc < 6)
	{
		std::cout << "Invalid parameters" << std::endl;
		std::cout << "Usage: " << argv[0] << " first-image " << " second-image " << " image-width " << " image-height " << " result-image " << std::endl;
		std::cout << "Example: " << argv[0] << " sino800_540x1200.raw sino801_540x1200.raw 540 1200 diff_image.raw" << std::endl;
		return false;
	}
	else
	{
		file_name1 = argv[1];
		if (file_name1.size() <= 0)
		{
			std::cout << "Invalid file path for first image" << std::endl;
			return false;
		}

		if (!imageoperations::FileOperations::CheckFile(file_name1))
		{
			std::cout << "Error on reading input file: " << file_name1 << std::endl;
			return false;
		}

		file_name2 = argv[2];
		if (file_name2.size() <= 0)
		{
			std::cout << "Invalid file path for second image" << std::endl;
			return false;
		}
		if (!imageoperations::FileOperations::CheckFile(file_name2))
		{
			std::cout << "Error on reading input file: " << file_name2 << std::endl;
			return false;
		}

		width = atoi(argv[3]);
		if (width <= 0)
		{
			std::cout << "Invalid image width: " << width << std::endl;
			return false;
		}

		height = atoi(argv[4]);
		if (height <= 0)
		{
			std::cout << "Invalid image height: " << height << std::endl;
			return false;
		}

		result_name = argv[5];
		if (result_name.size() <= 0)
		{
			std::cout << "Invalid file path for result image" << std::endl;
			return false;
		}
	}
	return true;
}

int main(int argc, char** argv) {

	std::string file_name1 = "", file_name2 = "", result_name = "";
	size_t width = 0, height = 0;

	if (!validate_parameters(argc, argv, file_name1, file_name2, width, height, result_name))
		return -1;

	// TODO: resize images, if they have different size.

	// Create image objects
	imageoperations::Image src_img1(width, height);
	imageoperations::Image src_img2(width, height);
	imageoperations::Image diff_img(width, height);

	// Load images
	imageoperations::FileOperations fileOperator;
	fileOperator.ReadImage(file_name1, width, height, src_img1);
	fileOperator.ReadImage(file_name2, width, height, src_img2);

	//uint16_t *ptr = src_img1.GetData();
	//for (int i = 0; i < 540 * 1200; i++)
	//{
	//	uint16_t pix = ptr[i];
	//	if (pix != 1238)
	//		int xxx = 0;
	//	//std::cout << pix << " ";
	//}

	//display_image(src_img1, "source1");
	//display_image(src_img2, "source2");

	// Subtract images
	imageoperations::ImageSubtraction imageSubtractor;

	auto start_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	imageSubtractor.SubtractAysnc(src_img1, src_img2, &diff_img);
	//imageSubtractor.SubtractPixelwise(src_img1, src_img2, diff_img);
	auto end_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::cout << "Process time: " << end_time - start_time << " ms" << std::endl;

	//display_image(diff_img, "difference");

	// Write result image
	fileOperator.WriteImage(diff_img, result_name);

	imageoperations::test::Tester test_all;
	test_all.RunAll();

	std::system("pause");
	return 0;
}