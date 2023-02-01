#pragma once

#include "JupiterEngine/JupiterEngine.h"

// PhysX includes
#include <PxPhysics.h>
#include <foundation/PxVec2.h>
#include <foundation/PxVec3.h>
#include <foundation/PxVec4.h>
#include <foundation/PxQuat.h>
#include <foundation/PxMat33.h>
#include <foundation/PxMat34.h>
#include <foundation/PxMat44.h>
#include <foundation/PxTransform.h>

namespace Jupiter {

	// Typedefs of PhysX math classes for ease of use
	typedef physx::PxVec2 Vector2;
	typedef physx::PxVec3 Vector3;
	typedef physx::PxVec4 Vector4;
	typedef physx::PxQuat Quaternion;
	typedef physx::PxMat33 Matrix3x3;
	typedef physx::PxMat34 Matrix3x4;
	typedef physx::PxMat44 Matrix4x4;
	typedef physx::PxTransform Transform;

	class JMath {

	public:
		static Matrix4x4 calculateViewMatrix(Transform& transform);

		static Matrix4x4 calculateViewMatrix(Vector3& position, Quaternion& rotation);
		
		static Matrix4x4 calculatePerspectiveProjectionMatrix(float fov, float aspectRatio, float nearClippingPlane, float farClipingPlane);

		static Matrix4x4 calculateOrthographicProjectionMatrix(float left, float right, float bottom, float top, float near, float far);

		static const float JptPi;
	};
}
