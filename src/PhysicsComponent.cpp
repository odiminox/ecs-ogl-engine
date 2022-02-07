
#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(int PL){
    _physicsLocation = PL;
}
PhysicsComponent::~PhysicsComponent(){

}

void PhysicsComponent::SetMass(float mass)
{
    wData::PhysicsComponents[_physicsLocation].mass = mass;
}
float PhysicsComponent::GetMass()
{
    return wData::PhysicsComponents[_physicsLocation].mass;
}
