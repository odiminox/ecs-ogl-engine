#include "MeshComponent.h"

MeshComponent::MeshComponent(int TL){
	_transformLocation = TL;
}
MeshComponent::~MeshComponent(){}

void MeshComponent::AssignDiffuseName(std::string DiffName){
	wData::MeshComponents[_transformLocation].diffuseName = DiffName;
}
void MeshComponent::AssignNormalName(std::string NormName){
	wData::MeshComponents[_transformLocation].normalName = NormName;
}
void MeshComponent::AssignSpecularName(std::string SpecName){
	wData::MeshComponents[_transformLocation].specularName = SpecName;
}
void MeshComponent::AssignMeshName(std::string MeshName){
	wData::MeshComponents[_transformLocation].meshName = MeshName;
}

void MeshComponent::LoadDiffuse(std::string diffuseName)
{
	Bitmap bmp = Bitmap::bitmapFromFile(diffuseName);
	bmp.flipVertically();
	wData::MeshComponents[_transformLocation].pTexture = new Texture(bmp);
}

std::string MeshComponent::GetDiffuseName(){
	return wData::MeshComponents[_transformLocation].diffuseName;
}
std::string MeshComponent::GetNormalName(){
	return wData::MeshComponents[_transformLocation].normalName;
}
std::string MeshComponent::GetSpecularName(){
	return wData::MeshComponents[_transformLocation].specularName;
}
std::string MeshComponent::GetMeshName(){
	return wData::MeshComponents[_transformLocation].meshName;
}

void MeshComponent::SetRedValue(float redVal){
	wData::MeshComponents[_transformLocation].RED = redVal;
}
void MeshComponent::SetBlueValue(float blueVal){
	wData::MeshComponents[_transformLocation].BLUE = blueVal;
}
void MeshComponent::SetGreenValue(float greenVal){
	wData::MeshComponents[_transformLocation].GREEN = greenVal;
}
void MeshComponent::SetAlphaValue(float alphaVal){
	wData::MeshComponents[_transformLocation].ALPHA = alphaVal;
}

float MeshComponent::GetRedValue(){
	return wData::MeshComponents[_transformLocation].RED;
}
float MeshComponent::GetBlueValue(){
	return wData::MeshComponents[_transformLocation].BLUE;
}
float MeshComponent::GetGreenValue(){
	return wData::MeshComponents[_transformLocation].GREEN;
}
float MeshComponent::GetAlphaValue(){
	return wData::MeshComponents[_transformLocation].ALPHA;
}

void MeshComponent::SetInvisible(){
	wData::MeshComponents[_transformLocation].ALPHA = 0.0f;
}
void MeshComponent::SetVisible(){
	wData::MeshComponents[_transformLocation].ALPHA = 1.0f;
}
