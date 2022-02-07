#include "ComponentDelegate.h"
#include "worldData.h"
#include "EntityManager.h"
#include "memoryManager.h"
#include "Component.h"
#include "TransformComponent.h"

void ComponentDelegate::BindComponentCallback(ObjectPayload& payload)
{
    printf("Executed contract: %d \n", payload.object->worldPosition);

    if (payload.com->GetID() == TRANSFORM)
    {
        printf("ComId : %d\n", payload.com->GetID());
        //printf("gameObjectID: %d\n", payload.object->_GO->gameObjectID);

        //entitySystem::gameObject* GO = payload.object->GetGameObject();
        //entityManager::addTransformComponent(GO);
        //payload.object->OC[0] = payload.com;
    }
}

void ComponentDelegate::DetachComponentCallback()
{

}

ComponentDelegate::ComponentDelegate()
{
    wData::WorldNotificationHandler->CreateContract("Bind_Component");
    wData::WorldNotificationHandler->JoinObserverToContract(this, this->BindComponentCallback, "Bind_Component");
}

ComponentDelegate::~ComponentDelegate()
{

}

