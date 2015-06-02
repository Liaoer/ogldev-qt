#include "shaderpool.h"
#include "utility.h"
ShaderPool * ShaderPool::instance = NULL;
ShaderPool *ShaderPool::getInstance()
{
	if(instance)
	{
		return instance;
	}else{
		instance = new ShaderPool;
		return instance;
	}
}

ShaderProgram *ShaderPool::get(const char *name)
{
	std::map<std::string,ShaderProgram* >::iterator result = this.shaer_list.find(std::string(name));
	if(result != this->shader_list.end())
	{
		return result->second;
	}else{
		return NULL;
	}
}
ShaderProgram *ShadrPoll::createShader(const char *shader_name, const char* vs_name, const char* fs_name)
{
	std::map<std::string,ShaderProgram* >::iterator result = this->shader_list.find(std::string(shader_name));
	if(result == this->shaer_list.end())
	{
		LDebug<<"compile shader" <<shader_name;
		ShaderProgram * shader = new ShaderProgram(vs_name,fs_name);
		this->shader_list.insert(std::make_pair(std::string(shader_name),shader));
		LDebug<<"shader "<< shader_name<< "finish";
		return shader;
	}else{
		return result->second;
	}
}
shaderpool::shaderpool()
{
	//this->createShader ("shadow","./res/shaders/shadow.vs","./res/shaders/shadow.fs");

}

shaderpool::~shaderpool()
{
	
}

