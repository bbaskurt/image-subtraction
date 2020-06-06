#include "test.h"
#include <iostream>
#include "test_file_operations.h"
#include "test_image_subtraction.h"

imageoperations::test::Tester::Tester()
{
}

imageoperations::test::Tester::~Tester()
{
}

bool imageoperations::test::Tester::RunAll()
{
	imageoperations::test::FileOperationsTester fTester;
	fTester.RunAll();
	imageoperations::test::ImageSubtractionTester iTester;
	iTester.RunAll();

	return true;
}
