#include "file_operations.h"
#include <fstream>

imageoperations::FileOperations::FileOperations()
{
}

imageoperations::FileOperations::~FileOperations()
{
}

bool imageoperations::FileOperations::ReadImage(const std::string& _file_name, const size_t& _width, const size_t& _height, imageoperations::Image& _img)
{
	try
	{
		// Re-init image object if its dimension is not coherent
		if (_img.GetWidth() != _width || _img.GetHeight() != _height)
		{
			_img = Image(_width, _height);
		}

		std::ifstream file(_file_name, std::ios::in | std::ios::binary);
		if (file.is_open())
		{
			file.read((char*)&_img.GetData()[0], _img.GetSizeByte());
			if (!file)
			{
				std::cout << "Error while reading file" << std::endl;
				return false;
			}
			file.close();
		}
		else
		{
			std::cout << "Given file cannot be opened!" << std::endl;
			return false;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}
	return true;
}

bool imageoperations::FileOperations::WriteImage(imageoperations::Image& _img, const std::string& _file_name)
{
	try
	{
		uint16_t* data = _img.GetData();
		std::ofstream file("file.raw", std::ios::out | std::ios::binary);
		file.write((char*)data, _img.GetSizeByte());
		file.close();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}

	return true;
}
