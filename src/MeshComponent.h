#pragma once
#include "Component.h"

class MeshComponent : public Component

{
public:
	MeshComponent(int TL);
	~MeshComponent();

	void AssignDiffuseName(std::string DiffName);
	void AssignNormalName(std::string NormName);
	void AssignSpecularName(std::string SpecName);
	void AssignMeshName(std::string MeshName);

	void LoadDiffuse(std::string diffuseName);

	std::string GetDiffuseName();
	std::string GetNormalName();
	std::string GetSpecularName();
	std::string GetMeshName();

	void SetRedValue(float redVal);
	void SetBlueValue(float blueVal);
	void SetGreenValue(float greenVal);
	void SetAlphaValue(float alphaVal);

	float GetRedValue();
	float GetBlueValue();
	float GetGreenValue();
	float GetAlphaValue();

	void SetInvisible();
	void SetVisible();

private:
	int _transformLocation;

};
