#pragma once

#include "Component.h"

class PhysicsComponent : public Component

{
public:
	PhysicsComponent(int PL);
	~PhysicsComponent();

    void SetMass(float mass);
    float GetMass();


private:
    int _physicsLocation;

};
