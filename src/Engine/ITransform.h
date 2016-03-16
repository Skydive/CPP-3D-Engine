#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

class ITransform
{
public:
    glm::vec3 Location;
    glm::quat Rotation;
	// FIXME: These rotations may be inconsistent.
    glm::vec3 GetForwardVector() { return glm::vec3(glm::toMat4(Rotation)*glm::vec4(1, 0, 0, 0)); }
    glm::vec3 GetUpVector() { return glm::vec3(glm::toMat4(Rotation)*glm::vec4(0, 1, 0, 0)); }
    glm::vec3 GetRightVector() { return glm::vec3(glm::toMat4(Rotation)*glm::vec4(0, 0, 1, 0)); }
	void LookAt(ITransform* Centre, glm::vec3 up)
	{
		glm::vec3 Direction = glm::normalize(Centre->Location - Location);
		Rotation = glm::rotation(glm::vec3(1, 0, 0), Direction);
		glm::vec3 ProperRightVector = glm::normalize(glm::cross(GetForwardVector(), up));
		Rotation = glm::rotation(GetRightVector(), ProperRightVector) * Rotation;
	}
	void LookAt(ITransform* Centre) { LookAt(Centre, GetUpVector()); }

	static glm::vec3 GetVectorInDirection(glm::quat Direction)
	{
		return glm::vec3(glm::toMat4(Direction)*glm::vec4(1, 0, 0, 0));
	}

	glm::vec3 LocalToRelative(glm::vec3 Position)
	{
		return GetForwardVector()*Position.x + GetUpVector()*Position.y + GetRightVector()*Position.z;
	}

	/*
	glm::vec3 GetForwardVector()
	{
		float this1 = Rotation.w, this2 = Rotation.x, this3 = Rotation.y, this4 = Rotation.z;
		return glm::vec3(
			this1 * this1 + this2 * this2 - this3 * this3 - this4 * this4,
			this3*2 * this2 + this4*2 * this1,
			this4*2 * this2 - this3*2 * this1
		);
	}
    glm::vec3 GetUpVector()
	{
		float this1 = Rotation.w, this2 = Rotation.x, this3 = Rotation.y, this4 = Rotation.z;
		return glm::vec3(
			this4*2 * this1 - this2*2 * this3,
			this2 * this2 - this1 * this1 + this4 * this4 - this3 * this3,
			- this2*2 * this1 - this3*2 * this4
		);
	}
    glm::vec3 GetRightVector()
	{
		float this1 = Rotation.w, this2 = Rotation.x, this3 = Rotation.y, this4 = Rotation.z;
		return glm::vec3(
			this3*2 * this1 + this2*2 * this4,
			this3*2 * this4 - this2*2 * this1,
			this1 * this1 - this2 * this2 - this3 * this3 + this4 * this4
		);
	}
	*/
};

/*
	local X = EyePod:x()
    local Y = EyePod:y()

    local CamMul = 1

    local Pitch = qRotation(Quat:right(),-Y * CamMul)
    local Yaw = qRotation(Quat:up(),X * CamMul)
    local Roll = qRotation(Quat:forward(),-Quat:toAngle():roll())
    Quat = (Pitch * Yaw * Roll) * Quat

    InvQuat = inv(Quat)

    holoAng(3,InvQuat:toAngle())
*/
