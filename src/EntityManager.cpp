#include "EntityManager.h"

std::vector<entitySystem::gameObject> wData::Objects;
std::vector<entitySystem::transformComponent> wData::TransformComponents;
std::vector<entitySystem::meshComponent> wData::wData::MeshComponents;
std::vector<entitySystem::cameraComponent> wData::CameraComponents;
std::vector<entitySystem::physicsComponent> wData::PhysicsComponents;
std::vector<entitySystem::lightComponent> wData::LightComponents;
std::vector<int> wData::Rigidbodies;

NotificationHandler* wData::WorldNotificationHandler = new NotificationHandler();

int eData::tCounter;
int eData::mCounter;
int eData::pCounter;
int eData::cCounter;
int eData::lCounter;

int eData::wCounter;

GLSLShader *eData::shaderLoader = new GLSLShader();
glm::mat4 eData::view;
glm::mat4 eData::projection;

void entityManager::createGameObjectByTag(int tag)
{
	entitySystem::gameObject GO;
	GO.tag = tag;//tag that we can identify this game object by
    GO.worldPosition = eData::wCounter;//Position of the object in the game object vector
    eData::wCounter++;
	wData::Objects.push_back(GO);

}

void entityManager::createGameObjectByName(std::string name)
{
	entitySystem::gameObject GO;
	GO.name = name;
    GO.worldPosition = eData::wCounter;
    eData::wCounter++;
	wData::Objects.push_back(GO);
}

entitySystem::gameObject* entityManager::getGameObjectByTag(int tag)
{
	for(int i = 0; i < wData::Objects.size(); ++i){
		if(wData::Objects[i].tag == tag){
			return &wData::Objects[i];
		}
	}
}
//entitySystem::gameObject* entityManager::getGameObjectByName(std::string name)
//{
//	/*for(int i = 0; i < worldwData::Objects.size(); ++i){
//		if(worldwData::Objects[i].name == name){
//			return &worldwData::Objects[i];
//		}
//	}*/
//}


int entityManager::getGameObjectWorldPosition(entitySystem::gameObject* GO)
{
    return GO->worldPosition;
}

void entityManager::setGameObjectParentWorldPosition(int childWorldPos, int parentWorldPos)
{
    wData::Objects[childWorldPos].parentGameObjectID = parentWorldPos;
}

void entityManager::addTransformComponent(entitySystem::gameObject* GO)
{
    printf("null: %d\n", GO->gameObjectID);
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
		printf("Game Object already contains transform component! \n");
	}else {
		entitySystem::transformComponent TC;					 //Create the new component
		GO->gameObjectID = (GO->gameObjectID + TRANSFORM);			//Set flags in GO ID so we recognise the component has been added
		TC.gameObjectForeignKey = GO->gameObjectForeignKey;		 //Associate the id of the GO with the component
		wData::TransformComponents.push_back(TC); //Add it to the appropriate world components
		GO->componentLocations[0] = eData::tCounter;				  //Access the location of the component in the world vector
		eData::tCounter++;
        printf("Adding transform component");
	}
}
void entityManager::addMeshComponent(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & MESH) == MESH){
		printf("Game Object already contains mesh component!");
	}else {
		entitySystem::meshComponent MC;
		wData::wData::MeshComponents.push_back(MC);
		GO->gameObjectID = (GO->gameObjectID + MESH);
		MC.gameObjectForeignKey = GO->gameObjectForeignKey;
		GO->componentLocations[1] = eData::mCounter;
		eData::mCounter++;
	}
}
void entityManager::addPhysicsComponent(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & PHYSICS) == PHYSICS){
		printf("Game Object already contains physics component!");
	}else{
		entitySystem::physicsComponent PC;
		wData::PhysicsComponents.push_back(PC);
		GO->gameObjectID = (GO->gameObjectID + PHYSICS);
		PC.gameObjectForeignKey = GO->gameObjectForeignKey;
		GO->componentLocations[2] = eData::pCounter;
		eData::pCounter++;
	}
}
void entityManager::addCameraComponent(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & CAMERA) == CAMERA){
		printf("Game Object already contains camera component!");
	}else {
		entitySystem::cameraComponent CC;
		wData::CameraComponents.push_back(CC);
		GO->gameObjectID = (GO->gameObjectID + CAMERA);
		CC.gameObjectForeignKey = GO->gameObjectForeignKey;
		GO->componentLocations[3] = eData::cCounter;
		eData::cCounter++;
	}
}

void entityManager::addLightComponent(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
		printf("Game Object already contains light component!");
	}else {
        entitySystem::lightComponent LC;
		wData::LightComponents.push_back(LC);
		GO->gameObjectID = (GO->gameObjectID + LIGHT);
		LC.gameObjectForeignKey = GO->gameObjectForeignKey;
		GO->componentLocations[4] = eData::lCounter;
		eData::lCounter++;
	}
}

void entityManager::removeTransformComponent(entitySystem::gameObject* GO)
{
}
void entityManager::removePhysicsComponent(entitySystem::gameObject* GO)
{
}
void entityManager::removeCameraComponent(entitySystem::gameObject* GO)
{
}
void entityManager::removeMeshComponent(entitySystem::gameObject* GO)
{
}
void entityManager::removeLightComponent(entitySystem::gameObject* GO)
{
}
void entityManager::addChildToGameObject(int parent, int child)
{
    wData::Objects[parent].childGameObjectIDs.push_back(child);
}
void entityManager::removeChildFromGameObject(entitySystem::gameObject* parent, entitySystem::gameObject* child)
{
}

void entityManager::gameObjects::transformComponent::OffsetVec(entitySystem::gameObject* GO, glm::vec3 &offset)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){ //The gameObject has the transform component
        glm::vec3 tempTran;
		wData::TransformComponents[GO->componentLocations[0]].positon*=offset;
	}
}
void entityManager::gameObjects::transformComponent::OffsetXYZ(entitySystem::gameObject* GO,float x, float y, float z)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
        wData::TransformComponents[GO->componentLocations[0]].positon.x += x;
        wData::TransformComponents[GO->componentLocations[0]].positon.y += y;
        wData::TransformComponents[GO->componentLocations[0]].positon.z += z;

    }
}
void entityManager::gameObjects::transformComponent::OffsetX(entitySystem::gameObject* GO,float x)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
		wData::TransformComponents[GO->componentLocations[0]].positon.x += x;
	}
}
void entityManager::gameObjects::transformComponent::OffsetY(entitySystem::gameObject* GO,float y)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
		wData::TransformComponents[GO->componentLocations[0]].positon.y += y;
	}
}
void entityManager::gameObjects::transformComponent::OffsetZ(entitySystem::gameObject* GO,float z)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
		wData::TransformComponents[GO->componentLocations[0]].positon.z += z;
	}
}

void entityManager::gameObjects::transformComponent::TranslateVec(entitySystem::gameObject* GO, glm::vec3 &pos)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
		wData::TransformComponents[GO->componentLocations[0]].positon = pos;
	}
}
void entityManager::gameObjects::transformComponent::TranslateXYZ(entitySystem::gameObject* GO, float x, float y, float z)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
		wData::TransformComponents[GO->componentLocations[0]].positon.x = x;
        wData::TransformComponents[GO->componentLocations[0]].positon.y = y;
        wData::TransformComponents[GO->componentLocations[0]].positon.z = z;
	}
}
void entityManager::gameObjects::transformComponent::TranslateX(entitySystem::gameObject* GO,float x)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
		wData::TransformComponents[GO->componentLocations[0]].positon.x = x;;
	}
}
void entityManager::gameObjects::transformComponent::TranslateY(entitySystem::gameObject* GO,float y)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
		wData::TransformComponents[GO->componentLocations[0]].positon.y = y;
	}
}
void entityManager::gameObjects::transformComponent::TranslateZ(entitySystem::gameObject* GO,float z)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
		wData::TransformComponents[GO->componentLocations[0]].positon.z = z;
	}
}

glm::vec3 entityManager::gameObjects::transformComponent::GetPosVec(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
		return wData::TransformComponents[GO->componentLocations[0]].positon;
	}
}
float entityManager::gameObjects::transformComponent::GetPosX(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
		return wData::TransformComponents[GO->componentLocations[0]].positon.x;
	}
}
float entityManager::gameObjects::transformComponent::GetPosY(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
		return wData::TransformComponents[GO->componentLocations[0]].positon.y;
	}
}
float entityManager::gameObjects::transformComponent::GetPosZ(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
		return wData::TransformComponents[GO->componentLocations[0]].positon.z;
	}
}

void entityManager::gameObjects::transformComponent::RotateX(entitySystem::gameObject* GO,float amount)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
		wData::TransformComponents[GO->componentLocations[0]].rotX = amount;
	}
}
void entityManager::gameObjects::transformComponent::RotateY(entitySystem::gameObject* GO,float amount)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
		wData::TransformComponents[GO->componentLocations[0]].rotY = amount;
	}
}
void entityManager::gameObjects::transformComponent::RotateZ(entitySystem::gameObject* GO,float amount)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
		wData::TransformComponents[GO->componentLocations[0]].rotZ = amount;
	}
}

float entityManager::gameObjects::transformComponent::GetRotX(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
		return wData::TransformComponents[GO->componentLocations[0]].rotX;
	}
}
float entityManager::gameObjects::transformComponent::GetRotY(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
		return wData::TransformComponents[GO->componentLocations[0]].rotY;
	}
}
float entityManager::gameObjects::transformComponent::GetRotZ(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
		return wData::TransformComponents[GO->componentLocations[0]].rotZ;
	}
}

void entityManager::gameObjects::transformComponent::ScaleVec(entitySystem::gameObject* GO, glm::vec3 &scale)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
		wData::TransformComponents[GO->componentLocations[0]].scale = scale;
	}
}
void entityManager::gameObjects::transformComponent::ScaleXYZ(entitySystem::gameObject* GO, float x, float y, float z)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
		wData::TransformComponents[GO->componentLocations[0]].scale.x = x;
		wData::TransformComponents[GO->componentLocations[0]].scale.y = y;
		wData::TransformComponents[GO->componentLocations[0]].scale.z = z;
	}
}
void entityManager::gameObjects::transformComponent::ScaleX(entitySystem::gameObject* GO,float x)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
		wData::TransformComponents[GO->componentLocations[0]].scale.x = x;
	}
}
void entityManager::gameObjects::transformComponent::ScaleY(entitySystem::gameObject* GO,float y)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
		wData::TransformComponents[GO->componentLocations[0]].scale.y = y;
	}
}
void entityManager::gameObjects::transformComponent::ScaleZ(entitySystem::gameObject* GO,float z)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
		wData::TransformComponents[GO->componentLocations[0]].scale.z = z;
	}
}

glm::vec3 entityManager::gameObjects::transformComponent::GetScaleVec(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
		return wData::TransformComponents[GO->componentLocations[0]].scale;
	}
}
float entityManager::gameObjects::transformComponent::GetScaleX(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
		return wData::TransformComponents[GO->componentLocations[0]].scale.x;
	}
}
float entityManager::gameObjects::transformComponent::GetScaleY(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
		return wData::TransformComponents[GO->componentLocations[0]].scale.y;
	}
}
float entityManager::gameObjects::transformComponent::GoGetScaleZ(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
		return wData::TransformComponents[GO->componentLocations[0]].scale.z;
	}
}

void entityManager::gameObjects::meshComponent::SetDiffuseName(entitySystem::gameObject* GO, std::string fileName)
{
	if((GO->gameObjectID & MESH) == MESH){
		wData::MeshComponents[GO->componentLocations[1]].diffuseName = fileName;
	}
}
std::string entityManager::gameObjects::meshComponent::GetTextureName(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & MESH) == MESH){
		return wData::MeshComponents[GO->componentLocations[1]].diffuseName;
	}
}

void entityManager::gameObjects::meshComponent::SetBlue(entitySystem::gameObject* GO, float blue)
{
	if((GO->gameObjectID & MESH) == MESH){
		wData::MeshComponents[GO->componentLocations[1]].BLUE = blue;
	}
}
void entityManager::gameObjects::meshComponent::SetRed(entitySystem::gameObject* GO, float red)
{
	if((GO->gameObjectID & MESH) == MESH){
		wData::MeshComponents[GO->componentLocations[1]].RED = red;
	}
}
void entityManager::gameObjects::meshComponent::SetGreen(entitySystem::gameObject* GO, float green)
{
	if((GO->gameObjectID & MESH) == MESH){
		wData::MeshComponents[GO->componentLocations[1]].GREEN = green;
	}
}
void entityManager::gameObjects::meshComponent::SetAlpha(entitySystem::gameObject* GO, float alpha)
{
	if((GO->gameObjectID & MESH) == MESH){
		wData::MeshComponents[GO->componentLocations[1]].ALPHA = alpha;
	}
}

void entityManager::gameObjects::meshComponent::Visible(entitySystem::gameObject* GO, bool isVisible)
{
	if((GO->gameObjectID & MESH) == MESH){
		wData::MeshComponents[GO->componentLocations[1]].ALPHA = 1.0f;
	}
}
void entityManager::gameObjects::meshComponent::Invisible(entitySystem::gameObject* GO, bool isInvisible)
{
	if((GO->gameObjectID & MESH) == MESH){
		wData::MeshComponents[GO->componentLocations[1]].ALPHA = 0.0f;
	}
}

float entityManager::gameObjects::meshComponent::GetRed(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & MESH) == MESH){
		return wData::MeshComponents[GO->componentLocations[1]].RED;
	}
}
float entityManager::gameObjects::meshComponent::GetGreen(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & MESH) == MESH){
		return wData::MeshComponents[GO->componentLocations[1]].GREEN;
	}
}
float entityManager::gameObjects::meshComponent::GetBlue(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & MESH) == MESH){
		return wData::MeshComponents[GO->componentLocations[1]].BLUE;
	}
}
float entityManager::gameObjects::meshComponent::GetAlpha(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & MESH) == MESH){
		return wData::MeshComponents[GO->componentLocations[1]].ALPHA;
	}
}

void entityManager::gameObjects::meshComponent::LoadDiffiuse(entitySystem::gameObject* GO, std::string diffuseName)
{
	if((GO->gameObjectID & MESH) == MESH){
		 Bitmap bmp = Bitmap::bitmapFromFile(diffuseName);
		 bmp.flipVertically();
		 wData::MeshComponents[GO->componentLocations[1]].pTexture = new Texture(bmp);
	}
}


void entityManager::gameObjects::cameraComponent::PitchCamera(entitySystem::gameObject* GO, float angle)
{
	if((GO->gameObjectID & CAMERA) == CAMERA){
        if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
            wData::TransformComponents[GO->componentLocations[0]].rotX = angle;
        }
	}
}
void entityManager::gameObjects::cameraComponent::RollCamera(entitySystem::gameObject* GO, float angle)
{
	if((GO->gameObjectID & CAMERA) == CAMERA){
		if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
            wData::TransformComponents[GO->componentLocations[0]].rotZ = angle;
        }
	}
}
void entityManager::gameObjects::cameraComponent::YawCamera(entitySystem::gameObject* GO, float angle)
{
	if((GO->gameObjectID & CAMERA) == CAMERA){
        if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
            wData::TransformComponents[GO->componentLocations[0]].rotY = angle;
        }
	}
}
void entityManager::gameObjects::cameraComponent::SetCamPitchYawRoll(entitySystem::gameObject* GO, float pitch,float yaw,float roll)
{
	if((GO->gameObjectID & CAMERA) == CAMERA){
        if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
            wData::TransformComponents[GO->componentLocations[0]].rotX = pitch;
            wData::TransformComponents[GO->componentLocations[0]].rotY = yaw;
            wData::TransformComponents[GO->componentLocations[0]].rotZ = roll;
        }
	}
}
void entityManager::gameObjects::cameraComponent::OffSetCamPitchRoll(entitySystem::gameObject* GO, float pitch, float yaw, float roll)
{
	if((GO->gameObjectID & CAMERA) == CAMERA){
        if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
            wData::TransformComponents[GO->componentLocations[0]].rotX += pitch;
            wData::TransformComponents[GO->componentLocations[0]].rotY += yaw;
            wData::TransformComponents[GO->componentLocations[0]].rotZ += roll;
        }
	}
}

float entityManager::gameObjects::cameraComponent::GetCameraPitch(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & CAMERA) == CAMERA){
		return wData::CameraComponents[GO->componentLocations[3]].pitch;
	}
}
float entityManager::gameObjects::cameraComponent::GetCameraRoll(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & CAMERA) == CAMERA){
		return wData::CameraComponents[GO->componentLocations[3]].roll;
	}
}
float entityManager::gameObjects::cameraComponent::GetCameraYaw(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & CAMERA) == CAMERA){
		return wData::CameraComponents[GO->componentLocations[3]].yaw;
	}
}


float entityManager::gameObjects::cameraComponent::GetCamNearPlane(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & CAMERA) == CAMERA){
		return wData::CameraComponents[GO->componentLocations[3]].nearPlane;
	}
}
float entityManager::gameObjects::cameraComponent::GetCamFarPlane(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & CAMERA) == CAMERA){
		return wData::CameraComponents[GO->componentLocations[3]].farPlane;
	}
}

glm::mat4 entityManager::gameObjects::cameraComponent::Matrix(entitySystem::gameObject *GO)
{
    if((GO->gameObjectID & CAMERA) == CAMERA){
        glm::mat4 camera =  glm::perspective(45.0f, wData::CameraComponents[GO->componentLocations[3]].aspectRatio,
                         wData::CameraComponents[GO->componentLocations[3]].nearPlane,
                         wData::CameraComponents[GO->componentLocations[3]].farPlane);
        camera *= CamOrientation(GO);
        camera = glm::translate(camera, -wData::TransformComponents[GO->componentLocations[0]].positon);
        return camera;
    }
}

glm::mat4 entityManager::gameObjects::cameraComponent::CamOrientation(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & CAMERA) == CAMERA){
         if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
             glm::mat4 orientation;

             orientation = glm::rotate(orientation, wData::TransformComponents[GO->componentLocations[0]].rotX, glm::vec3(1,0,0));
             orientation = glm::rotate(orientation, wData::TransformComponents[GO->componentLocations[0]].rotY,   glm::vec3(0,1,0));
             orientation = glm::rotate(orientation, wData::TransformComponents[GO->componentLocations[0]].rotZ,  glm::vec3(0,0,1));
             return orientation;
         }
	}
    //Output an error here
    return glm::mat4(1.0f);//if we get to this control point, there was an error
}
glm::vec3 entityManager::gameObjects::cameraComponent::GetForward(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & CAMERA) == CAMERA){
		glm::vec4 forward = glm::inverse(CamOrientation(GO))  * glm::vec4(0,0,-1,1);
		return glm::vec3(forward);
	}
}
glm::vec3 entityManager::gameObjects::cameraComponent::GetUp(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & CAMERA) == CAMERA){
		glm::vec4 up = glm::inverse(CamOrientation(GO))  * glm::vec4(0,1,0,1);
		return glm::vec3(up);
	}
}
glm::vec3 entityManager::gameObjects::cameraComponent::GetRight(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & CAMERA) == CAMERA){
		glm::vec4 right = glm::inverse(CamOrientation(GO)) * glm::vec4(1,0,0,1);
		return glm::vec3(right);
	}
}

void entityManager::gameObjects::cameraComponent::SetAspectRatio(entitySystem::gameObject* GO, float amount)
{
	if((GO->gameObjectID & CAMERA) == CAMERA){
		wData::CameraComponents[GO->componentLocations[3]].aspectRatio = amount;
	}
}
float entityManager::gameObjects::cameraComponent::GetAspectRatio(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & CAMERA) == CAMERA){
		return wData::CameraComponents[GO->componentLocations[3]].aspectRatio;
	}
}

glm::mat4 entityManager::gameObjects::cameraComponent::UpdateProjection(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & CAMERA) == CAMERA){
		return glm::perspective(45.0f, wData::CameraComponents[GO->componentLocations[3]].aspectRatio,
							wData::CameraComponents[GO->componentLocations[3]].nearPlane,
							wData::CameraComponents[GO->componentLocations[3]].farPlane);
	}
}
glm::mat4 entityManager::gameObjects::cameraComponent::UpdateView(entitySystem::gameObject* GO)
{
	if((GO->gameObjectID & CAMERA) == CAMERA){
        if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
            return CamOrientation(GO) * glm::translate(glm::mat4(), -wData::TransformComponents[GO->componentLocations[0]].positon);
        }
	}
}
void entityManager::gameObjects::physicsComponent::SetObjectMass(entitySystem::gameObject* GO,float mass)
{
    if((GO->gameObjectID & PHYSICS) == PHYSICS){
        wData::PhysicsComponents[GO->componentLocations[2]].mass = mass;
    }
}
float entityManager::gameObjects::physicsComponent::GetObjectMass(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & PHYSICS) == PHYSICS){
        return wData::PhysicsComponents[GO->componentLocations[2]].mass;
    }
}
void entityManager::gameObjects::physicsComponent::SetCollisionShapeScale(entitySystem::gameObject* GO, float x, float y, float z)
{
    if((GO->gameObjectID & PHYSICS) == PHYSICS){
    }
}
void entityManager::gameObjects::lightComponent::SetLightColourVec(entitySystem::gameObject* GO, glm::vec4 &col)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        wData::LightComponents[GO->componentLocations[4]].colour = col;
    }
}
void entityManager::gameObjects::lightComponent::SetLightColourRGBA(entitySystem::gameObject* GO, float r, float g, float b, float a)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        wData::LightComponents[GO->componentLocations[4]].colour.x = r;
        wData::LightComponents[GO->componentLocations[4]].colour.y = g;
        wData::LightComponents[GO->componentLocations[4]].colour.z = b;
        wData::LightComponents[GO->componentLocations[4]].colour.w = a;
    }
}
void entityManager::gameObjects::lightComponent::SetLightColourR(entitySystem::gameObject* GO, float r)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        wData::LightComponents[GO->componentLocations[4]].colour.x = r;
    }
}
void entityManager::gameObjects::lightComponent::SetLightColourG(entitySystem::gameObject* GO, float g)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        wData::LightComponents[GO->componentLocations[4]].colour.y = g;
    }
}
void entityManager::gameObjects::lightComponent::SetLightColourB(entitySystem::gameObject* GO, float b)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        wData::LightComponents[GO->componentLocations[4]].colour.z = b;
    }
}
void entityManager::gameObjects::lightComponent::SetLightColourA(entitySystem::gameObject* GO, float a)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        wData::LightComponents[GO->componentLocations[4]].colour.w = a;
    }
}

void entityManager::gameObjects::lightComponent::SetLightShininess(entitySystem::gameObject *GO, float shininess)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        wData::LightComponents[GO->componentLocations[4]].shininess = shininess;
    }
}

float entityManager::gameObjects::lightComponent::GetLightColourR(entitySystem::gameObject* GO)
{
    return wData::LightComponents[GO->componentLocations[4]].colour.x;
}
float entityManager::gameObjects::lightComponent::GetLightColourG(entitySystem::gameObject* GO)
{
    return wData::LightComponents[GO->componentLocations[4]].colour.y;
}
float entityManager::gameObjects::lightComponent::GetLightColourB(entitySystem::gameObject* GO)
{
    return wData::LightComponents[GO->componentLocations[4]].colour.z;
}

float entityManager::gameObjects::lightComponent::GetLightColourA(entitySystem::gameObject* GO)
{
    return wData::LightComponents[GO->componentLocations[4]].colour.w;
}

void entityManager::gameObjects::lightComponent::SetLightRadius(entitySystem::gameObject* GO, float rad)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        wData::LightComponents[GO->componentLocations[4]].radius = rad;
    }
}
float entityManager::gameObjects::lightComponent::GetLightRadius(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        return wData::LightComponents[GO->componentLocations[4]].radius;
    }
}
glm::vec3 entityManager::gameObjects::lightComponent::GetLightKa(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        return wData::LightComponents[GO->componentLocations[4]].Ka;
    }
}
glm::vec3 entityManager::gameObjects::lightComponent::GetLightKd(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        return wData::LightComponents[GO->componentLocations[4]].Kd;
    }
}
glm::vec3 entityManager::gameObjects::lightComponent::GetLightKs(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        return wData::LightComponents[GO->componentLocations[4]].Ks;
    }
}

glm::vec3 entityManager::gameObjects::lightComponent::GetLightLa(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        return wData::LightComponents[GO->componentLocations[4]].La;
    }
}
glm::vec3 entityManager::gameObjects::lightComponent::GetLightLd(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        return wData::LightComponents[GO->componentLocations[4]].Ld;
    }
}
glm::vec3 entityManager::gameObjects::lightComponent::GetLightLs(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        return wData::LightComponents[GO->componentLocations[4]].Ls;
    }
}

void entityManager::gameObjects::lightComponent::SetLightKa(entitySystem::gameObject* GO, float a, float b, float c)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        wData::LightComponents[GO->componentLocations[4]].Ka.x = a;
        wData::LightComponents[GO->componentLocations[4]].Ka.y = b;
        wData::LightComponents[GO->componentLocations[4]].Ka.z = c;
    }
}

void entityManager::gameObjects::lightComponent::SetLightKd(entitySystem::gameObject* GO, float a, float b, float c)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        wData::LightComponents[GO->componentLocations[4]].Kd.x = a;
        wData::LightComponents[GO->componentLocations[4]].Kd.y = b;
        wData::LightComponents[GO->componentLocations[4]].Kd.z = c;
    }
}

void entityManager::gameObjects::lightComponent::SetLightKs(entitySystem::gameObject* GO, float a, float b, float c)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        wData::LightComponents[GO->componentLocations[4]].Ks.x = a;
        wData::LightComponents[GO->componentLocations[4]].Ks.y = b;
        wData::LightComponents[GO->componentLocations[4]].Ks.z = c;
    }
}

void entityManager::gameObjects::lightComponent::SetLightLa(entitySystem::gameObject* GO, float a , float b, float c)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        wData::LightComponents[GO->componentLocations[4]].La.x = a;
        wData::LightComponents[GO->componentLocations[4]].La.y = b;
        wData::LightComponents[GO->componentLocations[4]].La.z = c;
    }
}

void entityManager::gameObjects::lightComponent::SetLightLd(entitySystem::gameObject* GO, float a , float b, float c)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        wData::LightComponents[GO->componentLocations[4]].Ld.x = a;
        wData::LightComponents[GO->componentLocations[4]].Ld.y = b;
        wData::LightComponents[GO->componentLocations[4]].Ld.z = c;
    }
}

void entityManager::gameObjects::lightComponent::SetLightLs(entitySystem::gameObject* GO, float a , float b, float c)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        wData::LightComponents[GO->componentLocations[4]].Ls.x = a;
        wData::LightComponents[GO->componentLocations[4]].Ls.y = b;
        wData::LightComponents[GO->componentLocations[4]].Ls.z = c;
    }
}


float entityManager::gameObjects::lightComponent::GetLightKaA(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        return wData::LightComponents[GO->componentLocations[4]].Ka.x;
    }
}
float entityManager::gameObjects::lightComponent::GetLightKdA(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        return wData::LightComponents[GO->componentLocations[4]].Kd.x;
    }
}
float entityManager::gameObjects::lightComponent::GetLightKsA(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        return wData::LightComponents[GO->componentLocations[4]].Ks.x;
    }
}

float entityManager::gameObjects::lightComponent::GetLightKaB(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        return wData::LightComponents[GO->componentLocations[4]].Ka.y;
    }
}
float entityManager::gameObjects::lightComponent::GetLightKdB(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        return wData::LightComponents[GO->componentLocations[4]].Kd.y;
    }
}
float entityManager::gameObjects::lightComponent::GetLightKsB(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        return wData::LightComponents[GO->componentLocations[4]].Ks.y;
    }
}

float entityManager::gameObjects::lightComponent::GetLightKaC(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        return wData::LightComponents[GO->componentLocations[4]].Ka.z;
    }
}
float entityManager::gameObjects::lightComponent::GetLightKdC(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        return wData::LightComponents[GO->componentLocations[4]].Kd.z;
    }
}
float entityManager::gameObjects::lightComponent::GetLightKsC(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        return wData::LightComponents[GO->componentLocations[4]].Ks.z;
    }
}

float entityManager::gameObjects::lightComponent::GetLightLaA(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        return wData::LightComponents[GO->componentLocations[4]].La.x;
    }
}
float entityManager::gameObjects::lightComponent::GetLightLdA(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        return wData::LightComponents[GO->componentLocations[4]].Ld.x;
    }
}
float entityManager::gameObjects::lightComponent::GetLightLsA(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        return wData::LightComponents[GO->componentLocations[4]].Ls.x;
    }
}

float entityManager::gameObjects::lightComponent::GetLightLaB(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        return wData::LightComponents[GO->componentLocations[4]].La.y;
    }
}
float entityManager::gameObjects::lightComponent::GetLightLdB(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        return wData::LightComponents[GO->componentLocations[4]].Ld.y;
    }
}
float entityManager::gameObjects::lightComponent::GetLightLsB(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        return wData::LightComponents[GO->componentLocations[4]].Ls.y;
    }
}

float entityManager::gameObjects::lightComponent::GetLightLaC(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        return wData::LightComponents[GO->componentLocations[4]].La.z;
    }
}
float entityManager::gameObjects::lightComponent::GetLightLdC(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        return wData::LightComponents[GO->componentLocations[4]].Ld.z;
    }
}
float entityManager::gameObjects::lightComponent::GetLightLsC(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        return wData::LightComponents[GO->componentLocations[4]].Ls.z;
    }
}

float entityManager::gameObjects::lightComponent::GetLightShininess(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        return wData::LightComponents[GO->componentLocations[4]].shininess;
    }
}

glm::vec3 entityManager::gameObjects::lightComponent::GetLightPosition(entitySystem::gameObject* GO)
{
    if((GO->gameObjectID & LIGHT) == LIGHT){
        if((GO->gameObjectID & TRANSFORM) == TRANSFORM){
            return wData::TransformComponents[GO->componentLocations[0]].positon;
        }
    }
}

