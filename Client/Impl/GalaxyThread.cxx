#include "GalaxyThread.hxx"

#include <thread>

namespace galaxy
{
	namespace api
	{
		/**
		 * The interface representing a thread object.
		 */

		GalaxyThread::GalaxyThread(std::thread&& thread) :
			_thread(std::move(thread))
		{

		}
		/**
		 * Join the thread.
		 *
		 * Wait until IGalaxyThread execution is finished. Internal callers of this function are blocked until the function returns.
		 */
		void GalaxyThread::Join() {
			_thread.join();
		}

		/**
		 * Checks if the IGalaxyThread is ready to Join().
		 *
		 * @return true if the thread is ready to Join().
		 */
		bool GalaxyThread::Joinable() {
			return _thread.joinable();
		}

		/**
		 * Detach the thread.
		 *
		 * Separate the thread of execution from the IGalaxyThread object, allowing execution to continue independently.
		 */
		void GalaxyThread::Detach() {
			_thread.detach();
		}

		GalaxyThread::~GalaxyThread() {
		};

		/**
		 * Custom thread spawner for the Galaxy SDK.
		 */

		 /**
		  * Spawn new internal Galaxy SDK thread.
		  *
		  * A new thread shall start from the provided ThreadEntryFunction accepting provided ThreadEntryParam.
		  *
		  * @note The very same allocator shall be used for thread objects allocations as specified in the InitOptions::galaxyAllocator.
		  *
		  * @param [in] entryPoint The wrapper for the entry point function.
		  * @param [in] param The parameter for the thread entry point.
		  * @return New thread object.
		  */
		IGalaxyThread* GalaxyThreadFactory::SpawnThread(ThreadEntryFunction const entryPoint, ThreadEntryParam param) {

			// TODO: use GalaxyAllocator
			return new GalaxyThread(std::thread(entryPoint, param));
		}

		GalaxyThreadFactory::~GalaxyThreadFactory() {};

		/** @} */
	}
}


