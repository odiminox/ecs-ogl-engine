#pragma once
#include <vector>
#include "EntitySystem.h"
#include "DebugDraw.h"
#include "NotificationHandler.h"
#include "GLSLShader.h"
#include "Defines.h"

struct wData {
    static std::vector<entitySystem::gameObject> Objects;//Contains all of the objects in the world that we want to process
    static std::vector<entitySystem::transformComponent> TransformComponents;
    static std::vector<entitySystem::meshComponent> MeshComponents;
    static std::vector<entitySystem::cameraComponent> CameraComponents;
    static std::vector<entitySystem::physicsComponent> PhysicsComponents;
    static std::vector<entitySystem::lightComponent> LightComponents;
    static std::vector<int> Rigidbodies;

    static NotificationHandler* WorldNotificationHandler;
};

struct eData
{
    eData()
    {
        tCounter = 0;
        mCounter = 0;
        pCounter = 0;
        cCounter = 0;
        lCounter = 0;
    }
    static int tCounter;
    static int mCounter;
    static int pCounter;
    static int cCounter;
    static int lCounter;

    static int wCounter;

    static GLSLShader *shaderLoader;
    static Mat4 view;
    static Mat4 projection;

};

struct pData
{
    pData()
    {

    }
};

