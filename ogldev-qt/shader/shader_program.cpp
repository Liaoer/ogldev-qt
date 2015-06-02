#include "shader_program.h"
#include "utility.h"
#include <QDebug>
#include <assert.h>

ShaderProgram::ShaderProgram(const char *pVSFileName, const char *pFSFileName)
{
	initializeOpenGLFunctions();
	this->shader = glCreateProgram();
	
	if(shder == 0){
		fprintf(stderr,"error create shader program\n");
		exit(1);
	}
	
	string vs, fs;
	if(!unility::ReadFile(pVSFileName, vs)){
		exit(1);
	}
	
	if(!unility::ReadFile(pFSFileName, fs)){
		exit(1);
	}
	
	AddShader(shader,vs.c_str(), GL_VERTEX_SHADER);
	AddShader(shader,fs.c_str(), GL_FRAGMENT_SHADER);
	
	GLint sucess = 0;
	GLchar ErrorLog[1024] = {0};
	
	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &sucess);
	if(sucess == 0){
		glGetProgramInfoLog(shader, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
	}
	
	glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(shader, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }
}
void ShaderProgram::use()
{
    glUseProgram(shader);
}

int ShaderProgram::getShaderId()
{
    return this->shader;
}

ShaderProgram::~ShaderProgram()
{

}

