#pragma once

#include "worldData.h"
#include "EntityProcessing.h"
#include <iostream>

namespace entityManager
{
    //Also need to create an object that is not automatically added to the world object list.

	void createGameObjectByTag(int tag);
	void createGameObjectByName(std::string name);

	entitySystem::gameObject* getGameObjectByTag(int tag);
	//entitySystem::gameObject* getGameObjectByName(std::string name);

	void addTransformComponent(entitySystem::gameObject* );
	void addMeshComponent(entitySystem::gameObject* );
	void addPhysicsComponent(entitySystem::gameObject* );
	void addCameraComponent(entitySystem::gameObject* );
    void addLightComponent(entitySystem::gameObject* );

	void removeTransformComponent(entitySystem::gameObject* );
	void removePhysicsComponent(entitySystem::gameObject* );
	void removeCameraComponent(entitySystem::gameObject* );
	void removeMeshComponent(entitySystem::gameObject* );
    void removeLightComponent(entitySystem::gameObject* );

	void addChildToGameObject(int parent, int child);
	void removeChildFromGameObject(entitySystem::gameObject* parent, entitySystem::gameObject* child);

    int getGameObjectWorldPosition(entitySystem::gameObject* );
    void setGameObjectParentWorldPosition(int childWorldPos, int parentWorldPos);

    namespace editorObjects
    {
        namespace buttonComponent
        {

        }
    }

	namespace gameObjects
	{
		namespace transformComponent
		{
			void OffsetVec(entitySystem::gameObject* GO, glm::vec3 &offset);
			void OffsetXYZ(entitySystem::gameObject* GO,float x, float y, float z);
			void OffsetX(entitySystem::gameObject* GO,float x);
			void OffsetY(entitySystem::gameObject* GO,float y);
			void OffsetZ(entitySystem::gameObject* GO,float z);

			void TranslateVec(entitySystem::gameObject* GO, glm::vec3 &pos);
			void TranslateXYZ(entitySystem::gameObject* GO, float x, float y, float z);
			void TranslateX(entitySystem::gameObject* GO,float x);
			void TranslateY(entitySystem::gameObject* GO,float y);
			void TranslateZ(entitySystem::gameObject* GO,float z);

			glm::vec3 GetPosVec(entitySystem::gameObject* GO);
			float GetPosX(entitySystem::gameObject* GO);
			float GetPosY(entitySystem::gameObject* GO);
			float GetPosZ(entitySystem::gameObject* GO);

			void RotateX(entitySystem::gameObject* GO,float amount);
			void RotateY(entitySystem::gameObject* GO,float amount);
			void RotateZ(entitySystem::gameObject* GO,float amount);

			float GetRotX(entitySystem::gameObject* GO);
			float GetRotY(entitySystem::gameObject* GO);
			float GetRotZ(entitySystem::gameObject* GO);

			void ScaleVec(entitySystem::gameObject* GO, glm::vec3 &scale);
			void ScaleXYZ(entitySystem::gameObject* GO, float x, float y, float z);
			void ScaleX(entitySystem::gameObject* GO,float x);
			void ScaleY(entitySystem::gameObject* GO,float y);
			void ScaleZ(entitySystem::gameObject* GO,float z);

			glm::vec3 GetScaleVec(entitySystem::gameObject* GO);
			float GetScaleX(entitySystem::gameObject* GO);
			float GetScaleY(entitySystem::gameObject* GO);
			float GoGetScaleZ(entitySystem::gameObject* );

			void SetMV();
		}

		namespace meshComponent
		{
			void SetDiffuseName(entitySystem::gameObject* GO, std::string fileName);
			std::string GetTextureName(entitySystem::gameObject* GO);

			void SetBlue(entitySystem::gameObject* GO, float blue);
			void SetRed(entitySystem::gameObject* GO, float red);
			void SetGreen(entitySystem::gameObject* GO, float green);
			void SetAlpha(entitySystem::gameObject* GO, float alpha);

			void Visible(entitySystem::gameObject* GO, bool isVisible);
			void Invisible(entitySystem::gameObject* GO, bool isInvisible);

			float GetRed(entitySystem::gameObject* GO);
			float GetGreen(entitySystem::gameObject* GO);
			float GetBlue(entitySystem::gameObject* GO);
			float GetAlpha(entitySystem::gameObject* GO);

            bool LoadMesh(entitySystem::gameObject* GO, std::string meshName);

			void LoadDiffiuse(entitySystem::gameObject* GO, std::string diffuseName);
		}

		namespace cameraComponent
		{
			void PitchCamera(entitySystem::gameObject* GO, float angle);
			void RollCamera(entitySystem::gameObject* GO, float angle);
			void YawCamera(entitySystem::gameObject* GO, float angle);
			void SetCamPitchYawRoll(entitySystem::gameObject* GO, float pitch,float yaw,float roll);
			void OffSetCamPitchRoll(entitySystem::gameObject* GO, float pitch, float yaw, float roll);

			float GetCameraPitch(entitySystem::gameObject* GO);
			float GetCameraRoll(entitySystem::gameObject* GO);
			float GetCameraYaw(entitySystem::gameObject* GO);

			float GetCamNearPlane(entitySystem::gameObject* GO);
			float GetCamFarPlane(entitySystem::gameObject* GO);

			glm::mat4 CamOrientation(entitySystem::gameObject* GO);
			glm::vec3 GetForward(entitySystem::gameObject* GO);
			glm::vec3 GetUp(entitySystem::gameObject* GO);
			glm::vec3 GetRight(entitySystem::gameObject* GO);

			void SetAspectRatio(entitySystem::gameObject* GO, float amount);
			float GetAspectRatio(entitySystem::gameObject* GO);

			glm::mat4 UpdateProjection(entitySystem::gameObject* GO);
			glm::mat4 UpdateView(entitySystem::gameObject* GO);

            glm::mat4 Matrix(entitySystem::gameObject* GO);

		}

		namespace physicsComponent
		{
            void SetObjectMass(entitySystem::gameObject* GO, float mass);
            float GetObjectMass(entitySystem::gameObject* GO);
            void SetCollisionShapeScale(entitySystem::gameObject* GO, float x, float y, float z);
		}

        namespace lightComponent
        {
            void SetLightColourVec(entitySystem::gameObject* GO, glm::vec4 &col);
            void SetLightColourRGBA(entitySystem::gameObject* GO, float r, float g, float b, float a);
            void SetLightColourR(entitySystem::gameObject* GO, float r);
            void SetLightColourG(entitySystem::gameObject* GO, float g);
            void SetLightColourB(entitySystem::gameObject* GO, float b);
            void SetLightColourA(entitySystem::gameObject* GO, float a);

            void SetLightKa(entitySystem::gameObject* GO, float a, float b, float c);
            void SetLightKd(entitySystem::gameObject* GO, float a, float b, float c);
            void SetLightKs(entitySystem::gameObject* GO, float a, float b, float c);

            void SetLightLa(entitySystem::gameObject* GO, float a, float b, float c);
            void SetLightLd(entitySystem::gameObject* GO, float a , float b, float c);
            void SetLightLs(entitySystem::gameObject* GO, float a, float b, float c);

            void SetLightShininess(entitySystem::gameObject* GO, float shininess);

            glm::vec3 GetLightKa(entitySystem::gameObject* GO);
            glm::vec3 GetLightKd(entitySystem::gameObject* GO);
            glm::vec3 GetLightKs(entitySystem::gameObject* GO);

            glm::vec3 GetLightLa(entitySystem::gameObject* GO);
            glm::vec3 GetLightLd(entitySystem::gameObject* GO);
            glm::vec3 GetLightLs(entitySystem::gameObject* GO);

            float GetLightShininess(entitySystem::gameObject* );

            glm::vec3 GetLightPosition(entitySystem::gameObject* GO);

            float GetLightKaA(entitySystem::gameObject* GO);
            float GetLightKaB(entitySystem::gameObject* GO);
            float GetLightKaC(entitySystem::gameObject* GO);
            float GetLightKdA(entitySystem::gameObject* GO);
            float GetLightKdB(entitySystem::gameObject* GO);
            float GetLightKdC(entitySystem::gameObject* GO);
            float GetLightKsA(entitySystem::gameObject* GO);
            float GetLightKsB(entitySystem::gameObject* GO);
            float GetLightKsC(entitySystem::gameObject* GO);

            float GetLightLaA(entitySystem::gameObject* GO);
            float GetLightLaB(entitySystem::gameObject* GO);
            float GetLightLaC(entitySystem::gameObject* GO);
            float GetLightLdA(entitySystem::gameObject* GO);
            float GetLightLdB(entitySystem::gameObject* GO);
            float GetLightLdC(entitySystem::gameObject* GO);
            float GetLightLsA(entitySystem::gameObject* GO);
            float GetLightLsB(entitySystem::gameObject* GO);
            float GetLightLsC(entitySystem::gameObject* GO);


            float GetLightColourR(entitySystem::gameObject* GO);
            float GetLightColourG(entitySystem::gameObject* GO);
            float GetLightColourB(entitySystem::gameObject* GO);
            float GetLightColourA(entitySystem::gameObject* GO);

            void SetLightRadius(entitySystem::gameObject* GO, float rad);
            float GetLightRadius(entitySystem::gameObject* GO);
        }
	}
}
