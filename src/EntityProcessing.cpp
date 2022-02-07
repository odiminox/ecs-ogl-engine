#include "EntityProcessing.h"
#include "memoryManager.h"

void entityProcessing::cleanupObjects()
{
	//safeDelete(textureLoader);
}


void entityProcessing::updateRotations()
{

}
void entityProcessing::updateTranslations()
{
}
void entityProcessing::updateScaling(){

}


//Create method to clean-up textures at end, as currently they create a memory leak
void entityProcessing::loadTexture(std::string fileName, GLuint *object)
{
	Texture* textureLoader;
	Bitmap bmp = Bitmap::bitmapFromFile(fileName);
	bmp.flipVertically();
	textureLoader = new Texture(bmp);
	//I don't know if this will work
	object = &textureLoader->_object;
	//delete textureLoader;
	//textureLoader = NULL;
//		safeDelete(textureLoader);
}
void entityProcessing::loadMeshdata(std::string fileName)
{
	//method for loading mesh data here
	//Also need to expand functionality to support skeletal animations
}


	static const entityData::Vertex testVerts[] =
	{
		// Front
		{{-0.5, -0.5, 0.5}, {0.0f, 0.0f, 1.0f}, {1, 0, 0, 1}, {0, 0}},
		{{0.5, -0.5, 0.5}, {0.0f, 0.0f, 1.0f}, {0, 1, 0, 1}, {1, 0}},
		{{0.5, 0.5, 0.5}, {0.0f, 0.0f, 1.0f},{0, 0, 1, 1}, {1, 1}},
		{{-0.5, 0.5, 0.5},{0.0f, 0.0f, 1.0f}, {0, 0, 0, 1}, {0, 1}}
	};

static const GLubyte testIndices[] =
{
	0,1,2,0,2,3
};

void entityProcessing::drawLights(entitySystem::gameObject *GO, GLSLShader *shader)
{
    glm::vec4 tempPos = glm::vec4(1.0f,1.0f,1.0f,1.0f);
    glm::vec3 tempEntPos = entityManager::gameObjects::lightComponent::GetLightPosition(GO);
    tempPos.x = tempEntPos.x;
    tempPos.y = tempEntPos.y;
    tempPos.z = tempEntPos.z;
    tempPos.w = 1.0f;

    shader->setUniform("lightPosition", tempPos);

    shader->setUniform("Ka", entityManager::gameObjects::lightComponent::GetLightKa(GO));
    shader->setUniform("Kd", entityManager::gameObjects::lightComponent::GetLightKd(GO));
    shader->setUniform("Ks", entityManager::gameObjects::lightComponent::GetLightKs(GO));

    shader->setUniform("La", entityManager::gameObjects::lightComponent::GetLightLa(GO));
    shader->setUniform("Ld", entityManager::gameObjects::lightComponent::GetLightLd(GO));
    shader->setUniform("Ls", entityManager::gameObjects::lightComponent::GetLightLs(GO));

    shader->setUniform("shininess", entityManager::gameObjects::lightComponent::GetLightShininess(GO));
}

void entityProcessing::initMeshComponents(GLSLShader *shader3D, GLSLShader *shader2D)
{
	for(int i = 0; i < wData::Objects.size(); ++i){

        if(wData::TransformComponents[wData::Objects[i].componentLocations[0]].scale.z != 0.0f){

            initMeshes3D(&wData::Objects[i], shader3D);

        }else if(wData::TransformComponents[wData::Objects[i].componentLocations[0]].scale.z == 0.0f){

            initMeshed2D(&wData::Objects[i], shader2D);
        }
	}
}

void entityProcessing::loadAllTextures()
{
	for(int i = 0; i < wData::MeshComponents.size(); ++i){
		loadTexture(wData::MeshComponents[i].diffuseName, &wData::MeshComponents[i]._texture);//Init the texture data first
	}
}

void entityProcessing::drawAllObjects(GLSLShader *shader3D, GLSLShader *shader2D)
{
	for(int i = 0; i <wData::Objects.size(); ++i){

		if((wData::Objects[i].gameObjectID & 64) == 64)
		{
            //Check the z component of the object to see if it is 2D or 3D, 2D objects will always have a Z component of 0
            if(wData::TransformComponents[wData::Objects[i].componentLocations[0]].scale.z != 0.0f){

                //Draw 3D objects
                shader3D->bind();

                draw3DMVM(&wData::Objects[i], shader3D);
                draw3DMeshes(&wData::Objects[i], shader3D);

                shader3D->unbind();

            } else if(wData::TransformComponents[wData::Objects[i].componentLocations[0]].scale.z == 0.0f){

                //Draw 2D objects
                shader2D->bind();

                draw2DMVM(&wData::Objects[i], shader2D);
                draw2DMeshes(&wData::Objects[i], shader2D);

                shader2D->unbind();
            }
		}

        //Check to see if the object has a light component
        if((wData::Objects[i].gameObjectID & 8) == 8){
            shader3D->bind();
            drawLights(&wData::Objects[i], shader3D);
            shader3D->unbind();
        }

	}
}

void entityProcessing::initMeshes3D(entitySystem::gameObject *GO,GLSLShader *shader)
{
    if((GO->gameObjectID & 64) == 64){

		shader->loadAttribute(wData::MeshComponents[GO->componentLocations[1]]._positionSlot,"Position");
		shader->loadAttribute(wData::MeshComponents[GO->componentLocations[1]]._colorSlot,   "SourceColor");
		shader->loadAttribute(wData::MeshComponents[GO->componentLocations[1]]._texCoordSlot,"TexCoordIn");
		shader->loadAttribute(wData::MeshComponents[GO->componentLocations[1]]._NormalSlot,  "Normal");

		glGenBuffers(1, &wData::MeshComponents[GO->componentLocations[1]]._vertexBufferID);
		glGenBuffers(1, &wData::MeshComponents[GO->componentLocations[1]]._indexBufferID);

		glBindBuffer(GL_ARRAY_BUFFER, wData::MeshComponents[GO->componentLocations[1]]._vertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, wData::MeshComponents[GO->componentLocations[1]].Vertices.size() * sizeof(entityData::Vertex), wData::MeshComponents[GO->componentLocations[1]].Vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, wData::MeshComponents[GO->componentLocations[1]]._indexBufferID);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, MeshComponents[GO->componentLocations[1]].Indices.size() * sizeof(entityData::Index), MeshComponents[GO->componentLocations[1]].Indices.data(), GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(testIndices), testIndices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(wData::MeshComponents[GO->componentLocations[1]]._positionSlot); // Vertex Position
		glEnableVertexAttribArray(wData::MeshComponents[GO->componentLocations[1]]._colorSlot);    // Vertex Colour
		glEnableVertexAttribArray(wData::MeshComponents[GO->componentLocations[1]]._texCoordSlot); // Vertex Texture
		glEnableVertexAttribArray(wData::MeshComponents[GO->componentLocations[1]]._NormalSlot);   // Vertex Normal

		glVertexAttribPointer(wData::MeshComponents[GO->componentLocations[1]]._positionSlot, 3, GL_FLOAT, GL_FALSE, sizeof(entityData::Vertex) , 0);
		glVertexAttribPointer(wData::MeshComponents[GO->componentLocations[1]]._NormalSlot,   3, GL_FLOAT, GL_FALSE, sizeof(entityData::Vertex),(GLvoid*)(sizeof(float) * 3));
		glVertexAttribPointer(wData::MeshComponents[GO->componentLocations[1]]._colorSlot,    4, GL_FLOAT, GL_FALSE, sizeof(entityData::Vertex),(GLvoid*)(sizeof(float) * 6));
		glVertexAttribPointer(wData::MeshComponents[GO->componentLocations[1]]._texCoordSlot, 2, GL_FLOAT, GL_FALSE, sizeof(entityData::Vertex),(GLvoid*)(sizeof(float) * 10));
	}

}
void entityProcessing::initMeshed2D(entitySystem::gameObject *GO,GLSLShader *shader)
{
    if((GO->gameObjectID & 64) == 64){

		shader->loadAttribute(wData::MeshComponents[GO->componentLocations[1]]._positionSlot,"Position");
		shader->loadAttribute(wData::MeshComponents[GO->componentLocations[1]]._colorSlot,   "SourceColor");
		shader->loadAttribute(wData::MeshComponents[GO->componentLocations[1]]._texCoordSlot,"TexCoordIn");
        shader->loadAttribute(wData::MeshComponents[GO->componentLocations[1]]._NormalSlot,  "Normal");

		glGenBuffers(1, &wData::MeshComponents[GO->componentLocations[1]]._vertexBufferID);
		glGenBuffers(1, &wData::MeshComponents[GO->componentLocations[1]]._indexBufferID);

		glBindBuffer(GL_ARRAY_BUFFER, wData::MeshComponents[GO->componentLocations[1]]._vertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, wData::MeshComponents[GO->componentLocations[1]].Vertices.size() * sizeof(entityData::Vertex), wData::MeshComponents[GO->componentLocations[1]].Vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, wData::MeshComponents[GO->componentLocations[1]]._indexBufferID);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, MeshComponents[GO->componentLocations[1]].Indices.size() * sizeof(entityData::Index), MeshComponents[GO->componentLocations[1]].Indices.data(), GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(testIndices), testIndices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(wData::MeshComponents[GO->componentLocations[1]]._positionSlot); // Vertex Position
		glEnableVertexAttribArray(wData::MeshComponents[GO->componentLocations[1]]._colorSlot);    // Vertex Colour
		glEnableVertexAttribArray(wData::MeshComponents[GO->componentLocations[1]]._texCoordSlot); // Vertex Texture
		//glEnableVertexAttribArray(MeshComponents[GO->componentLocations[1]]._NormalSlot);   // Vertex Normal

		glVertexAttribPointer(wData::MeshComponents[GO->componentLocations[1]]._positionSlot, 3, GL_FLOAT, GL_FALSE, sizeof(entityData::Vertex) , 0);
		glVertexAttribPointer(wData::MeshComponents[GO->componentLocations[1]]._NormalSlot,   3, GL_FLOAT, GL_FALSE, sizeof(entityData::Vertex),(GLvoid*)(sizeof(float) * 3));
		glVertexAttribPointer(wData::MeshComponents[GO->componentLocations[1]]._colorSlot,    4, GL_FLOAT, GL_FALSE, sizeof(entityData::Vertex),(GLvoid*)(sizeof(float) * 6));
		glVertexAttribPointer(wData::MeshComponents[GO->componentLocations[1]]._texCoordSlot, 2, GL_FLOAT, GL_FALSE, sizeof(entityData::Vertex),(GLvoid*)(sizeof(float) * 10));
	}

}
void entityProcessing::draw3DMVM(entitySystem::gameObject *GO,GLSLShader *shader)
{
    if((GO->gameObjectID & 128) == 128)
	{
		wData::TransformComponents[GO->componentLocations[0]].mv = eData::view * wData::TransformComponents[GO->componentLocations[0]].model;
        shader->setUniform("modelMatrix",  eData::view * wData::TransformComponents[GO->componentLocations[0]].model);
        shader->setUniform("viewMatrix",  eData::view);
        shader->setUniform("projectionMatrix",  eData::projection);
		shader->setUniform("modelViewMatrix", wData::TransformComponents[GO->componentLocations[0]].mv);
		shader->setUniform("MVP",  eData::projection * wData::TransformComponents[GO->componentLocations[0]].mv);

        shader->setUniform("normalMatrix", glm::mat3(glm::vec3(wData::TransformComponents[GO->componentLocations[0]].mv[0]),glm::vec3(wData::TransformComponents[GO->componentLocations[0]].mv[1]),glm::vec3(wData::TransformComponents[GO->componentLocations[0]].mv[2]) ));
	}

    if((GO->gameObjectID & 8) == 8)
	{
        shader->setUniform("cameraPosition",  wData::TransformComponents[GO->componentLocations[0]].positon);
    }

}
void entityProcessing::draw2DMVM(entitySystem::gameObject *GO,GLSLShader *shader)
{
    if((GO->gameObjectID & 128) == 128)
	{
		wData::TransformComponents[GO->componentLocations[0]].mv = eData::view * wData::TransformComponents[GO->componentLocations[0]].model;
        shader->setUniform("modelMatrix",  eData::view * wData::TransformComponents[GO->componentLocations[0]].model);
        shader->setUniform("viewMatrix",  eData::view);
        shader->setUniform("projectionMatrix",  eData::projection);
		shader->setUniform("modelViewMatrix", wData::TransformComponents[GO->componentLocations[0]].mv);
		shader->setUniform("MVP",  eData::projection * wData::TransformComponents[GO->componentLocations[0]].mv);
	}

}
void entityProcessing::draw3DMeshes(entitySystem::gameObject *GO,GLSLShader *shader)
{
    if((GO->gameObjectID & 64) == 64){
        glBindBuffer(GL_ARRAY_BUFFER, wData::MeshComponents[GO->componentLocations[1]]._vertexBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, wData::MeshComponents[GO->componentLocations[1]]._indexBufferID);

        shader->setUniform("red",   entityManager::gameObjects::meshComponent::GetRed(GO));
        shader->setUniform("green", entityManager::gameObjects::meshComponent::GetGreen(GO));
        shader->setUniform("blue",  entityManager::gameObjects::meshComponent::GetBlue(GO));
        shader->setUniform("alpha", entityManager::gameObjects::meshComponent::GetAlpha(GO));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, wData::MeshComponents[GO->componentLocations[1]].pTexture->_object);

        shader->setUniform("Texture", 0);//Apply the uniform for this instance

        glDrawElements(GL_TRIANGLE_STRIP, sizeof(testIndices)/sizeof(testIndices[0]), GL_UNSIGNED_BYTE, 0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    }
}
//currently is same as above, but requires different shader and enables different uniform access in the future
void entityProcessing::draw2DMeshes(entitySystem::gameObject *GO,GLSLShader *shader)
{
    if((GO->gameObjectID & 64) == 64){
        glBindBuffer(GL_ARRAY_BUFFER, wData::MeshComponents[GO->componentLocations[1]]._vertexBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, wData::MeshComponents[GO->componentLocations[1]]._indexBufferID);

        shader->setUniform("red",   entityManager::gameObjects::meshComponent::GetRed(GO));
        shader->setUniform("green", entityManager::gameObjects::meshComponent::GetGreen(GO));
        shader->setUniform("blue",  entityManager::gameObjects::meshComponent::GetBlue(GO));
        shader->setUniform("alpha", entityManager::gameObjects::meshComponent::GetAlpha(GO));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, wData::MeshComponents[GO->componentLocations[1]].pTexture->_object);

        shader->setUniform("Texture", 0);//Apply the uniform for this instance

        glDrawElements(GL_TRIANGLE_STRIP, sizeof(testIndices)/sizeof(testIndices[0]), GL_UNSIGNED_BYTE, 0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    }
}

void entityProcessing::updateSceneGraph(int objectNum)
{
    if((wData::Objects[objectNum].gameObjectID & 128) == 128){

        wData::TransformComponents[objectNum].isDirty = false;

        //Assign the X, Y and Z inputs from the rotation the user entered to the quaternion

        /*
        //We assign the values over from the bullet physics quaternion, to the glm one
        wData::TransformComponents[objectNum].orientation.x = wData::TransformComponents[objectNum].qOrientation.x();
        wData::TransformComponents[objectNum].orientation.y = wData::TransformComponents[objectNum].qOrientation.y();
        wData::TransformComponents[objectNum].orientation.z = wData::TransformComponents[objectNum].qOrientation.z();
        wData::TransformComponents[objectNum].orientation.w = wData::TransformComponents[objectNum].qOrientation.w();
        */
        //Test to see if we have a physics component
        if((wData::Objects[objectNum].gameObjectID & 32) == 32){
            /*
            //Copy over to allow us to use with glm
            wData::TransformComponents[objectNum].positon.x = wData::TransformComponents[objectNum].trans.getOrigin().getX();
            wData::TransformComponents[objectNum].positon.y = wData::TransformComponents[objectNum].trans.getOrigin().getY();
            wData::TransformComponents[objectNum].positon.z = wData::TransformComponents[objectNum].trans.getOrigin().getZ();

            wData::TransformComponents[objectNum].orientation.x = wData::TransformComponents[objectNum].trans.getRotation().getX();
            wData::TransformComponents[objectNum].orientation.y = wData::TransformComponents[objectNum].trans.getRotation().getY();
            wData::TransformComponents[objectNum].orientation.z = wData::TransformComponents[objectNum].trans.getRotation().getZ();
            wData::TransformComponents[objectNum].orientation.w = wData::TransformComponents[objectNum].trans.getRotation().getW();
            */
        }


        //Cast orientation to the matrix for use and get our locals
        //wData::TransformComponents[objectNum].localRotate = glm::mat4_cast(wData::TransformComponents[objectNum].orientation);

        wData::TransformComponents[objectNum].localScale = glm::scale(glm::mat4(1.0f), glm::vec3(wData::TransformComponents[objectNum].scale.x,
                                                                                                                   wData::TransformComponents[objectNum].scale.y,
                                                                                                                   wData::TransformComponents[objectNum].scale.z));

        wData::TransformComponents[objectNum].localTranslate = glm::translate(glm::mat4(1.0f),
                                                                                glm::vec3(wData::TransformComponents[objectNum].positon.x,
                                                                                          wData::TransformComponents[objectNum].positon.y,
                                                                                          wData::TransformComponents[objectNum].positon.z));
        glm::mat4 localTranslate;
        glm::mat4 localRotate;
        glm::mat4 localScale;

        glm::mat4 parentWorldTranslate;
        glm::mat4 parentWorldRotate;
        glm::mat4 parentWorldScale;

        //make sure we have a parent object
        if(wData::Objects[objectNum].parentGameObjectID != -1){

            parentWorldTranslate = wData::TransformComponents[wData::Objects[objectNum].parentGameObjectID].worldTranslate;
            parentWorldRotate = wData::TransformComponents[wData::Objects[objectNum].parentGameObjectID].worldRotate;
            parentWorldScale = wData::TransformComponents[wData::Objects[objectNum].parentGameObjectID].worldScale;

            localTranslate = wData::TransformComponents[objectNum].localTranslate;
            localRotate = wData::TransformComponents[objectNum].localRotate;
            localScale = wData::TransformComponents[objectNum].localScale;

            //Transform the child against the parent
            wData::TransformComponents[objectNum].worldTranslate =  parentWorldTranslate * localTranslate;
            wData::TransformComponents[objectNum].worldRotate = parentWorldRotate * localRotate;
            wData::TransformComponents[objectNum].worldScale = parentWorldScale * localScale;

        }else {
                //We don't have a parent object, we transform them without their transforms
                wData::TransformComponents[objectNum].worldTranslate =  localTranslate;
                wData::TransformComponents[objectNum].worldRotate = localRotate;
                wData::TransformComponents[objectNum].worldScale = localScale;
        }

        //Combine the matrices together
        wData::TransformComponents[objectNum].model = wData::TransformComponents[objectNum].worldTranslate * wData::TransformComponents[objectNum].worldRotate * wData::TransformComponents[objectNum].worldScale;

        //Make sure this object has children
        if(!wData::Objects[objectNum].childGameObjectIDs.empty()){
            //Now loop through all of the children
            for(int j = 0; j < wData::Objects[objectNum].childGameObjectIDs.size(); ++j){
                //Now check for children and update
                updateSceneGraph(wData::Objects[objectNum].childGameObjectIDs[j]);
            }
        }
    }
}


void entityProcessing::updateCameraComponents(){
	for(int i = 0; i < wData::Objects.size(); ++i){
		if((wData::Objects[i].gameObjectID & 16) == 16)
		{
            eData::projection = entityManager::gameObjects::cameraComponent::UpdateProjection(&wData::Objects[i]);
			eData::view = entityManager::gameObjects::cameraComponent::UpdateView(&wData::Objects[i]);
		}
	}
}

void entityProcessing::runCoreUpdate()
{
    wData::WorldNotificationHandler->ProcessPostContracts();

    for(int i = 0; i < wData::Objects.size(); ++i){
        if(wData::TransformComponents[wData::Objects[i].componentLocations[0]].isDirty == true)
            updateSceneGraph(i);

        wData::TransformComponents[wData::Objects[i].componentLocations[0]].isDirty = true;
    }

	updateCameraComponents();
}

void entityProcessing::runCoreDraw(GLSLShader *shader3D, GLSLShader *shader2D)
{
	drawAllObjects(shader3D, shader2D);
}

void entityProcessing::initLive3DObjects()
{

}
void entityProcessing::initLive2DObjects()
{

}

void entityProcessing::initPhysicsComponents()
{
    //Set up world physics data

    // Set up the collision configuration and dispatcher

    // Build the broadphase

    // The actual physics solver

    // The world.

    //Now set p physics data for each object
    for(int i =0; i < wData::Objects.size();++i){
        if((wData::Objects[i].gameObjectID & 32) == 32){

            /*if(mass != 0.0f){
            }*/
            //Mass in Kg 0 = static object
        }
    }
}
void entityProcessing::updatePhysicsComponents(float delta){
}


void entityProcessing::updateMeshComponents(){

}
void entityProcessing::initCameraComponents(){

}
