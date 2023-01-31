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

	class Shader {

	public:
		virtual ~Shader() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
	};

}
