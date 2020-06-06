#include "test_base.h"
#include <iostream>

imageoperations::test::TestBase::TestBase()
{
}

imageoperations::test::TestBase::~TestBase()
{
}

void imageoperations::test::TestBase::CustomAssert(bool _status, const std::string & _test_name)
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
