#include "GLShader.hpp"
#include "ShaderFileReader.hpp"
#include <stdexcept>
#ifdef _DEBUG
#include <memory>
#include <iostream>
#endif

namespace loser_renderer{






	GLShader::GLShader(const std::filesystem::path& vertex_shader_file_path, const std::filesystem::path& fragment_shader_file_path) noexcept(false){
		const GLuint vertex_shader_object = glCreateShader(GL_VERTEX_SHADER);
		const GLuint fragment_shader_object = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vertex_shader_source_code = loser_reader::readShaderFile(vertex_shader_file_path);
		
		if(vertex_shader_source_code.empty()){
			throw(std::runtime_error(std::string(__FILE__) + " | Line " + std::to_string(__LINE__) + "\n\t" + "Fail to Read Vertex Shader File."));
		}
		enableSource(vertex_shader_object, vertex_shader_source_code);

		std::string fragment_shader_source_code = loser_reader::readShaderFile(fragment_shader_file_path);
		if(fragment_shader_source_code.empty()){
			throw(std::runtime_error(std::string(__FILE__) + " | Line " + std::to_string(__LINE__) + "\n\t" + "Fail to Read Fragment Shader File."));
		}
		enableSource(fragment_shader_object, fragment_shader_source_code);

		if(!compileShader(vertex_shader_object)){
			throw(std::runtime_error(std::string(__FILE__) + " | Line " + std::to_string(__LINE__) + "\n\t" + "Fail to Compile Vertex Shader."));
		}
		if(!compileShader(fragment_shader_object)){
			throw(std::runtime_error(std::string(__FILE__) + " | Line " + std::to_string(__LINE__) + "\n\t" + "Fail to Compile Fragment Shader."));
		}

		program_ = glCreateProgram();

		glAttachShader(program_, vertex_shader_object);
		glAttachShader(program_, fragment_shader_object);

		if(!linkShader(program_)){
			throw(std::runtime_error(std::string(__FILE__) + " | Line " + std::to_string(__LINE__) + "\n\t" + "Fail to Link Shader."));
		}
	}


	void GLShader::enableSource(const GLuint shader_object, const std::string& source_code) noexcept{
		const GLchar*	code	= source_code.c_str();
		const GLint		length	= source_code.length();
		glShaderSource(shader_object, 1, &code, &length);
		return;
	}


	bool GLShader::compileShader(const GLuint shader_object) noexcept{
		glCompileShader(shader_object);
#ifdef _DEBUG
		GLint is_compiled = 0;
		glGetShaderiv(shader_object, GL_COMPILE_STATUS, &is_compiled);
		if(is_compiled != GL_TRUE){
			reportCompileError(shader_object);
			return false;
		}
#endif
		return true;
	}

	bool GLShader::linkShader(const GLuint program) noexcept{
		glLinkProgram(program);
#ifdef _DEBUG
		GLint is_linked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &is_linked);
		if(is_linked != GL_TRUE){
			reportLinkError(program);
			return false;
		}
#endif
		return true;
	}

#ifdef _DEBUG
	void GLShader::reportCompileError(const GLuint shader_object) noexcept{
		GLint log_length = 0;
		glGetShaderiv(shader_object, GL_INFO_LOG_LENGTH, &log_length);

		std::unique_ptr<GLchar[]> log = std::make_unique<GLchar[]>(static_cast<std::size_t>(log_length));

		glGetShaderInfoLog(shader_object, log_length - 1, &log_length, log.get());
		std::cerr << log.get() << std::endl;

		log.release();

		return;
	}

	void GLShader::reportLinkError(const GLuint prorgam) noexcept{
		GLint log_length = 0;
		glGetProgramiv(prorgam, GL_INFO_LOG_LENGTH, &log_length);

		std::unique_ptr<GLchar[]> log = std::make_unique<GLchar[]>(static_cast<std::size_t>(log_length));
		glGetProgramInfoLog(prorgam, log_length - 1, &log_length, log.get());
		std::cerr << log.get() << std::endl;

		log.release();

		return;
	}
#endif
}