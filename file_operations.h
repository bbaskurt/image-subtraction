#pragma once
#include "image.h"

namespace imageoperations {

	class FileOperations
	{
	public:

		FileOperations();
		~FileOperations();

		/*
		* Load image from given file path. Returns false if any error occurs while loading image.
		* Image width and height are required as image file does not have header information.
		*
		* @param file_name path of source image file name
		* @param width image width (pixels)
		* @param height image height (pixels)
		* @param img loaded image
		* @return status true if the image is loaded successfully, false if any error occured
		*/
		bool ReadImage(const std::string& _file_name, const size_t& _width, const size_t& _height, imageoperations::Image& _img);

		/*
		* Write image to given file path. Returns false if any error occurs while writing image.
		*
		* @param img source image
		* @param file_name image file name to be written (with its path)
		* @return status true if the image is written successfully, false if any error occured
		*/
		bool WriteImage(imageoperations::Image& _img, const std::string& _file_name);

		/*
		* Check if given file exists and can be opened.
		*
		* @param file_name image file name to be written (with its path)
		* @return status true if the the file is valid, false if any error occured
		*/
		static bool CheckFile(const std::string& _file_name);

		/*
		* Remove given file from file system.
		*
		* @param file_name image file name to be written (with its path)
		* @return status true if the the file is removed successfully, false if any error occured
		*/
		static bool RemoveFile(const std::string& _file_name);

	private:

	};
}