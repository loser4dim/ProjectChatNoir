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
		//Hatsune Miku Color
		static constexpr const GLclampf DEFAULT_BACKGROUND_RED_		= 57.0f / 255.0f;
		static constexpr const GLclampf DEFAULT_BACKGROUND_GREEN_	= 197.0f / 255.0f;
		static constexpr const GLclampf DEFAULT_BACKGROUND_BLUE_	= 187.0f / 255.0f;
		static constexpr const GLclampf DEFAULT_BACKGROUND_ALPHA_	= 1.0f;

		std::array<GLclampf, 4> background_color_;

		GLint projection_matrix_location_ = 0;
		GLint view_matrix_location_ = 0;



	public:
		GLRenderer() noexcept(false);
		explicit GLRenderer(const GLclampf r, const GLclampf g, const GLclampf b, const GLclampf a) noexcept(false);

		GLRenderer(const GLRenderer&)	= delete;
		GLRenderer(GLRenderer&&)		= delete;

		GLRenderer& operator=(const GLRenderer&)	= delete;
		GLRenderer& operator=(GLRenderer&&)			= delete;

		~GLRenderer() = default;

		std::unique_ptr<GLShader> axes_shader_ = nullptr;

	public:
		void clear() const noexcept;

		
		void drawAxes(const loser_scene::Scene& scene_ref) noexcept;



		void computeViewportMatrix(const GLint width, const GLint height) const noexcept;


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
