#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <iostream>

namespace imageoperations
{
	class Image
	{
	public:
		Image();
		Image(const int& _width, const int& _height);
		~Image();
		Image(Image const& _img);
		Image &operator=(const Image& _img);

		/*
		* Get value of a specific pixel
		*
		* @param col column of the pixel (starting from 0)
		* @param row row of the pixel (starting from 0)
		* @return pixel value
		*/
		uint16_t GetPixel(const size_t& _col, const size_t& _row) const;

		/*
		* Set value of a specific pixel
		*
		* @param col column of the pixel (starting from 0)
		* @param row row of the pixel (starting from 0)
		* @param value value of the pixel (0-65535)
		*/
		void SetPixel(const size_t& _col, const size_t& _row, const uint16_t& _value = 0);
		
		/*
		* Get image height
		*/
		size_t GetHeight() const;

		/*
		* Get image width
		*/
		size_t GetWidth() const;

		/*
		* Get total image size in bytes
		*/
		size_t GetSizeByte() const;

		/*
		* Get image data pointer
		*/
		uint16_t* GetData() const;

	private:

		uint16_t *m_data;
		size_t m_width;
		size_t m_height;
		size_t m_size_byte;
		
	};
}