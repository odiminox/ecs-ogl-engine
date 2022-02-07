#pragma once

#include "Component.h"

class TransformComponent : public Component
{
public:
    friend class Object;

    TransformComponent();
	TransformComponent(int TL);
	~TransformComponent();

	void TranslateObjectVec(glm::vec3 &pos);
	void TranslateObjectXYZ(float x, float y, float z);
	void TranslateObjectX(float x);
	void TranslateObjectY(float y);
	void TranslateObjectZ(float z);

	void OffsetObjectVec(glm::vec3 &pos);
	void OffsetObjectXYZ(float x, float y, float z);
	void OffsetObjectX(float x);
	void OffsetObjectY(float y);
	void OffsetObjectZ(float z);

	glm::vec3& GetPositionVec();
	float GetPosX();
	float GetPosY();
	float GetPosZ();
	float* GetPosXYZArray();

	void YTKRotateObjectVec(glm::vec3 vec);
	void RotateObjectXYZ(float xAmount, float yAmount, float zAmount);
	void RotateObjectX(float xAmount);
	void RotateObjectY(float yAmount);
	void RotateObjectZ(float zAmount);

    void RotateLocal(bool isLocal);

	glm::vec3& GetRotationVec();
	float GetRotXAmount();
	float GetRotYAmount();
	float GetRotZAmount();
	float* GetRotXYZAmountArray();

	void ScaleObjectVec(glm::vec3 &scale);
	void ScaleObjectXYZ(float xScale, float yScale, float zScale);
	void ScaleObjectX(float xScale);
	void ScaleObjectY(float yScale);
	void ScaleObjectZ(float zScale);

	glm::vec3& GetScaleVec();
	float GetScaleX();
	float GetScaleY();
	float GetScaleZ();
	float* GetScaleXYZArray();
    void SetTransformLocation(int location);

private:
	int _transformLocation;
protected:
};
