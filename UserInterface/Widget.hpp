#pragma once

#include "Scene.hpp"
#include "GLRenderer.hpp"

#define WINDOWS_IGNORE_PACKING_MISMATCH
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

#include <memory>

namespace loser_ui{
	class Widget final{
	private:
		std::shared_ptr<loser_scene::Scene> scene_ref_ = nullptr;
		std::shared_ptr<loser_renderer::GLRenderer> renderer_ref_ = nullptr;

	public:
		Widget() = delete;
		explicit Widget(GLFWwindow* const window, std::shared_ptr<loser_scene::Scene>& new_scene_ref_, std::shared_ptr<loser_renderer::GLRenderer>& new_renderer_ref) noexcept(false);

		Widget(const Widget&) = delete;
		Widget(Widget&&) = delete;

		Widget& operator=(const Widget&) = delete;
		Widget& operator=(Widget&&) = delete;

		~Widget() noexcept;

	public:
		void createParts(const float width, const float height) const noexcept;
		void display() const noexcept;

	private:
		void createFrame() const noexcept;
		void createMenu(const float width, const float height) const noexcept;
	};
}
