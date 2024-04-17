
#include <iostream>
#include <string>

#ifdef _WIN32
	#include <windows.h>
#else
	#include <sys/types.h>
	#include <sys/ipc.h>
	#include <sys/shm.h>
	#include <cstring>
	#include <cerrno>
#endif

namespace IPCWrappers
{

	class SharedMemory 
	{

		public:
	    		SharedMemory(const std::string& identifier, const size_t size = 1024);
	    		~SharedMemory();
			
			bool Create();
			bool Open();
			void Close();
			int Write(const void* data, size_t dataSize);
			int Read(void* buffer, size_t bufferSize);

		private:
			bool OpenOrCreate(const bool create);
	    		
			int m_shmId;
	    		void* m_shmPtr;
	    		size_t m_size;
	    		std::string m_name;
	};

}
