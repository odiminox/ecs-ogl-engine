#pragma once

#include "Component.h"

class LightComponent : public Component

{
public:
    LightComponent(int LL);
    ~LightComponent();

    void SetLightColourVec(glm::vec4 &col);
    void SetLightColourRGBA(float r, float g, float b, float a);
    void SetLightColourR(float r);
    void SetLightColourG(float g);
    void SetLightColourB(float b);
    void SetLightColourA(float a);

    void SetLightKa(float a, float b, float c);
    void SetLightKd(float a, float b, float c);
    void SetLightKs(float a, float b, float c);

    void SetLightLa(float a, float b, float c);
    void SetLightLd(float a, float b, float c);
    void SetLightLs(float a, float b, float c);

    void SetLightShininess(float shininess);

    void SetLightRadius(float rad);
    float GetLightRadius();

private:
	int _lightLocation;
};

