#pragma once
#include "test_base.h"
#include "image.h"

namespace imageoperations
{
	namespace test
	{
		class ImageSubtractionTester : public TestBase
		{
		public:
			ImageSubtractionTester();
			~ImageSubtractionTester();
			bool TestSubtraction();
			bool RunAll();

		private:
			bool IsBlackImage(const imageoperations::Image& _img);
		};
	}
}