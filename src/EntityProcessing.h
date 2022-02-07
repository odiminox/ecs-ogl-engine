#ifndef ENTITYPROCESSING_H_
#define ENTITYPROCESSING_H_

//#include "Source\memoryManager.h"
#include "Bitmap.h"
#include "Texture.h"
#include "GLSLShader.h"
#include "EntityManager.h"

namespace entityProcessing
{
    void cleanupObjects();

    void updateRotations();
    void updateTranslations();
    void updateScaling();
    void updatePhysics(float delta);

    void loadTexture(std::string fileName, GLuint *object);
    void loadMeshdata(std::string fileName);

    void drawLights(entitySystem::gameObject *GO, GLSLShader *shader);

    void draw3DMVM(entitySystem::gameObject *GO,GLSLShader *shader);
    void draw2DMVM(entitySystem::gameObject *GO,GLSLShader *shader);

    void draw3DMeshes(entitySystem::gameObject *GO,GLSLShader *shader);
    void draw2DMeshes(entitySystem::gameObject *GO,GLSLShader *shader);

    void loadAllTextures();

    void initMeshes3D(entitySystem::gameObject *GO,GLSLShader *shader);
    void initMeshed2D(entitySystem::gameObject *GO,GLSLShader *shader);
    void initMeshComponents(GLSLShader *shader3D, GLSLShader *shader2D);
    void initCameraComponents();
    void initPhysicsComponents();

    void initLive3DObjects();
    void initLive2DObjects();

    void drawAllObjects(GLSLShader *shader3D, GLSLShader *shader2D);
    void updateCameraComponents();

    void updateSceneGraph(int objectNum);

    void runCoreUpdate();
    void runCoreDraw(GLSLShader *shader3D, GLSLShader *shader2D);

    void updateMeshComponents();

    void updatePhysicsComponents(float delta);
}

#endif

