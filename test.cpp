#include "test.h"
#include <iostream>

imageoperations::test::SubtractionTester::SubtractionTester()
{
}

imageoperations::test::SubtractionTester::~SubtractionTester()
{
}

bool imageoperations::test::SubtractionTester::TestSubtraction()
{
	return false;
}

bool imageoperations::test::SubtractionTester::TestRead()
{
	return false;
}

bool imageoperations::test::SubtractionTester::TestWrite()
{
	return false;
}

bool imageoperations::test::SubtractionTester::TestTotal()
{
	return false;
}


void imageoperations::test::SubtractionTester::CustomAssert(bool _status, const std::string & _test_name)
{
	if (_status)
	{
		std::cout << _test_name << " passed" << std::endl;
	}
	else
	{
		std::cout << "----> " << _test_name << " failed!" << std::endl;
	}
}

bool imageoperations::test::SubtractionTester::RunAll()
{
	CustomAssert(TestSubtraction(), "Image subtraction test");
	CustomAssert(TestRead(), "Image read test");
	CustomAssert(TestWrite(), "Image write test");

	return false;
}
