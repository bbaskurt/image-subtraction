#include "test_file_operations.h"
#include "file_operations.h"

imageoperations::test::FileOperationsTester::FileOperationsTester()
{
}

imageoperations::test::FileOperationsTester::~FileOperationsTester()
{
}

bool imageoperations::test::FileOperationsTester::TestRemoveFile()
{
	size_t width = 1000;
	size_t height = 1000;
	Image src_img(width, height);
	imageoperations::FileOperations fileOperator;
	std::string result_file = "test_remove.raw";
	fileOperator.WriteImage(src_img, result_file);
	if (!imageoperations::FileOperations::RemoveFile(result_file))
		return false;
	if (imageoperations::FileOperations::CheckFile(result_file))
		return false;

	return true;
}

bool imageoperations::test::FileOperationsTester::TestCheckFile()
{
	std::string file_name = "sino800_540x1200.raw";
	std::string file_name2 = "test.png";

	if (!imageoperations::FileOperations::CheckFile(file_name2))
		return false;

	if (!imageoperations::FileOperations::CheckFile(file_name))
		return false;

	return true;
}

bool imageoperations::test::FileOperationsTester::TestRead()
{
	std::string file_name = "sino800_540x1200.raw";
	size_t width = 540;
	size_t height = 1200;
	Image src_img(width, height);
	imageoperations::FileOperations fileOperator;
	if (!fileOperator.ReadImage(file_name, width, height, src_img))
		return false;
	return true;
}

bool imageoperations::test::FileOperationsTester::TestWrite()
{
	std::string file_name = "sino800_540x1200.raw";
	imageoperations::FileOperations fileOperator;
	size_t width = 540;
	size_t height = 1200;
	Image src_img(width, height);
	fileOperator.ReadImage(file_name, width, height, src_img);
	
	std::string output_file = "test_write.raw";
	if (!fileOperator.WriteImage(src_img, output_file))
		return false;

	if (!imageoperations::FileOperations::CheckFile(output_file))
		return false;

	imageoperations::FileOperations::RemoveFile(output_file);

	return true;
}

bool imageoperations::test::FileOperationsTester::RunAll()
{
	CustomAssert(TestCheckFile(), "Check file test");
	CustomAssert(TestRead(), "Image read test");
	CustomAssert(TestWrite(), "Image write test");
	CustomAssert(TestRemoveFile(), "Remove file test");

	return true;
}
