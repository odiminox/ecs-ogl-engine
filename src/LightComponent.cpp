
#include "LightComponent.h"
LightComponent::LightComponent(int LL)
{
    _lightLocation = LL;
}
LightComponent::~LightComponent()
{
}

void LightComponent::SetLightColourVec(glm::vec4 &col)
{
    entityManager::gameObjects::lightComponent::SetLightColourVec(&wData::Objects[this->GetObjectIWorldPos()], col);
}
void LightComponent::SetLightColourRGBA(float r, float g, float b, float a)
{
    entityManager::gameObjects::lightComponent::SetLightColourRGBA(&wData::Objects[this->GetObjectIWorldPos()], r,g,b,a);
}
void LightComponent::SetLightColourR(float r)
{
    entityManager::gameObjects::lightComponent::SetLightColourR(&wData::Objects[this->GetObjectIWorldPos()], r);
}
void LightComponent::SetLightColourG(float g)
{
    entityManager::gameObjects::lightComponent::SetLightColourG(&wData::Objects[this->GetObjectIWorldPos()], g);
}
void LightComponent::SetLightColourB(float b)
{
    entityManager::gameObjects::lightComponent::SetLightColourB(&wData::Objects[this->GetObjectIWorldPos()], b);
}
void LightComponent::SetLightColourA(float a)
{
    entityManager::gameObjects::lightComponent::SetLightColourA(&wData::Objects[this->GetObjectIWorldPos()], a);
}

void LightComponent::SetLightRadius(float rad)
{
    entityManager::gameObjects::lightComponent::SetLightRadius(&wData::Objects[this->GetObjectIWorldPos()], rad);
}
float LightComponent::GetLightRadius()
{
    return entityManager::gameObjects::lightComponent::GetLightRadius(&wData::Objects[this->GetObjectIWorldPos()]);
}


void LightComponent::SetLightKa(float a, float b, float c)
{
    entityManager::gameObjects::lightComponent::SetLightKa(&wData::Objects[this->GetObjectIWorldPos()], a, b, c);
}
void LightComponent::SetLightKd(float a, float b, float c)
{
    entityManager::gameObjects::lightComponent::SetLightKs(&wData::Objects[this->GetObjectIWorldPos()], a, b, c);
}
void LightComponent::SetLightKs(float a, float b, float c)
{
    entityManager::gameObjects::lightComponent::SetLightKd(&wData::Objects[this->GetObjectIWorldPos()], a, b, c);
}

void LightComponent::SetLightLa(float a, float b, float c)
{
    entityManager::gameObjects::lightComponent::SetLightLa(&wData::Objects[this->GetObjectIWorldPos()], a, b, c);
}
void LightComponent::SetLightLd(float a, float b, float c)
{
    entityManager::gameObjects::lightComponent::SetLightLd(&wData::Objects[this->GetObjectIWorldPos()], a, b, c);
}
void LightComponent::SetLightLs(float a, float b, float c)
{
    entityManager::gameObjects::lightComponent::SetLightLs(&wData::Objects[this->GetObjectIWorldPos()], a, b, c);
}


void LightComponent::SetLightShininess(float shininess)
{
    entityManager::gameObjects::lightComponent::SetLightShininess(&wData::Objects[this->GetObjectIWorldPos()], shininess);
}



