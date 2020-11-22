#include "GLRenderer.hpp"

#include <string>
#include <stdexcept>
#ifdef _DEBUG
#include <iostream>
#endif

namespace loser_renderer{
	GLRenderer::GLRenderer() noexcept(false): GLRenderer(GLRenderer::DEFAULT_BACKGROUND_RED_, GLRenderer::DEFAULT_BACKGROUND_GREEN_, GLRenderer::DEFAULT_BACKGROUND_BLUE_, GLRenderer::DEFAULT_BACKGROUND_ALPHA_){
	}
	GLRenderer::GLRenderer(const GLclampf red, const GLclampf green, const GLclampf blue, const GLclampf alpha) noexcept(false): background_color_{red, green, blue, alpha}{
		//Use Modern OpenGL and Extensions
		glewExperimental = GL_TRUE;

		GLenum error = glewInit();
		if(error != GLEW_OK){
			//HACK: Convert (const GLubyte*) => (const char*)
			std::string message(reinterpret_cast<const char*>(glewGetErrorString(error)));
			throw(std::runtime_error(std::string(__FILE__) + " | Line " + std::to_string(__LINE__) + "\n\t" + message));
		}
		if(GLEW_VERSION_4_6 != GL_TRUE){
			throw(std::runtime_error(std::string(__FILE__) + " | Line " + std::to_string(__LINE__) + "\n\t" + "Sorry, This Computer Environment does NOT Support OpenGL 4.6."));
		}
#ifdef _DEBUG
		std::clog << "GLEW Version: " << glewGetString(GLEW_VERSION) << std::endl;
		reportDebugInfo();
#endif
		setupSmoothHint();
		setupTextureFlag();
		setupVertexPostProcessingFlag();
		setupRasterizationFlag();
		setupPerFragmentOperationFlag();
		setupDebugOutputFlag();

		axes_shader_ = std::make_unique<GLShader>(AXES_VERTEX_SHADER_PATH_, AXES_FRAGMENT_SHADER_PATH_);
		model_shader_ = std::make_unique<GLShader>(MODEL_VERTEX_SHADER_PATH_, MODEL_FRAGMENT_SHADER_PATH_);

		axes_projection_matrix_location_ = glGetUniformLocation(axes_shader_->getProgram(), "projection_matrix");
		axes_view_matrix_location_ = glGetUniformLocation(axes_shader_->getProgram(), "view_matrix");

		model_projection_matrix_location_ = glGetUniformLocation(model_shader_->getProgram(), "projection_matrix");
		model_view_matrix_location_ = glGetUniformLocation(model_shader_->getProgram(), "view_matrix");
	}

	GLRenderer::~GLRenderer() noexcept{
		glFinish();
	}

	void GLRenderer::clear() const noexcept{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(background_color_[Color::RED_], background_color_[Color::GREEN_], background_color_[Color::BLUE_], background_color_[Color::ALPHA_]);
		return;
	}

	void GLRenderer::computeViewportMatrix(const GLint width, const GLint height) const noexcept{
		glViewport(0, 0, width, height);
		return;
	}

	void GLRenderer::drawAxes(const loser_scene::Scene& scene_ref) noexcept{

		glUseProgram(axes_shader_->getProgram());
		glUniformMatrix4fv(axes_projection_matrix_location_, 1, GL_TRUE, scene_ref.getProjectionMatrixData());
		glUniformMatrix4fv(axes_view_matrix_location_, 1, GL_TRUE, scene_ref.getViewMatrixData());

		GLuint vertex_array_obj = 0;
		glGenVertexArrays(1, &vertex_array_obj);
		glBindVertexArray(vertex_array_obj);

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
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLdouble) * 18, data.data(), GL_STATIC_READ);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_obj);
		glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 0, nullptr);

		glDrawArrays(GL_LINES, 0, 6);

		glDisableVertexAttribArray(0);

		glDeleteBuffers(1, &vertex_buffer_obj);

		glDeleteVertexArrays(1, &vertex_array_obj);

		return;
	}





	void GLRenderer::drawTriangle(const loser_scene::Scene& scene_ref) noexcept{
		//std::cout << va * pa * loser_math::Vector4D{0.0, 0.0, 0.0, 1.0} << std::endl;


		glUseProgram(model_shader_->getProgram());

		glUniformMatrix4fv(model_projection_matrix_location_, 1, GL_TRUE, scene_ref.getProjectionMatrixData());
		glUniformMatrix4fv(model_view_matrix_location_, 1, GL_TRUE, scene_ref.getViewMatrixData());



		constexpr const std::array<GLdouble, 3> a{1.0, 0.0, 0.0};
		constexpr const std::array<GLdouble, 3> b{0.0, 1.0, 0.0};
		constexpr const std::array<GLdouble, 3> c{0.0, 0.0, 1.0};

		const std::array<std::array<GLdouble, 3>, 3> vertices{a, b, c};

		constexpr const std::size_t triangle_num = 1;
		constexpr const std::size_t vertex_num = 3;
		constexpr const std::size_t dimension = 3;


		constexpr const std::array<GLfloat, 12> color{
				1.0, 0.0, 0.0, 1.0,
				0.0, 1.0, 0.0, 1.0,
				0.0, 0.0, 1.0, 1.0
		};

		GLuint vertex_array_obj = 0;
		glGenVertexArrays(1, &vertex_array_obj);
		glBindVertexArray(vertex_array_obj);

		GLuint vertex_buffer_obj = 0;
		glGenBuffers(1, &vertex_buffer_obj);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_obj);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLdouble) * triangle_num * vertex_num * dimension, vertices.data(), GL_STATIC_READ);

		GLuint color_buffer_obj = 1;
		glGenBuffers(1, &color_buffer_obj);
		glBindBuffer(GL_ARRAY_BUFFER, color_buffer_obj);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, color.data(), GL_STATIC_READ);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_obj);
		glVertexAttribPointer(0, dimension, GL_DOUBLE, GL_FALSE, 0, nullptr);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, color_buffer_obj);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

		glDrawArrays(GL_TRIANGLES, 0, triangle_num * vertex_num);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		glDeleteBuffers(1, &vertex_buffer_obj);

		glDeleteVertexArrays(1, &vertex_array_obj);

		return;
	}
	
	/*
	void_t<> GraphicsManager::DrawBall(const Vector4f& center, const std::float_t radius) noexcept(false){

	const int face[] = {
		0, 1, 2,
		0, 2, 3,
		0, 3, 1,
		1, 3, 2
	};

	const float vertex[] = {
		radius, radius, radius,
		radius, -radius, -radius,
		-radius, radius, -radius,
		-radius, -radius, radius
	};

	//std::vector<int> face;
	//std::vector<float> vertex;

	cout << radius << endl;

	int index_cnt = sizeof(face) / sizeof(face[0]);

	glUseProgram(ball_shader_handle_);

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int position;
	int stride = 3 * sizeof(float);
	glGenBuffers(1, &position);
	glBindBuffer(GL_ARRAY_BUFFER, position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);

	unsigned int index;
	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(face), face, GL_STATIC_DRAW);

	glUniformMatrix4fv(ball_mvp_matrix_location_, 1, GL_FALSE, &mvp_matrix_[0][0]);

	glPatchParameteri(GL_PATCH_VERTICES, 3);

	glUniform1f(ball_radius_location_, radius);
	glUniform3f(ball_center_location_, center[0], center[1], center[2]);

	glDrawElements(GL_PATCHES, index_cnt, GL_UNSIGNED_INT, 0);

	return;
}*/
	

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
			std::clog << "\t" << glGetStringi(GL_EXTENSIONS, i)					<< std::endl;
		}

		GLint shader_language_version_num = 0;
		glGetIntegerv(GL_NUM_SHADING_LANGUAGE_VERSIONS, &shader_language_version_num);
		std::clog << "Shader Language Versions:"	<< std::endl;
		for(GLuint i = 0; i < static_cast<GLuint>(shader_language_version_num); ++i){
			std::clog << "\t" << glGetStringi(GL_SHADING_LANGUAGE_VERSION, i)	<< std::endl;
		}

		GLint spir_v_extensions_num = 0;
		glGetIntegerv(GL_NUM_SPIR_V_EXTENSIONS, &spir_v_extensions_num);
		std::clog << "Spir-V Extensions       :"	<< std::endl;
		for(GLuint i = 0; i < static_cast<GLuint>(spir_v_extensions_num); ++i){
			std::clog << "\t" << glGetStringi(GL_SPIR_V_EXTENSIONS, i)			<< std::endl;
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
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
		return;
	}

	void GLRenderer::setupVertexPostProcessingFlag() noexcept{
		glEnable(GL_DEPTH_CLAMP);
#ifdef GL_CLIP_DISTANCE0
		glEnable(GL_CLIP_DISTANCE0);
#endif
#ifdef GL_CLIP_DISTANCE1
		glEnable(GL_CLIP_DISTANCE1);
#endif
#ifdef GL_CLIP_DISTANCE2
		glEnable(GL_CLIP_DISTANCE2);
#endif
#ifdef GL_CLIP_DISTANCE3
		glEnable(GL_CLIP_DISTANCE3);
#endif
#ifdef GL_CLIP_DISTANCE4
		glEnable(GL_CLIP_DISTANCE4);
#endif
#ifdef GL_CLIP_DISTANCE5
		glEnable(GL_CLIP_DISTANCE5);
#endif
		return;
	}

	void GLRenderer::setupRasterizationFlag() noexcept{
		glDisable(GL_RASTERIZER_DISCARD);

		glEnable(GL_MULTISAMPLE);
		glEnable(GL_SAMPLE_SHADING);

		glEnable(GL_PROGRAM_POINT_SIZE);

		glEnable(GL_LINE_SMOOTH);
		glLineWidth(1.0f);

		//For DearImgui
		glDisable(GL_POLYGON_SMOOTH);
		glEnable(GL_CULL_FACE);

		//glFrontFace(GL_CCW);
		glCullFace(GL_BACK);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glEnable(GL_POLYGON_OFFSET_POINT);
		glEnable(GL_POLYGON_OFFSET_LINE);
		glEnable(GL_POLYGON_OFFSET_FILL);

		return;
	}

	void GLRenderer::setupPerFragmentOperationFlag() noexcept{
		glDisable(GL_SCISSOR_TEST);

		glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
		glEnable(GL_SAMPLE_ALPHA_TO_ONE);
		glEnable(GL_SAMPLE_COVERAGE);
		glEnable(GL_SAMPLE_MASK);

		glDisable(GL_STENCIL_TEST);
		//glStencilFunc(GL_LESS);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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