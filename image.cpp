#include "image.h"

imageoperations::Image::Image()
{
	m_data = nullptr;
	m_width = 0;
	m_height = 0;
	m_size_byte = 0;
}

imageoperations::Image::Image(const int & _width, const int & _height)
{
	if (_width <= 0 || _height <= 0)
	{
		std::cout << "Invalid image size. Empty image created!" << std::endl;
		m_data = nullptr;
		m_width = 0;
		m_height = 0;
		m_size_byte = 0;
	}
	else
	{
		m_data = new uint16_t[_width*_height];
		m_width = _width;
		m_height = _height;
		m_size_byte = sizeof(uint16_t)*m_height*m_width;
	}
}

imageoperations::Image::~Image()
{
	if (m_data != nullptr) {
		delete[] m_data;
	}
	m_width = 0;
	m_height = 0;
	m_size_byte = 0;
}

imageoperations::Image::Image(Image const & _img)
{
	// TODO: check image size
	m_data = new uint16_t[m_height*m_width];
	//m_size_byte = sizeof(uint16_t)*m_height*m_width;
	std::memcpy(m_data, _img.m_data, m_size_byte);
}

imageoperations::Image & imageoperations::Image::operator=(const Image & _img)
{
	if (m_data != nullptr)
		delete[] m_data;
	m_data = new uint16_t[_img.m_height*_img.m_width];
	m_width = _img.m_width;
	m_height = _img.m_height;
	m_size_byte = sizeof(uint16_t)*m_height*m_width;
	std::memcpy(m_data, _img.m_data, m_size_byte);
	return *this;
}


uint16_t imageoperations::Image::GetPixel(const size_t & _col, const size_t & _row) const
{
	if (_col < m_width && _row < m_height)
	{
		return m_data[_row * m_width + _col];
	}
	else
	{
		std::cout << "Invalid coordinates!" << std::endl;
	}
	return 0;
}

void imageoperations::Image::SetPixel(const size_t & _col, const size_t & _row, const uint16_t & _value)
{
	if (_col < m_width && _row < m_height)
	{
		m_data[_row * m_width + _col] = _value;
	}
	else
	{
		std::cout << "Invalid coordinates!" << std::endl;
	}
}

size_t imageoperations::Image::GetHeight() const
{
	return m_height;
}

size_t imageoperations::Image::GetWidth() const
{
	return m_width;
}

size_t imageoperations::Image::GetSizeByte() const
{
	return m_size_byte;
}

uint16_t * imageoperations::Image::GetData() const
{
	return m_data;
}

