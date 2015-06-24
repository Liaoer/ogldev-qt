#ifndef MESHDRAWCOMAND_H
#define MESHDRAWCOMAND_H
#include <QOpenGLFunctions_3_0>
#include <QGLShaderProgram>
#include "base/vertexdata.h"
#include "shader/shader_program.h"
#include <QMatrix4x4>
#include "material/material.h"
#include "base/bonedata.h"

class MeshDrawCommand : protected QOpenGLFunctions_3_0
{
public:
	void synchronizeData(ShaderProgram *shader, Material *material, GLuint vertices, GLuint indices);
	void init(Material *material, GLuint vertices, GLuint indices, int indices_count);
	void init(Material *material, GLuint vertices, GLuint indices, GLuint bone, GLuint bone, int indices_count);
	void commandSetRenderState(ShaderProgram *shader, Material *material, GLuint vertices, GLuint indices, bool withoutTexture = false);
	void setShaderState();
	MeshDrawCommand();
	void Draw();
	ShaderProgram *getShaderProgram();
	std::vertor<BoneData> m_bones;
private:
	int indices_count;
	void setTextureState();
	void setAttribState();
	ShaderProgram *shaderProgram;
	Material *material;
	GLuint vbo[3];
	int shader_id;
		
};

#endif // MESHDRAWCOMAND_H