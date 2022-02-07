#pragma once

#include "Component.h"

class CameraComponent : public Component

{
public:
	CameraComponent(int CL);
	~CameraComponent();

	void PitchCamera(float pitchAngle);
	void RollCamera(float rollAngle);
	void YawCamera(float yawAngle);
	void SetPitchYawRoll(float pitchAngle, float yawAngle, float rollAngle);
	void OffsetPitchYawRoll(float pitchAngle, float yawAngle, float rollAngle);

	float GetPitch();
	float GetYaw();
	float GetRoll();
	float* GetPitchYawRollArray();
	glm::vec3 GetPitchYawRollVec();

	float GetNearPlane();
	float GetFarPlane();

	glm::mat4 CamOrientation();
	glm::vec3 GetForward();
	glm::vec3 GetUp();
	glm::vec3 GetRight();

	void SetAspectRatio(float amount);
	float GetAspectRatio();

private:

	int _componentLocation;

};
