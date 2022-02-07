#include "Object.h"
#include "NotificationPayloads.h"

Object::Object()
{
    worldPosition = -1;

    wData::WorldNotificationHandler->JoinSenderToContract(this, "Bind_Component");
}
Object::~Object()
{
}

template <typename T>
void Object::BindComponent(T* com)
{
    ObjectPayload* objectPayload = new ObjectPayload();

    com->SetObjectWorldPos(worldPosition);

    objectPayload->com = com;
    objectPayload->object = this;

    printf("objectpayload object: %p\n", objectPayload->object);
    printf("object: %p\n", this);

    wData::WorldNotificationHandler->PostContract("Bind_Component", objectPayload);
}

void Object::SpawnObject()
{
	int tag = rand()%10000;
    this->tag = tag;
	entityManager::createGameObjectByTag(tag);
	_GO = entityManager::getGameObjectByTag(tag);
    worldPosition = entityManager::getGameObjectWorldPosition(_GO);
    printf("worldpos: %d ml: %p\n", worldPosition, &_GO);
}
void Object::SpawnObject(int tag)
{
    this->tag = tag;
	entityManager::createGameObjectByTag(tag);
	_GO = entityManager::getGameObjectByTag(tag);
    worldPosition = entityManager::getGameObjectWorldPosition(_GO);
}
void Object::SpawnObject(std::string name)
{
}
void Object::DestroyObject()
{
}

entitySystem::gameObject* Object::GetGameObject()
{
    return _GO;
}

void Object::AddChild(Object *child)
{
    entityManager::setGameObjectParentWorldPosition(child->worldPosition, worldPosition);

    entityManager::addChildToGameObject(worldPosition, child->worldPosition);
}

void Object::AttatchTransformComponent()
{
	entityManager::addTransformComponent(_GO);
	TransformComponent* GOTC = new TransformComponent(_GO->componentLocations[0]);
	OC[0] = GOTC;
    OC[0]->SetObjectWorldPos(_GO->worldPosition);
}
void Object::AttatchMeshComponent()
{
	entityManager::addMeshComponent(_GO);
	MeshComponent* GOMC = new MeshComponent(_GO->componentLocations[1]);
	OC[1] = GOMC;
    OC[1]->SetObjectWorldPos(_GO->worldPosition);
}
void Object::AttatchCameraComponent()
{

	entityManager::addCameraComponent(_GO);
	CameraComponent* GOCC = new CameraComponent(_GO->componentLocations[3]);
	OC[2] = GOCC;
    OC[2]->SetObjectWorldPos(_GO->worldPosition);
}
void Object::AttatchPhysicsComponent()
{
    if((_GO->gameObjectID & 128) == 128){
        entityManager::addPhysicsComponent(_GO);
        PhysicsComponent* GOPC = new PhysicsComponent(_GO->componentLocations[2]);
        OC[3] = GOPC;
        OC[3]->SetObjectWorldPos(_GO->worldPosition);
    } else {
        std::cout<<"gameObject does not contain transform component. Physics components relies on transform component, please ammend."<<std::endl;
    }
}

void Object::AttatchLightComponent()
{
    if((_GO->gameObjectID & 128) == 128){
        entityManager::addLightComponent(_GO);
        LightComponent* GOLC = new LightComponent(_GO->componentLocations[4]);
        OC[4] = GOLC;
        OC[4]->SetObjectWorldPos(_GO->worldPosition);
    }else {
        std::cout<<"gameObject does not contain transform component. Light components relies on transform component, please ammend."<<std::endl;
    }

}
void Object::RemoveTransformComponent()
{
}
void Object::RemoveMeshComponent()
{
}
void Object::RemoveCameraComponent()
{
}
void Object::RemovePhysicsComponent()
{
}
void Object::RemoveLightComponent()
{
}
TransformComponent& Object::GetTC(){
   // if((_GO->gameObjectID & 128) == 128){
        TransformComponent* temp = static_cast<TransformComponent*>(OC[0]);
        return *temp;
   // } else {
   //     std::cout<<"gameObject does not contain transform component, add transform component to use it, please ammend."<<std::endl;
       // return;
 //   }
}
MeshComponent& Object::GetMC(){
   // if((_GO->gameObjectID & 64) == 64){
	MeshComponent* temp = static_cast<MeshComponent*>(OC[1]);
	return *temp;
   // } else {
   //     std::cout<<"gameObject does not contain mesh component, add mesh component to use it, please ammend."<<std::endl;
        //return NULL;
   // }
}
CameraComponent& Object::GetCC(){
   // if((_GO->gameObjectID & 16) == 16){
        CameraComponent* temp = static_cast<CameraComponent*>(OC[2]);
        return *temp;
  //  } else {
   //     std::cout<<"gameObject does not contain camera component, add camera component to use it, please ammend."<<std::endl;
        //return NULL;
   // }
}
PhysicsComponent& Object::GetPC(){
   // if((_GO->gameObjectID & 32) == 32){
        PhysicsComponent* temp = static_cast<PhysicsComponent*>(OC[3]);
        return *temp;
  //  } else {
   //     std::cout<<"gameObject does not contain physics component, add physics component to use it, please ammend."<<std::endl;
        //return NULL;
   // }
}

LightComponent& Object::GetLC(){
    LightComponent* temp = static_cast<LightComponent*>(OC[4]);
    return *temp;

}

template void Object::BindComponent<TransformComponent>(TransformComponent* com);
template void Object::BindComponent<MeshComponent>(MeshComponent* com);
template void Object::BindComponent<CameraComponent>(CameraComponent* com);
template void Object::BindComponent<PhysicsComponent>(PhysicsComponent* com);
template void Object::BindComponent<LightComponent>(LightComponent* com);
