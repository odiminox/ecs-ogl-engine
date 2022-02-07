//A simple class for handling GLSL shader compilation
//Auhtor: Movania Muhammad Mobeen
//Modified by: Simon Jordan
//Last Modified: August 28th, 2012

#pragma once
#include "globals.h"
#include <GL/glew.h>
#include <map>
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace std;

class GLSLShader
{
public:
	GLSLShader(void);
	~GLSLShader(void);
	void LoadFromString(GLenum whichShader, const string source);
	void LoadFromFile(GLenum whichShader, const string filename);
	void CreateAndLinkProgram();
	void bind();
	void unbind();
	void AddAttribute(const string attribute);
	void loadAttribute(GLuint& inAttribName, std::string name);
	void AddUniform(const string uniform);
	void   setUniform(const char *name,float x,float y, float z);
	void   setUniform(const char *name, const glm::vec3 & v);
	void   setUniform(const char *name, const glm::vec4 & v);
	void   setUniform(const char *name, const glm::mat4 & m);
	void   setUniform(const char *name, const glm::mat3 & m);
	void   setUniform(const char *name, float val );
	void   setUniform(const char *name, int val );
	void   setUniform(const char *name, bool val );
	GLuint GetProgram() const;
	//An indexer that returns the location of the attribute/uniform
	GLuint operator[](const string attribute);
	GLuint operator()(const string uniform);
	//Set uniforms
	//void setUniform(const char* name, const vector3 & v);
	//void setUniform()
	//Program deletion
	void DeleteProgram() {glDeleteProgram(_program);_program=-1;}
	GLuint	_program;
private:
	enum ShaderType {VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER, COMPUTE_SHADER};

	GLuint location;
	int _totalShaders;
	GLuint _shaders[4];//0->vertexshader, 1->fragmentshader, 2->geometryshader, 3->computeshader
	map<string,GLuint> _attributeList;
	map<string,GLuint> _uniformLocationList;
};
