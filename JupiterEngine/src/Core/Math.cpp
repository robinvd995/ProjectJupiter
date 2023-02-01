#include "JupiterEngine/Core/Math.h"

namespace Jupiter {

	const float JMath::JptPi = physx::PxPi;

	Matrix4x4 JMath::calculateViewMatrix(Transform& transform) {
		Matrix4x4 model = transform.getInverse();

		Matrix4x4 view(1.0);
		view[0][0] = model[0][0]; view[0][1] = model[0][1]; view[0][2] = model[0][2];
		view[1][0] = model[1][0]; view[1][1] = model[1][1]; view[1][2] = model[2][2];
		view[2][0] = model[2][0]; view[2][1] = model[2][1]; view[2][2] = model[1][2];

		view[3][0] = -model[3][0];
		view[3][1] = -model[3][1];
		view[3][2] = -model[3][2];
		return view;
	}

	Matrix4x4 JMath::calculateViewMatrix(Vector3& position, Quaternion& rotation) {
		Transform transform(position, rotation);
		Matrix4x4 model = transform.getInverse();

		Matrix4x4 view(1.0);
		view[0][0] = model[0][0]; view[0][1] = model[0][1]; view[0][2] = model[0][2];
		view[1][0] = model[1][0]; view[1][1] = model[1][1]; view[1][2] = model[2][2];
		view[2][0] = model[2][0]; view[2][1] = model[2][1]; view[2][2] = model[1][2];

		view[3][0] = -model[3][0];
		view[3][1] = -model[3][1];
		view[3][2] = -model[3][2];
		return view;
	}


	Matrix4x4 JMath::calculatePerspectiveProjectionMatrix(float fov, float aspectRatio, float nearClippingPlane, float farClipingPlane) {
		float tanHalfFov = tan(fov * 0.5f * JptPi / 180.0f);
		float range = farClipingPlane - nearClippingPlane;

		Matrix4x4 mat(0.0f);
		mat[0][0] = 1.0f / (tanHalfFov * aspectRatio);
		mat[1][1] = 1.0f / tanHalfFov;
		mat[2][2] = -(farClipingPlane + nearClippingPlane) / range;
		mat[2][3] = -1.0f;
		mat[3][2] = -(2.0f * farClipingPlane * nearClippingPlane) / range;

		return mat;
	}

	Matrix4x4 JMath::calculateOrthographicProjectionMatrix(float left, float right, float bottom, float top, float near, float far) {
		Matrix4x4 mat(0.0f);
		mat[0][0] = 2.0f / (right - left);
		mat[1][1] = 2.0f / (top - bottom);
		mat[2][2] = -2.0f / (far - near);
		mat[3][0] = -(right + left) / (right - left);
		mat[3][1] = -(top + bottom) / (top - bottom);
		mat[3][2] = -(far + near) / (far - near);
		mat[3][3] = 1.0f;
		
		return mat;
	}
}