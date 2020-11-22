#include "GLRenderer.hpp"

#include <string>
#include <stdexcept>
#ifdef _DEBUG
#include <iostream>
#endif

namespace loser_renderer{
	GLRenderer::GLRenderer() noexcept(false): GLRenderer(GLRenderer::DEFAULT_BACKGROUND_RED_, GLRenderer::DEFAULT_BACKGROUND_GREEN_, GLRenderer::DEFAULT_BACKGROUND_BLUE_, GLRenderer::DEFAULT_BACKGROUND_ALPHA_){
	}
	GLRenderer::GLRenderer(const GLclampf r, const GLclampf g, const GLclampf b, const GLclampf a) noexcept(false): background_color_{r, g, b, a}{
		glewExperimental = GL_TRUE;

		GLenum error = glewInit();
		if(error != GLEW_OK){
			std::string message(reinterpret_cast<const char*>(glewGetErrorString(error)));
			throw(std::runtime_error(std::string(__FILE__) + " | Line " + std::to_string(__LINE__) + "\n\t" + message));
		}
#ifdef _DEBUG
		std::clog << "GLEW Version: " << glewGetString(GLEW_VERSION) << std::endl;
		if(GLEW_VERSION_4_6 != GL_TRUE){
			throw(std::runtime_error(std::string(__FILE__) + " | Line " + std::to_string(__LINE__) + "\n\t" + "Sorry, This Computer Environment does NOT Support OpenGL 4.6."));
		}
		reportDebugInfo();
#endif
		setupSmoothHint();
		setupTextureFlag();
		setupVertexPostProcessingFlag();
		setupRasterizationFlag();
		setupPerFragmentOperationFlag();
		setupDebugOutputFlag();

		axes_shader_ = std::make_unique<GLShader>("./Shader/Axes.vert", "./Shader/Axes.frag");

		projection_matrix_location_ = glGetUniformLocation(axes_shader_->getProgram(), "projection_matrix");
		view_matrix_location_ = glGetUniformLocation(axes_shader_->getProgram(), "view_matrix");
	}

	void GLRenderer::clear() const noexcept{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(background_color_[Color::RED_], background_color_[Color::GREEN_], background_color_[Color::BLUE_], background_color_[Color::ALPHA_]);
		return;
	}


	void GLRenderer::drawAxes(const loser_scene::Scene& scene_ref) noexcept{
		constexpr const std::array<GLdouble, 16> p{
				3.73205, 0.0, 0.0, 0.0,
				0.0, 3.73205, 0.0, 0.0,
				0.0, 0.0, 1.0002, -1.0,
				0.0, 0.0, -0.20002, 0.0
		};

		constexpr const std::array<GLdouble, 16> v{
				-0.866025, -0.43013, 0.25, 0.0,
				0.5, -0.75, 0.433013, 0.0,
				0.0, 0.5, 0.866025, 0.0, 
				0.0, 0.0, -10.0, 1.0
		};

		std::clog << projection_matrix_location_ << std::endl;
		std::clog << view_matrix_location_ << std::endl;

		glUseProgram(axes_shader_->getProgram());
		glUniformMatrix4dv(projection_matrix_location_, 1, GL_FALSE, p.data());
		glUniformMatrix4dv(view_matrix_location_, 1, GL_FALSE, v.data());

		GLuint vertex_array_buffer_obj = 0;
		glGenVertexArrays(1, &vertex_array_buffer_obj);
		glBindVertexArray(vertex_array_buffer_obj);

		constexpr const std::array<GLdouble, 18> data{
				0.0, 0.0, 0.0,
				150, 0.0, 0.0,
				0.0, 0.0, 0.0,
				0.0, 150, 0.0,
				0.0, 0.0, 0.0,
				0.0, 0.0, 150
		};

		GLuint vertex_buffer_obj = 0;
		glGenBuffers(1, &vertex_buffer_obj);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_obj);
		glBufferData(GL_ARRAY_BUFFER, 18, data.data(), GL_STATIC_READ);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_obj);
		glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 0, nullptr);

		
		glDrawArrays(GL_LINES, 0, 6);

		glDisableVertexAttribArray(0);
		glDeleteBuffers(1, &vertex_buffer_obj);


		return;
	}






	void GLRenderer::computeViewportMatrix(const GLint width, const GLint height) const noexcept{
		glViewport(0, 0, width, height);
		return;
	}

	

#ifdef _DEBUG
	void GLRenderer::reportDebugInfo() noexcept{
		std::clog << "GPU Info                :"												<< std::endl;
		std::clog << "\t" << "Renderer        : "	<< glGetString(GL_RENDERER)					<< std::endl;
		std::clog << "\t" << "Vendor          : "	<< glGetString(GL_VENDOR)					<< std::endl;
		std::clog << "\t" << "OpenGL Version  : "	<< glGetString(GL_VERSION)					<< std::endl;
		std::clog << "\t" << "Shading Language: "	<< glGetString(GL_SHADING_LANGUAGE_VERSION)	<< std::endl;

		GLint extension_num = 0;
		glGetIntegerv(GL_NUM_EXTENSIONS, &extension_num);
		std::clog << "Extensions              :"	<< std::endl;
		for(GLuint i = 0; i < static_cast<GLuint>(extension_num); ++i){
			std::clog << "\t" << reinterpret_cast<const char*>(glGetStringi(GL_EXTENSIONS, i))					<< std::endl;
		}

		GLint shader_language_version_num = 0;
		glGetIntegerv(GL_NUM_SHADING_LANGUAGE_VERSIONS, &shader_language_version_num);
		std::clog << "Shader Language Versions:"	<< std::endl;
		for(GLuint i = 0; i < static_cast<GLuint>(shader_language_version_num); ++i){
			std::clog << "\t" << reinterpret_cast<const char*>(glGetStringi(GL_SHADING_LANGUAGE_VERSION, i))	<< std::endl;
		}

		GLint spir_v_extensions_num = 0;
		glGetIntegerv(GL_NUM_SPIR_V_EXTENSIONS, &spir_v_extensions_num);
		std::clog << "Spir-V Extensions       :"	<< std::endl;
		for(GLuint i = 0; i < static_cast<GLuint>(spir_v_extensions_num); ++i){
			std::clog << "\t" << reinterpret_cast<const char*>(glGetStringi(GL_SPIR_V_EXTENSIONS, i))			<< std::endl;
		}

		return;
	}
#endif

	void GLRenderer::setupSmoothHint() noexcept{
		glHint(GL_LINE_SMOOTH_HINT,					GL_NICEST);
		glHint(GL_POLYGON_SMOOTH_HINT,				GL_NICEST);
		glHint(GL_TEXTURE_COMPRESSION_HINT,			GL_NICEST);
		glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT,	GL_NICEST);
		return;
	}

	void GLRenderer::setupTextureFlag() noexcept{
		//glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
		return;
	}

	void GLRenderer::setupVertexPostProcessingFlag() noexcept{
		//glEnable(GL_DEPTH_CLAMP);
		return;
	}

	void GLRenderer::setupRasterizationFlag() noexcept{
		glDisable(GL_RASTERIZER_DISCARD);

		//glEnable(GL_MULTISAMPLE);
		//glEnable(GL_SAMPLE_SHADING);

		//(GL_PROGRAM_POINT_SIZE);

		//glEnable(GL_LINE_SMOOTH);
		//glLineWidth(1.0f);

		//glEnable(GL_POLYGON_SMOOTH);
		//glEnable(GL_CULL_FACE);

		//glFrontFace(GL_CCW);
		//glCullFace(GL_BACK);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//glEnable(GL_POLYGON_OFFSET_POINT);
		//glEnable(GL_POLYGON_OFFSET_LINE);
		//glEnable(GL_POLYGON_OFFSET_FILL);

		return;
	}

	void GLRenderer::setupPerFragmentOperationFlag() noexcept{
		glDisable(GL_SCISSOR_TEST);

		//glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
		//glEnable(GL_SAMPLE_ALPHA_TO_ONE);
		//glEnable(GL_SAMPLE_COVERAGE);
		//glEnable(GL_SAMPLE_MASK);

		//glEnable(GL_DEPTH_TEST);
		//glDepthFunc(GL_LESS);

		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glDisable(GL_DITHER);

		glDisable(GL_COLOR_LOGIC_OP);

		return;
	}

	void GLRenderer::setupDebugOutputFlag() noexcept{
#ifdef _DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#else
		glDisable(GL_DEBUG_OUTPUT);
		glDisable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#endif
		return;
	}
}