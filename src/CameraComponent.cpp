#include "CameraComponent.h"

CameraComponent::CameraComponent(int CL)
{
	_componentLocation = CL;
}
CameraComponent::~CameraComponent()
{
}

void CameraComponent::PitchCamera(float pitchAngle)
{
    entityManager::gameObjects::cameraComponent::PitchCamera(&wData::Objects[this->GetObjectIWorldPos()], pitchAngle);
}
void CameraComponent::RollCamera(float rollAngle)
{
	entityManager::gameObjects::cameraComponent::RollCamera(&wData::Objects[this->GetObjectIWorldPos()], rollAngle);
}
void CameraComponent::YawCamera(float yawAngle)
{
	entityManager::gameObjects::cameraComponent::YawCamera(&wData::Objects[this->GetObjectIWorldPos()], yawAngle);
}
void CameraComponent::SetPitchYawRoll(float pitchAngle, float yawAngle, float rollAngle)
{
    entityManager::gameObjects::cameraComponent::SetCamPitchYawRoll(&wData::Objects[this->GetObjectIWorldPos()], pitchAngle, yawAngle, rollAngle);

}
void CameraComponent::OffsetPitchYawRoll(float pitchAngle, float yawAngle, float rollAngle)
{

    entityManager::gameObjects::cameraComponent::OffSetCamPitchRoll(&wData::Objects[this->GetObjectIWorldPos()], pitchAngle, yawAngle, rollAngle);
}

float CameraComponent::GetPitch()
{
    return entityManager::gameObjects::cameraComponent::GetCameraPitch(&wData::Objects[this->GetObjectIWorldPos()]);
}
float CameraComponent::GetYaw()
{
	return entityManager::gameObjects::cameraComponent::GetCameraYaw(&wData::Objects[this->GetObjectIWorldPos()]);
}
float CameraComponent::GetRoll()
{
	return entityManager::gameObjects::cameraComponent::GetCameraRoll(&wData::Objects[this->GetObjectIWorldPos()]);
}
float* CameraComponent::GetPitchYawRollArray()
{
	float temp[3];
	temp[0] = wData::CameraComponents[_componentLocation].pitch;
	temp[1] = wData::CameraComponents[_componentLocation].yaw;
	temp[3] = wData::CameraComponents[_componentLocation].roll;
	return temp;
}
glm::vec3 CameraComponent::GetPitchYawRollVec()
{
	glm::vec3 temp;
	temp.x = wData::CameraComponents[_componentLocation].pitch;
	temp.y = wData::CameraComponents[_componentLocation].yaw;
	temp.z = wData::CameraComponents[_componentLocation].roll;
	return temp;
}


float CameraComponent::GetNearPlane()
{
	return wData::CameraComponents[_componentLocation].nearPlane;
}
float CameraComponent::GetFarPlane()
{
	return wData::CameraComponents[_componentLocation].farPlane;
}

glm::mat4 CameraComponent::CamOrientation()
{
    return entityManager::gameObjects::cameraComponent::CamOrientation(&wData::Objects[this->GetObjectIWorldPos()]);
}
glm::vec3 CameraComponent::GetForward()
{

    return entityManager::gameObjects::cameraComponent::GetForward(&wData::Objects[this->GetObjectIWorldPos()]);

}
glm::vec3 CameraComponent::GetUp()
{
    return entityManager::gameObjects::cameraComponent::GetUp(&wData::Objects[this->GetObjectIWorldPos()]);
}
glm::vec3 CameraComponent::GetRight()
{
	return entityManager::gameObjects::cameraComponent::GetRight(&wData::Objects[this->GetObjectIWorldPos()]);
}

void CameraComponent::SetAspectRatio(float amount)
{
	wData::CameraComponents[_componentLocation].aspectRatio = amount;
}
float CameraComponent::GetAspectRatio()
{
	return  wData::CameraComponents[_componentLocation].aspectRatio;
}
