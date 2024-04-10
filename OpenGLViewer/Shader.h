#ifndef SSHADER_H
#define SSHADER_H

#include <GLAD/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct SShader
{
	unsigned int id{};
	inline SShader() {};
	SShader(const char* vertexPath, const char* fragmentPath);

	void Use();

	unsigned int GetAttributeLocation(const char* _name);
	//void SetBool(const std::string& name, bool value) const;
	//void SetInt(const std::string& name, int value) const;
	//void SetFloat(const std::string& name, float value) const;

};
#endif //!SSHADER_H

