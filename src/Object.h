#ifndef OBJECT_H_
#define OBJECT_H_

#include "ContractMember.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "CameraComponent.h"
#include "PhysicsComponent.h"
#include "LightComponent.h"

#include <vector>


class Object : public ContractMember
{
public:
	Object();
	~Object();

    void SpawnObject();
    void SpawnObject(int tag);
    void SpawnObject(std::string name);

    void DestroyObject();

    void AddChild(Object *child);

    template <typename T> void BindComponent(T* com);

    void AttatchTransformComponent();
    void AttatchMeshComponent();
    void AttatchCameraComponent();
    void AttatchPhysicsComponent();
    void AttatchLightComponent();

    void RemoveTransformComponent();
    void RemoveMeshComponent();
    void RemoveCameraComponent();
    void RemovePhysicsComponent();
    void RemoveLightComponent();

    TransformComponent& GetTC();
    MeshComponent& GetMC();
    CameraComponent& GetCC();
    PhysicsComponent& GetPC();
    LightComponent& GetLC();

    entitySystem::gameObject *GetGameObject();

    //Encapsulate these items
    entitySystem::gameObject *_GO;
    std::vector<Component*> OC;

    int tag;
    int worldPosition;
};

#endif
