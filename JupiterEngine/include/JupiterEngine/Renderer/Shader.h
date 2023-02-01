#pragma once

namespace Jupiter {

	/// <summary>
	/// Rename to ShaderSource?
	/// Struct carrying the data needed to load a shader into the targeted graphics api
	/// TODO spirv source into here
	/// </summary>
	struct ShaderLoadData {
		std::string filename;
		std::string vertexSource;
		std::string fragmentSource;
	};

	/// <summary>
	/// Object representation of a shader
	/// </summary>
	class Shader {

	public:
		virtual ~Shader() {}

		/// <summary>
		/// 
		/// </summary>
		virtual void bind() const = 0;

		/// <summary>
		/// 
		/// </summary>
		virtual void unbind() const = 0;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="name"></param>
		/// <param name="value"></param>
//		virtual void setInt(const std::string& name, const int value) = 0;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="name"></param>
		/// <param name="value"></param>
//		virtual void setFloat(const std::string& name, const float value) = 0;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="name"></param>
		/// <param name="values"></param>
//		virtual void setVec2f(const std::string& name, float* values) = 0;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="name"></param>
		/// <param name="values"></param>
//		virtual void setVec3f(const std::string& name, float* values) = 0;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="name"></param>
		/// <param name="values"></param>
//		virtual void setVec4f(const std::string& name, float* values) = 0;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="name"></param>
		/// <param name="values"></param>
//		virtual void setMat33f(const std::string& name, float* values) = 0;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="name"></param>
		/// <param name="values"></param>
//		virtual void setMat44f(const std::string& name, float* values) = 0;
	};

}
