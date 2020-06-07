#include "test_image_subtraction.h"
#include "image_subtraction.h"
#include "file_operations.h"


imageoperations::test::ImageSubtractionTester::ImageSubtractionTester()
{
}

imageoperations::test::ImageSubtractionTester::~ImageSubtractionTester()
{
}

bool imageoperations::test::ImageSubtractionTester::TestSubtraction()
{
	std::string file_name = "sino800_540x1200.raw";
	size_t width = 540;
	size_t height = 1200;
	Image src_img(width, height);
	imageoperations::FileOperations fileOperator;
	fileOperator.ReadImage(file_name, width, height, src_img);
	imageoperations::ImageSubtraction imgSubtractor;
	Image result_img(width, height);
	imgSubtractor.SubtractAysnc(src_img, src_img, &result_img);
	if (!IsBlackImage(result_img))
		return false;
	return true;
}

bool imageoperations::test::ImageSubtractionTester::RunAll()
{
	CustomAssert(TestSubtraction(), "Image subtraction test");

	return true;
}

bool imageoperations::test::ImageSubtractionTester::IsBlackImage(const imageoperations::Image & _img)
{
	uint16_t *ptr = _img.GetData();
	size_t width = _img.GetWidth();
	size_t height = _img.GetHeight();
	size_t total_pixels = width*height;
	for (int i = 0; i < total_pixels; i++)
	{
		if ((ptr[i]) != 0)
			return false;
	}
	return true;
}
