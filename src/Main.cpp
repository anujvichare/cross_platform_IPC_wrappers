
#include "SharedMemory.h"

using namespace IPCWrappers;

int main(int argc, char* argv[])
{

    const std::string name = "SharedMemory";
	
    if(argc == 1)
    	std::cout << "I will create Shared memory" << std::endl;

    else
	std::cout << "Memory is already being created" << std::endl;
    
    SharedMemory sharedMemory(name);

    if (argc == 1)
    {	
	    	if(sharedMemory.Create())
        		std::cout << "Created Memory"<< std::endl;
       		else	
			std::cout << "Failed to create"<< std::endl;	
    	
		std::string inputString;
		std::cin >> inputString;

		sharedMemory.Write(inputString.c_str(), inputString.size());
		
    }	
    else
    {

	    	if(sharedMemory.Open())
        		std::cout << "Opened Memory"<< std::endl;
       		else	
			std::cout << "Failed to open"<< std::endl;	

    		char buffer[200];
    		int ret = sharedMemory.Read(buffer, 200);
    		std::cout << "Message read from shared memory: " << buffer << std::endl;
    }

    std::string a;
    std::cin>>a;
    return 0;
}

