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

//		virtual void setInt(const std::string& name, const int value) override {
//			GLuint location = glGetUniformLocation(m_ShaderId, name.c_str());
//			glUniform1i(location, value);
//		}
//
//		virtual void setFloat(const std::string& name, const float value) override {
//			GLuint location = glGetUniformLocation(m_ShaderId, name.c_str());
//			glUniform1f(location, value);
//		}
//
//		virtual void setVec2f(const std::string& name, float* values) override {
//			GLuint location = glGetUniformLocation(m_ShaderId, name.c_str());
//			glUniform2f(location, values[0], values[1]);
//		};
//
//		virtual void setVec3f(const std::string& name, float* values) override {
//			GLuint location = glGetUniformLocation(m_ShaderId, name.c_str());
//			glUniform3f(location, values[0], values[1], values[2]);
//		};
//
//		virtual void setVec4f(const std::string& name, float* values) override {
//			GLuint location = glGetUniformLocation(m_ShaderId, name.c_str());
//			glUniform4f(location, values[0], values[1], values[2], values[3]);
//		};
//
//		virtual void setMat33f(const std::string& name, float* values) override {
//			GLuint location = glGetUniformLocation(m_ShaderId, name.c_str());
//			glUniformMatrix3fv(location, 1, GL_FALSE, values);
//		};
//
//		virtual void setMat44f(const std::string& name, float* values) override {
//			GLuint location = glGetUniformLocation(m_ShaderId, name.c_str());
//			glUniformMatrix4fv(location, 1, GL_FALSE, values);
//		};

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
