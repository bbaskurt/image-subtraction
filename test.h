#pragma once

#include "image_subtraction.h"

namespace imageoperations
{
	namespace test
	{
		class SubtractionTester
		{
		public:
			SubtractionTester();
			~SubtractionTester();
			bool TestSubtraction();
			bool TestRead();
			bool TestWrite();
			bool TestTotal();
			bool RunAll();

		private:
			void CustomAssert(bool _status, const std::string& _test_name);
		};
	}
}