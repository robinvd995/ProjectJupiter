#pragma once
#ifdef JPT_ENABLE_OPENGL

#include "OpenGL.h"

#include "JupiterEngine/Renderer/Shader.h"

namespace Jupiter {

	class OpenGLShader : public Shader {

	public:
		OpenGLShader(ShaderLoadData& data) {
			uint vertexShader, fragmentShader = 0;

			const GLchar* vertexSource = (const GLchar*)data.vertexSource.c_str();
			const GLchar* fragmentSource = (const GLchar*)data.fragmentSource.c_str();

			bool compiledVertex = compileShader(vertexShader, GL_VERTEX_SHADER, vertexSource);
			bool compiledFragment = compileShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentSource);

			if (compiledVertex && compiledFragment) {
				uint program = glCreateProgram();

				glAttachShader(program, vertexShader);
				glAttachShader(program, fragmentShader);

				glLinkProgram(program);
				bool succes = verifyShaderLink(program);
				if (succes) m_ShaderId = program;
				else {
					glDeleteProgram(program);
				}

				glDetachShader(program, vertexShader);
				glDetachShader(program, fragmentShader);

				glDeleteShader(vertexShader);
				glDeleteShader(fragmentShader);
			}
			else {
				JPT_ENGINE_ERROR("Could not link shader because of compilation errors!");
			}
		}

		virtual ~OpenGLShader() override {
			glDeleteProgram(m_ShaderId);
		}

		virtual void bind() const override {
			glUseProgram(m_ShaderId);
		}

		virtual void unbind() const override {
			glUseProgram(0);
		}

	private:
		bool compileShader(uint& shaderid, uint shadertype, const GLchar* source) {
			shaderid = glCreateShader(shadertype);
			glShaderSource(shaderid, 1, &source, NULL);
			glCompileShader(shaderid);

			GLint isCompiled = 0;
			glGetShaderiv(shaderid, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE) {
				GLint maxLength = 500;
				glGetShaderiv(shaderid, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shaderid, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shaderid);

				JPT_ENGINE_ERROR("Shader compiler error: \n[0]", infoLog.data());
				JPT_ENGINE_WARN("Shader compilation failed!");
				return false;
			}
			return true;
		}

		bool verifyShaderLink(uint program) {
			GLint isLinked = 0;
			glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
			if (isLinked == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

				glDeleteProgram(program);

				JPT_ENGINE_ERROR("Shader linker error: \n[0]", infoLog.data());
				JPT_ENGINE_WARN("Shader linking failed!");

				return false;
			}
			return true;
		}

		uint m_ShaderId = 0;
	};
}

#endif
