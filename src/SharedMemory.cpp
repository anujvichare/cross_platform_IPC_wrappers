#include "SharedMemory.h"
#include <iostream>

namespace IPCWrappers
{

	SharedMemory::SharedMemory(const std::string& name, const size_t size) 
		: m_size(size), m_name(name) 
	{
	}

	SharedMemory::~SharedMemory() 
	{
        	Close();
    	}
	
	bool SharedMemory::Create()
	{
		return OpenOrCreate(true);
	}	
	
	bool SharedMemory::Open()
	{
		return OpenOrCreate(false);
	}

	bool SharedMemory::OpenOrCreate(const bool create) 
	{
#ifdef _WIN32
		if(create)
		{
			m_shmId = CreateFileMappingA 
			(
                		INVALID_HANDLE_VALUE,    // use paging file
                		NULL,                    // default security
                		PAGE_READWRITE,          // read/write access
                		0,                       // maximum object size (high-order DWORD)
                		size,                    // maximum object size (low-order DWORD)
                		m_name.c_str()    	 // name of mapping object
			);                       
			
			if (0 == m_shmId) 
			{
                		std::cerr << "Failed to create shared memory\n";
                		return false;
	    		}
            	}
		else
		{
        		m_shmId = OpenFileMappingA
			( 
			 	FILE_MAP_ALL_ACCESS, 	// read/write access
				FALSE, 			// do not inherit the name
				m_name.c_str()		// name of mapping object
			);
		
			if (0 == m_shmId) 
			{
                		std::cerr << "Failed to open shared memory\n";
                		return false;
            		}
		}
        	
		m_shmPtr = MapViewOfFile
			( 
			 	m_shmId, 		// handle to map object
			 	FILE_MAP_ALL_ACCESS, 	// read/write permission
			 	0, 
			 	0, 
			 	m_size
			 );
		if (nullptr == m_shmPtr) 
		{
            		std::cerr << "Failed to map shared memory\n";
            		return false;
        	}
#else

		int flags = 0666;
        	if (create)
            		flags |= IPC_CREAT;
		
		m_shmId = shmget(ftok(m_name.c_str(), 1), m_size, flags);
		if (-1 == m_shmId) 
		{
			std::cerr << "shmget failed";
			return false;
		}

		m_shmPtr = shmat(m_shmId, nullptr, 0);
		if ((void*)-1 == m_shmPtr) 
		{
			std::cerr << "shmat failed";
			return false;
		}
#endif
        	return true;
    	}

    	void SharedMemory::Close() 
	{
#ifdef _WIN32
        	if (nullptr != m_shmPtr) 
		{
            		UnmapViewOfFile(m_shmPtr);
            		m_shmPtr = nullptr;
        	}
        	if (0 != m_shmId) 
		{
        		CloseHandle(m_shmId);
            		hMapFile = 0;
        	}
#else
        	if (nullptr != m_shmPtr) 
		{
            		shmdt(m_shmPtr);
            		m_shmPtr = nullptr;
        	}
		m_shmId = 0;
#endif
    	}

    	int  SharedMemory::Write(const void* data, size_t dataSize) 
	{
       		if (dataSize > m_size) 
		{
            		std::cerr << "Data size exceeds shared memory size\n";
            		return false;
        	}
        	
		std::memcpy(m_shmPtr, data, dataSize);
        	
		return dataSize;
    	}

    	int SharedMemory::Read(void* buffer, size_t bufferSize) 
	{
        	if (bufferSize > m_size) 
		{
            		std::cerr << "Buffer size is smaller than shared memory size\n";
            		return false;
        	}
        	
		std::memcpy(buffer, m_shmPtr, bufferSize);
        	
		return bufferSize;
    	}

}

