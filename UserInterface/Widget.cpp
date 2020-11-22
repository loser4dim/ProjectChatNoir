#include "Widget.hpp"

#include <string>
#include <stdexcept>

namespace loser_ui{
	Widget::Widget(GLFWwindow* const window, std::shared_ptr<loser_scene::Scene>& new_scene_ref, std::shared_ptr<loser_renderer::GLRenderer>& new_renderer_ref) noexcept(false){
		if(new_scene_ref == nullptr){
			throw(std::runtime_error(std::string(__FILE__) + " | Line " + std::to_string(__LINE__) + "\n\t" + "Fail to Obtain Scene Reference."));
		}
		if(new_renderer_ref == nullptr){
			throw(std::runtime_error(std::string(__FILE__) + " | Line " + std::to_string(__LINE__) + "\n\t" + "Fail to Obtain Renderer Reference."));
		}

		scene_ref_		= new_scene_ref;
		renderer_ref_	= new_renderer_ref;

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

		ImGui::StyleColorsDark();

		if(!ImGui_ImplOpenGL3_Init("#version 460")){
			throw(std::runtime_error(std::string(__FILE__) + " | Line " + std::to_string(__LINE__) + "\n\t" + "Fail to Initialize DearImGui for OpenGL."));
		}
		if(!ImGui_ImplGlfw_InitForOpenGL(window, true)){
			throw(std::runtime_error(std::string(__FILE__) + " | Line " + std::to_string(__LINE__) + "\n\t" + "Fail to Initialize DearImGui for GLFW."));
		}
	}

	Widget::~Widget() noexcept{
		scene_ref_.reset();
		renderer_ref_.reset();

		ImGui_ImplGlfw_Shutdown();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void Widget::createParts(const float width, const float height) const noexcept{
		createFrame();
		createMenu(width, height);
		return;
	}

	void Widget::display() const noexcept{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		return;
	}

	void Widget::createFrame() const noexcept{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		return;
	}

    void Widget::createMenu(const float width, const float height) const noexcept{
        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(width / 4.0f, height / 3.0f), ImGuiCond_Always);

        ImGui::Begin("Main Menu", nullptr, ImGuiWindowFlags_MenuBar);
        if(ImGui::BeginMenuBar()){
            if(ImGui::BeginMenu("File")){
                if(ImGui::MenuItem("Exit")){

                }
                ImGui::EndMenu();
            }

            if(ImGui::BeginMenu("Help")){
                if(ImGui::MenuItem("Copyright")){
                    /*if(ImGui::BeginPopupModal("Copyright"), nullptr, ImGuiWindowFlags_AlwaysAutoResize){
                        ImGui::Text("(C) DSE Lab. in Hokkaido University 2010-2019");
                        ImGui::Separator();
                        if(ImGui::Button("Close")){
                            ImGui::CloseCurrentPopup();
                        }
                        ImGui::EndPopup();
                    }*/
                }
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }


        ImGui::End();

        /*bool show_demo_window = true;
        bool show_another_window = true;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if(show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);
        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if(ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
        // 3. Show another simple window.
        if(show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if(ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }*/



        return;
    }
}

#include <imgui.cpp>
#include <imgui_widgets.cpp>
#include <imgui_draw.cpp>
//#include <imgui_demo.cpp>
#include <backends/imgui_impl_opengl3.cpp>
#include <backends/imgui_impl_glfw.cpp>