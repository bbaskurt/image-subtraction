#include "image_subtraction.h"
#include <thread>

std::mutex imageoperations::ImageSubtraction::m_result_mutex;

imageoperations::ImageSubtraction::ImageSubtraction() :
	m_width(0),
	m_height(0),
	m_size_initialized(false),
	m_cycle(0),
	m_thread_wait_time(1),
	m_working_counter(0),
	m_completed_counter(0)
{
	// do not create threads more than the number of cores.
	m_thread_count = std::thread::hardware_concurrency() - 1;
	m_new_image_received.exchange(false);
	m_thread_status.exchange(true);

	// create workers
	for (int i = 0; i < m_thread_count; i++)
	{
		m_workers.push_back(std::make_shared<std::thread>(&ImageSubtraction::SubtractRoi, this, i));
	}
}

imageoperations::ImageSubtraction::~ImageSubtraction()
{
	m_thread_status.exchange(false);
	// wait untill all threads to be killed
	std::this_thread::sleep_for(std::chrono::milliseconds(m_thread_wait_time * 2));

	for (auto worker : m_workers)
	{
		if (worker)
			worker->detach();
	}
}

bool imageoperations::ImageSubtraction::SubtractPixelwise(const Image & _img1, const Image & _img2, Image & _result_image)
{

	if (_img1.GetSizeByte() != _img2.GetSizeByte())
	{
		std::cout << "Images must have same size!" << std::endl;
		return false;
	}

	// Initialize result image.
	if (_result_image.GetSizeByte() != _img1.GetSizeByte())
		_result_image = Image(_img1.GetWidth(), _img1.GetHeight());

	uint16_t* ptr1 = _img1.GetData();
	uint16_t* ptr2 = _img2.GetData();
	uint16_t* result_ptr = _result_image.GetData();

	int total_pixels = _img1.GetWidth()*_img2.GetHeight();
	for (int i = 0; i < total_pixels; i++)
	{
		uint16_t px1 = ptr1[i];
		uint16_t px2 = ptr2[i];

		if (ptr1[i] < ptr2[i])
			result_ptr[i] = 0;
		else
			result_ptr[i] = ptr1[i] - ptr2[i];
	}
	return false;
}

bool imageoperations::ImageSubtraction::SubtractAysnc(const Image& _img1, const Image& _img2, Image* _result_image)
{
	if (m_workers.empty())
		return false;

	if (!m_size_initialized && _img1.GetData() != nullptr)
	{
		m_width = _img1.GetWidth();
		m_height = _img1.GetHeight();
		m_size_initialized = true;
	}

	//auto start_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	m_source1 = _img1;
	m_source2 = _img2;
	m_result = _result_image;
	//auto end_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	//std::cout << "Image copy time: " << end_time - start_time << std::endl;

	m_cycle++;
	m_new_image_received.exchange(true);

	// wait until all workers done
	while (m_completed_counter != m_thread_count)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		// disable new source trigger once all threads received it. 
		if (m_working_counter == m_thread_count)
			m_new_image_received.exchange(false);
	}
	m_working_counter = 0;
	m_completed_counter = 0;

	return true;
}

void imageoperations::ImageSubtraction::SubtractRoi(const int & _index)
{
	// prevent to process same roi twice.
	uint32_t local_cycle = m_cycle;

	while (m_thread_status)
	{
		if (m_new_image_received && m_cycle != local_cycle)
		{
			local_cycle = m_cycle;
			m_working_counter++;
			uint16_t *src1_ptr = m_source1.GetData();
			uint16_t *src2_ptr = m_source2.GetData();
			uint16_t *result_ptr = m_result->GetData();
			if (result_ptr == nullptr)
			{
				m_result = new Image(m_width, m_height);
			}
			if (src1_ptr != nullptr && src2_ptr != nullptr)
			{
				// calculate total pixel count that will be processed by the thread
				int pix_count = m_width*m_height / m_thread_count;
				int offset = pix_count * _index;
				// expand roi for last worker to cover remaining pixels at the end of image. 
				if (_index == m_thread_count - 1)
				{
					pix_count = (m_width * m_height) - offset;
				}
				for (int i = 0; i < pix_count; i++)
				{
					// no need to use mutex as multiple threads do not write to the same address at the same time.
					int current_ind = offset + i;
					if (src1_ptr[current_ind] < src2_ptr[current_ind])
						result_ptr[current_ind] = 0;
					else
						result_ptr[current_ind] = src1_ptr[current_ind] - src2_ptr[current_ind];
				}
			}
			m_completed_counter++;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(m_thread_wait_time));
	}
}

bool imageoperations::ImageSubtraction::SubtractBitwise(const Image& _img1, const Image& _img2, Image& _result_image)
{
	// TODO: Implement
	return true;
}

