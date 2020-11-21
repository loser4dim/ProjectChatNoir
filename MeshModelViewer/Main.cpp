









#include <exception>
#include <iostream>

#ifdef _DEBUG
#include <string>
#include <vector>
int main(int argc, char** argv){
	const std::vector<std::string> args(argv, argv + argc);
	for(const auto& message : args){
		std::clog << message << std::endl;
	}
	std::clog << "Compiled on " << __DATE__ << " at " __TIME__ << std::endl;
#else
int main(){
#endif
	try{



	}
	catch(const std::exception& error){
		std::cerr << "Exception! : " << error.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}