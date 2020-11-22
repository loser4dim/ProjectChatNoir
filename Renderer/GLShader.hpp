#pragma once

#ifndef _DLL
#define GLEW_STATIC
#endif
#include <GL/glew.h>
#pragma comment(lib, "opengl32")
#ifdef _DLL
#ifdef _DEBUG
#pragma comment(lib, "glew32d")
#else
#pragma comment(lib, "glew32")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib, "glew32sd")
#else
#pragma comment(lib, "glew32s")
#endif
#endif

#include <filesystem>

namespace loser_renderer{


	class GLShader final{
		GLuint program_ = 0;


	public:
		GLShader() = delete;
		GLShader(const std::filesystem::path& vertex_shader_file_path, const std::filesystem::path& fragment_shader_file_path) noexcept(false);

		GLShader(const GLShader&) = delete;
		GLShader(GLShader&&) = delete;

		GLShader& operator=(const GLShader&) = delete;
		GLShader& operator=(GLShader&&) = delete;

		~GLShader() = default;


	private:




		static void enableSource(const GLuint shader_object, const std::string& source_code) noexcept;



		static bool compileShader(const GLuint shader_object) noexcept;
		static bool linkShader(const GLuint program) noexcept;

#ifdef _DEBUG
		static void reportCompileError(const GLuint shader_object) noexcept;
		static void reportLinkError(const GLuint prorgam) noexcept;
#endif


	public:
		inline GLuint getProgram() const noexcept{
			return program_;
		}
	};


}
