





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
		loser_ui::UserInteraface ui(&scene);

		loser_renderer::GLRenderer renderer(255.0, 255.0, 255.0, 255.0);

		//Create Widget Instance After Creating Renderer Instance
		//Because DearImGui Needs Initialization of GLEW
		ui.addWidget(&renderer);


		while(ui.isEnable()){
			renderer.clear();
			
			//We must Create Widget Every Frame
			ui.createWidget();


			renderer.drawAxes(scene);


			ui.update();
		}
	}
	catch(const std::exception& error){
		std::cerr << "Exception! : " << error.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}