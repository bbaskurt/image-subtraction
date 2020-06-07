#pragma once
#include <atomic>
#include <mutex>
#include <vector>

namespace imageoperations {
	
	// Base class for asynchronous operations
	class AsyncOperation
	{
	public:

		AsyncOperation();
		~AsyncOperation();

	protected:
		// number of threads to be run async.
		int m_thread_count;
		// atomic flag triggered by new source
		std::atomic_bool m_new_source_received;
		// status of the threads, used to safely kill the threads 
		std::atomic_bool m_thread_status;
		// number of threads working on the image
		std::atomic<int> m_working_counter;
		// number of threads completed the process
		std::atomic<int> m_completed_counter;
		// number of process
		std::atomic<uint32_t> m_cycle;
		// worker threads to process roi of source images
		std::vector<std::shared_ptr<std::thread> > m_workers;
		// thread sleep time to check new source (ms)
		int m_thread_wait_time;
	};
}