#ifndef __cplusplus
#ifdef _MSC_VER
#pragma message("Implementation is NOT C++ Standards Compliant!")
#endif
#else
#if __cplusplus >= 201703L
#ifdef _MSC_VER
#pragma message("Implementation is C++17 Compliant!")
#endif
#elif __cplusplus >= 201402L
#ifdef _MSC_VER
#pragma message("Implementation is C++14 Compliant!")
#endif
#elif __cplusplus >= 201103L
#ifdef _MSC_VER
#pragma message("Implementation is C++11 Compliant!")
#endif
#elif __cplusplus >= 199711L
#ifdef _MSC_VER
#pragma message("Implementation is C++03 Compliant!")
#endif
#else
#ifdef _MSC_VER
#pragma message("Implementation is Unknown Compliant!")
#endif
#endif
#endif

#ifndef __STDCPP_STRICT_POINTER_SAFETY__
#ifdef _MSC_VER
#pragma message("Implementation does NOT Have Strict Pointer Safety!")
#endif
#endif

#ifndef __STDCPP_THREADS__
#ifdef _MSC_VER
#pragma message("Program does NOT Run Mulptiplr Threads!")
#endif
#endif

#ifndef __STDC_MB_MIGHT_NEQ_WC__
#ifdef _MSC_VER
#pragma message("Character Literals in the Base Character Set may Have the Same Value in char and wchar_t!")
#endif
#endif 

#ifndef __STDCPP_DEFAULT_NEW_ALIGNMENT__
#ifdef _MSC_VER
#pragma message("NO Default Alignment Value!")
#endif
#endif

#ifdef  __STDC_HOSTED__
#if __STDC_HOSTED__ == 1
#ifdef _MSC_VER
#pragma message("Implementation is Hosted!")
#endif
#elif __STDC_HOSTED__ == 0
#ifdef _MSC_VER
#pragma message("Implementation is Free Standing!")
#endif
#else
#ifdef _MSC_VER
#pragma message("Implementation is Unknown!!")
#endif
#endif
#endif

#ifndef __STDC_ISO_10646__
#ifdef _MSC_VER
#pragma message("wchar_t is NOT Encoded as Unicode!")
#endif
#endif

#ifdef _MSC_VER
#ifdef _CONTROL_FLOW_GUARD
#endif

#ifdef _CPPRTTI
#endif

#ifdef _CPPUNWIND
#endif

#ifdef _MT
#endif

#ifdef _DLL
#endif

#ifdef _M_AMD64
#endif

#ifdef _M_IX86
#endif

#ifdef _M_X64
#endif

#ifdef _M_ARM
#endif

#ifdef _M_ARM64
#endif

#ifdef _M_FP_EXCEPT
#endif

#ifdef _M_FP_FAST
#endif

#ifdef _M_FP_PRECISE
#endif

#ifdef _M_FP_STRICT
#endif

#ifdef __MSVC_RUNTIME_CHECKS
#endif

#ifdef _WCHAR_T_DEFINED
#endif

#ifdef _WIN32
#endif

#ifdef _WIN64
#endif
#endif




#include "UserInterface.hpp"



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
		std::ios::sync_with_stdio(false);

		loser_scene::Scene scene;

		//Create Window Instance Before Creating Renderer Instance
		//Because Initialization of GLEW Needs Window Context
		loser_ui::UserInterface ui(&scene);

		loser_renderer::GLRenderer renderer(255.0f, 255.0f, 255.0f, 255.0f);

		//Create Widget Instance After Creating Renderer Instance
		//Because DearImGui Needs Initialization of GLEW
		ui.addRendererReference(&renderer);
		ui.addWidget();

		scene.computeProjectionMatrix(ui.getWindowWidth(), ui.getWindowHeight());

		while(ui.isEnable()){
			renderer.clear();
			
			//We must Create Widget Every Frame
			ui.createWidget();

			scene.update();

			renderer.drawAxes(scene);
			renderer.drawTriangle(scene);

			ui.update();
		}
	}
	catch(const std::exception& error){
		std::cerr << "Exception! : " << error.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}