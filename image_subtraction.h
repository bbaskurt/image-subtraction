#pragma once
#include "image.h"
#include <atomic>
#include <mutex>

namespace imageoperations {

	class ImageSubtraction
	{
	public:

		ImageSubtraction();
		~ImageSubtraction();

		/*
		* Subtract (bitwise) the second image from the first one and write the difference image with the given file name.
		*
		* @param img1 source image
		* @param img2 source image
		* @param result_image difference image
		* @return status true if subtracted successfully, false if any error occured
		*/
		bool SubtractBitwise(const Image& _img1, const Image& _img2, Image& _result_image);	

		/*
		* Subtract (pixelwise) the second image from the first one and write the difference image with the given file name.
		*
		* @param img1 source image
		* @param img2 source image
		* @param result_image difference image
		* @return status true if subtracted successfully, false if any error occured
		*/
		bool SubtractPixelwise(const Image& _img1, const Image& _img2, Image& _result_image);

		/*
		* Asynchronous subtraction. Sources are divided into rois to be processed in parallel.
		* Each thread processes own roi and notifies this function once it's done. Function releases 
		* the main thread once all threads complete the operation.
		*
		* @param img1 source image
		* @param img2 source image
		* @param result_image difference image
		* @return status true if subtracted successfully, false if any error occured
		*/
		bool SubtractAysnc(const Image& _img1, const Image& _img2, Image* _result_image);

	private:

		/*
		* Apply image subtraction to the given roi. Used in async operation.
		*
		* @param index index of the thread to calculate corresponding roi on image.
		*/
		void SubtractRoi(const int& _index);

	private:
		// number of threads to be run async.
		int m_thread_count;
		// atomic flag triggered by new source
		std::atomic_bool m_new_image_received;
		// status of the threads, used to safely kill the threads 
		std::atomic_bool m_thread_status;
		// number of threads working on the image
		std::atomic<int> m_working_counter;
		// number of threads completed the process
		std::atomic<int> m_completed_counter;
		// worker threads to process roi of source images
		std::vector<std::shared_ptr<std::thread> > m_workers;
		// source image
		Image m_source1;
		// source image
		Image m_source2;
		// difference image
		Image* m_result;
		// image width & height
		size_t m_width;
		size_t m_height;
		bool m_size_initialized;
		// mutex to control write operation of the result image
		static std::mutex m_result_mutex;
		// thread sleep time to check new source (ms)
		int m_thread_wait_time;
		
	};
}