#include <iostream>
#include "image_subtraction.h"
#include "file_operations.h"
#include <fstream>
#include "test.h"

/*
* TODO:
*      - Use log file instead of console output for error message 
*      - Use Google or Boost test instead of manual testing. (They are not used to prevent 3rd party dependency)
*      - Bitwise subtraction can be used for improvement of run-time performance 
*/

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

	// Subtract images
	imageoperations::ImageSubtraction imageSubtractor;

	auto start_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	// worth it to use for big images
	imageSubtractor.SubtractAysnc(src_img1, src_img2, &diff_img);
	//imageSubtractor.Subtract(src_img1, src_img2, diff_img);
	auto end_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::cout << "Process time: " << end_time - start_time << " ms" << std::endl;

	// Write result image
	fileOperator.WriteImage(diff_img, result_name);

	// Run tests
	imageoperations::test::Tester test_all;
	test_all.RunAll();

	std::system("pause");
	return 0;
}