#include "TransformComponent.h"

TransformComponent::TransformComponent()
{
    _componentID = TRANSFORM;
    printf("Transform Component ID is: %d\n", _componentID);
}

TransformComponent::TransformComponent(int TL)
{
	_transformLocation = TL;
}
TransformComponent::~TransformComponent()
{
}

void TransformComponent::SetTransformLocation(int location)
{
    _transformLocation = location;
}

void TransformComponent::TranslateObjectVec(glm::vec3 &pos)
{
	entityManager::gameObjects::transformComponent::TranslateVec(&wData::Objects[this->GetObjectIWorldPos()],pos);
}
void TransformComponent::TranslateObjectXYZ(float x, float y, float z){
    entityManager::gameObjects::transformComponent::TranslateXYZ(&wData::Objects[this->GetObjectIWorldPos()], x, y, z);
}
void TransformComponent::TranslateObjectX(float x){
	entityManager::gameObjects::transformComponent::TranslateX(&wData::Objects[this->GetObjectIWorldPos()],x);
}
void TransformComponent::TranslateObjectY(float y){
	entityManager::gameObjects::transformComponent::TranslateY(&wData::Objects[this->GetObjectIWorldPos()],y);
}
void TransformComponent::TranslateObjectZ(float z){
	entityManager::gameObjects::transformComponent::TranslateZ(&wData::Objects[this->GetObjectIWorldPos()],z);
}

void TransformComponent::OffsetObjectVec(glm::vec3 &pos){
	entityManager::gameObjects::transformComponent::OffsetVec(&wData::Objects[this->GetObjectIWorldPos()],pos);
}
void TransformComponent::OffsetObjectXYZ(float x, float y, float z){
	entityManager::gameObjects::transformComponent::OffsetXYZ(&wData::Objects[this->GetObjectIWorldPos()], x, y, z);
}
void TransformComponent::OffsetObjectX(float x){
	entityManager::gameObjects::transformComponent::OffsetX(&wData::Objects[this->GetObjectIWorldPos()],x);
}
void TransformComponent::OffsetObjectY(float y){
	entityManager::gameObjects::transformComponent::OffsetY(&wData::Objects[this->GetObjectIWorldPos()],y);
}
void TransformComponent::OffsetObjectZ(float z){
	entityManager::gameObjects::transformComponent::OffsetZ(&wData::Objects[this->GetObjectIWorldPos()],z);
}

glm::vec3& TransformComponent::GetPositionVec(){

    return wData::TransformComponents[_transformLocation].positon;
}
float TransformComponent::GetPosX(){
	return wData::TransformComponents[_transformLocation].positon.x;
}
float TransformComponent::GetPosY(){
	return wData::TransformComponents[_transformLocation].positon.y;
}
float TransformComponent::GetPosZ(){
	return wData::TransformComponents[_transformLocation].positon.z;
}
float* TransformComponent::GetPosXYZArray(){
	float pos[3];
	pos[0] = wData::TransformComponents[_transformLocation].positon.x;
	pos[1] = wData::TransformComponents[_transformLocation].positon.y;
	pos[2] = wData::TransformComponents[_transformLocation].positon.z;
	return pos;
}
void TransformComponent::YTKRotateObjectVec(glm::vec3 vec){
	wData::TransformComponents[_transformLocation].rotX = vec.x;
	wData::TransformComponents[_transformLocation].rotY = vec.y;
	wData::TransformComponents[_transformLocation].rotZ = vec.z;
}
void TransformComponent::RotateObjectXYZ(float xAmount, float yAmount, float zAmount){
	wData::TransformComponents[_transformLocation].rotX = xAmount;
	wData::TransformComponents[_transformLocation].rotY = yAmount;
	wData::TransformComponents[_transformLocation].rotZ = zAmount;
}
void TransformComponent::RotateObjectX(float xAmount){
	wData::TransformComponents[_transformLocation].rotX = xAmount;
}
void TransformComponent::RotateObjectY(float yAmount){
	wData::TransformComponents[_transformLocation].rotY = yAmount;
}
void TransformComponent::RotateObjectZ(float zAmount){
	wData::TransformComponents[_transformLocation].rotZ = zAmount;
}

glm::vec3& TransformComponent::GetRotationVec(){
	glm::vec3 rot;
	rot.x = wData::TransformComponents[_transformLocation].rotX;
	rot.y = wData::TransformComponents[_transformLocation].rotY;
	rot.z = wData::TransformComponents[_transformLocation].rotZ;
	return rot;
}
float TransformComponent::GetRotXAmount(){
	return wData::TransformComponents[_transformLocation].rotX;
}
float TransformComponent::GetRotYAmount(){
	return wData::TransformComponents[_transformLocation].rotY;
}
float TransformComponent::GetRotZAmount(){
	return wData::TransformComponents[_transformLocation].rotZ;
}
float* TransformComponent::GetRotXYZAmountArray(){
	float rot[3];
	rot[0] = wData::TransformComponents[_transformLocation].rotX;
	rot[1] = wData::TransformComponents[_transformLocation].rotY;
	rot[2] = wData::TransformComponents[_transformLocation].rotZ;
	return rot;
}

void TransformComponent::ScaleObjectVec(glm::vec3 &scale){
	wData::TransformComponents[_transformLocation].scale = scale;
}
void TransformComponent::ScaleObjectXYZ(float xScale, float yScale, float zScale){
	wData::TransformComponents[_transformLocation].scale.x = xScale;
	wData::TransformComponents[_transformLocation].scale.y = yScale;
	wData::TransformComponents[_transformLocation].scale.z = zScale;
    //If the object belonging to this transform has a physics component, we must also scale the collision shape
    if((wData::Objects[this->GetObjectIWorldPos()].gameObjectID & 32) == 32){

        entityManager::gameObjects::physicsComponent::SetCollisionShapeScale(&wData::Objects[this->GetObjectIWorldPos()], xScale, yScale, zScale);
    }

}
void TransformComponent::ScaleObjectX(float xScale){
	wData::TransformComponents[_transformLocation].scale.x = xScale;
}
void TransformComponent::ScaleObjectY(float yScale){
	wData::TransformComponents[_transformLocation].scale.y = yScale;
}
void TransformComponent::ScaleObjectZ(float zScale){
	wData::TransformComponents[_transformLocation].scale.z = zScale;
}

glm::vec3& TransformComponent::GetScaleVec(){
	return wData::TransformComponents[_transformLocation].scale;
}
float TransformComponent::GetScaleX(){
	return wData::TransformComponents[_transformLocation].scale.x;
}
float TransformComponent::GetScaleY(){
	return wData::TransformComponents[_transformLocation].scale.y;
}
float TransformComponent::GetScaleZ(){
	return wData::TransformComponents[_transformLocation].scale.z;
}
float* TransformComponent::GetScaleXYZArray(){
	float scale[3];
	scale[0] = wData::TransformComponents[_transformLocation].scale.x;
	scale[1] = wData::TransformComponents[_transformLocation].scale.y;
	scale[2] = wData::TransformComponents[_transformLocation].scale.z;
	return scale;
}
