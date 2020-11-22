#pragma once

#include "GLShader.hpp"
#include "Scene.hpp"
#include <array>

#include <memory>

namespace loser_renderer{
	enum Color: std::size_t{
		RED_	= 0,
		GREEN_	= 1,
		BLUE_	= 2,
		ALPHA_	= 3
	};

	class GLRenderer final{
	private:
		static constexpr const char* const AXES_VERTEX_SHADER_PATH_ = "./Shader/Axes.vert";
		static constexpr const char* const AXES_FRAGMENT_SHADER_PATH_ = "./Shader/Axes.frag";

		static constexpr const char* const MODEL_VERTEX_SHADER_PATH_ = "./Shader/Model.vert";
		static constexpr const char* const MODEL_FRAGMENT_SHADER_PATH_ = "./Shader/Model.frag";

		//Hatsune Miku Color
		static constexpr const GLclampf DEFAULT_BACKGROUND_RED_		= 57.0f / 255.0f;
		static constexpr const GLclampf DEFAULT_BACKGROUND_GREEN_	= 197.0f / 255.0f;
		static constexpr const GLclampf DEFAULT_BACKGROUND_BLUE_	= 187.0f / 255.0f;
		static constexpr const GLclampf DEFAULT_BACKGROUND_ALPHA_	= 1.0f;

		std::array<GLclampf, 4> background_color_;

		GLint axes_projection_matrix_location_ = -1;
		GLint axes_view_matrix_location_ = -1;

		GLint model_projection_matrix_location_ = -1;
		GLint model_view_matrix_location_ = -1;

		std::unique_ptr<GLShader> axes_shader_ = nullptr;

		std::unique_ptr<GLShader> model_shader_ = nullptr;

	public:
		GLRenderer() noexcept(false);
		explicit GLRenderer(const GLclampf red, const GLclampf green, const GLclampf blue, const GLclampf alpha) noexcept(false);

		GLRenderer(const GLRenderer&)	= delete;
		GLRenderer(GLRenderer&&)		= delete;

		GLRenderer& operator=(const GLRenderer&)	= delete;
		GLRenderer& operator=(GLRenderer&&)			= delete;

		~GLRenderer() noexcept;


	public:
		void clear() const noexcept;
		void computeViewportMatrix(const GLint width, const GLint height) const noexcept;
		
		void drawAxes(const loser_scene::Scene& scene_ref) noexcept;


		void drawTriangle(const loser_scene::Scene& scene_ref) noexcept;
		


	private:

#ifdef _DEBUG
		static void reportDebugInfo() noexcept;
#endif
		static void setupSmoothHint() noexcept;
		static void setupTextureFlag() noexcept;
		static void setupVertexPostProcessingFlag() noexcept;
		static void setupRasterizationFlag() noexcept;
		static void setupPerFragmentOperationFlag() noexcept;
		static void setupDebugOutputFlag() noexcept;
	};
}
