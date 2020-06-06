#pragma once
#include "test_base.h"

namespace imageoperations
{
	namespace test
	{
		class FileOperationsTester : public TestBase
		{
		public:
			FileOperationsTester();
			~FileOperationsTester();
			bool TestRemoveFile();
			bool TestCheckFile();
			bool TestRead();
			bool TestWrite();
			bool RunAll();

		private:
			
		};
	}
}