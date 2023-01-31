#pragma once

#include "JupiterCore/JupiterVertex.h"

#include "JupiterEngine/JupiterEngine.h"
#include "JupiterEngine/Core/Layer.h"
#include "JupiterEngine/Renderer/RenderFunctions.h"

#include <fstream>

namespace Juno {

	class JunoLayer : public Jupiter::Layer {

	public:
		JunoLayer() {}

		JunoLayer(const std::string& name) :
			m_LayerName(name)
		{}

		virtual ~JunoLayer() override {
			
		}

		virtual void onAdded() override {
			std::ifstream vertFile("assets/test_vert.glsl");
			std::ifstream fragFile("assets/test_frag.glsl");

			std::stringstream vertBuffer, fragBuffer;
			vertBuffer << vertFile.rdbuf();
			fragBuffer << fragFile.rdbuf();

			Jupiter::ShaderLoadData sld;
			sld.vertexSource = vertBuffer.str();
			sld.fragmentSource = fragBuffer.str();

			Jupiter::s_ptr<Jupiter::Shader> shader = Jupiter::RenderFunctions::createShader(sld);

			static float vertexData[] = {
				-0.5f, -0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,
				0.0f,  0.5f, 0.0f
			};

			Jupiter::VertexLayout bufferLayout(1);
			bufferLayout.addElement(0, { "a_Position", &Jupiter::JupiterDataTypes::type_vec3f, false});
			bufferLayout.finalizeLayout();

			Jupiter::VertexBufferSpecification bufferSpec(Jupiter::BufferUsage::STATIC);

			Jupiter::s_ptr<Jupiter::VertexBuffer> buffer = Jupiter::RenderFunctions::createVertexBuffer(&vertexData[0], 9, bufferLayout, bufferSpec);
		}

		virtual void onRemoved() override {

		}

		virtual void onUpdate() override {

		}

		virtual void onFixedUpdate() override {

		}

	private:
		std::string m_LayerName;
	};
}