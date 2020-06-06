#pragma once
#include <string>

namespace imageoperations
{
	namespace test
	{
		class TestBase
		{
		public:
			TestBase();
			~TestBase();
			virtual bool RunAll() = 0;

		protected:
			void CustomAssert(bool _status, const std::string& _test_name);
		};
	}
}