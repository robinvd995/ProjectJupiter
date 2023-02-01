#pragma once

#include "JupiterCore/JupiterVertex.h"

#include "JupiterEngine/JupiterEngine.h"
#include "JupiterEngine/Core/Layer.h"
#include "JupiterEngine/Core/Math.h"
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

			// -----  START:  Create Shader -----
			std::ifstream vertFile("assets/test_vert.glsl");
			std::ifstream fragFile("assets/test_frag.glsl");

			std::stringstream vertBuffer, fragBuffer;
			vertBuffer << vertFile.rdbuf();
			fragBuffer << fragFile.rdbuf();

			Jupiter::ShaderLoadData sld;
			sld.vertexSource = vertBuffer.str();
			sld.fragmentSource = fragBuffer.str();

			m_Shader = Jupiter::RenderFunctions::createShader(sld);
			// -----   END:   Create Shader -----


			// -----  START:  Create VertexBuffer -----
			static float vertexData[] = {
				-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
				0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
				0.0f,  0.5f, 0.0f, 0.5f, 0.0f
			};

			Jupiter::VertexLayout bufferLayout(2);
			bufferLayout.addElement(0, { "a_Position", &Jupiter::JupiterDataTypes::type_vec3f, false });
			bufferLayout.addElement(1, { "a_TextureCoord", &Jupiter::JupiterDataTypes::type_vec2f, false });
			bufferLayout.finalizeLayout();

			Jupiter::VertexBufferSpecification bufferSpec(Jupiter::BufferUsage::STATIC);

			m_VertexBuffer = Jupiter::RenderFunctions::createVertexBuffer(&vertexData[0], 15, bufferLayout, bufferSpec);
			// -----   END:   Create VertexBuffer -----


			// -----  START:  Create Texture2D -----
			Jupiter::JupiterTextureLoader texLoader("assets/peepohottub.png");
			Jupiter::TextureSource texSource(texLoader);
			Jupiter::TextureSpecification texSpec(Jupiter::TextureFormat::RGBA);

			m_Texture = Jupiter::RenderFunctions::createTexture2D(texSource, texSpec);
			texLoader.free();
			// -----   END:   Create Texture2D -----


			// -----  START:  Create UniformBuffer -----
			m_ModelUniformBuffer = Jupiter::RenderFunctions::createUniformBuffer(128);
			m_ModelMatrix = Jupiter::Matrix4x4(1);
			m_ModelUniformBuffer->bufferData(0, 64, (const char*)m_ModelMatrix.front());

			m_SceneUniformBuffer = Jupiter::RenderFunctions::createUniformBuffer(128);
			// -----   END:   Create UniformBuffer -----

			// -----  START:  Create ProjectionMatrix -----
			m_ProjectionMatrix = Jupiter::JMath::calculatePerspectiveProjectionMatrix(60.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
			m_SceneUniformBuffer->bufferData(64, 64, (const char*)m_ProjectionMatrix.front());
			// -----   END:   Create ProjectionMatrix -----
		}

		virtual void onRemoved() override {

		}

		virtual void onUpdate() override {
			m_Shader->bind();
			m_VertexBuffer->bind();
			m_Texture->bind();
			
			m_ModelUniformBuffer->bind(0);
			m_SceneUniformBuffer->bind(1);

			Jupiter::RenderFunctions::drawArrays(0, 3);
		}

		virtual void onFixedUpdate() override {
			Jupiter::Vector3 axis(0.0f, 1.0f, 0.0f);
			float angle = physx::PxPi / 100.0f;

			m_ModelMatrix.rotate(axis);

			Jupiter::Quaternion quat(angle, axis);
			Jupiter::Matrix4x4 rot(quat);

			m_ModelMatrix *= rot;

			// modelMatrix.column0.x = rot[0][0]; modelMatrix.column0.y = rot[0][1]; modelMatrix.column0.z = rot[0][2];
			// modelMatrix.column1.x = rot[1][0]; modelMatrix.column1.y = rot[1][1]; modelMatrix.column0.z = rot[1][2];
			// modelMatrix.column2.x = rot[2][0]; modelMatrix.column2.y = rot[2][1]; modelMatrix.column0.z = rot[2][2];

			m_ModelUniformBuffer->bufferData(0, 64, (const char*)m_ModelMatrix.front());

			Jupiter::Vector3 cameraPosition(0.0f, 0.0f, -10.0f);
			Jupiter::Quaternion cameraRotation(physx::PxIDENTITY::PxIdentity);
			m_ViewMatrix = Jupiter::JMath::calculateViewMatrix(cameraPosition, cameraRotation);
			m_SceneUniformBuffer->bufferData(0, 64, (const char*)m_ViewMatrix.front());
		}

	private:
		std::string m_LayerName;
		Jupiter::s_ptr<Jupiter::Shader> m_Shader;
		Jupiter::s_ptr<Jupiter::VertexBuffer> m_VertexBuffer;
		Jupiter::s_ptr<Jupiter::Texture> m_Texture;
		Jupiter::s_ptr<Jupiter::UniformBuffer> m_ModelUniformBuffer;
		Jupiter::s_ptr<Jupiter::UniformBuffer> m_SceneUniformBuffer;

		Jupiter::Matrix4x4 m_ModelMatrix;
		Jupiter::Matrix4x4 m_ViewMatrix;
		Jupiter::Matrix4x4 m_ProjectionMatrix;
	};
}
