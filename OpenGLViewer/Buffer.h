#pragma once
#include <GLAD/glad.h>

struct SBuffer
{
	void CreateBufferObject();
	void SetAttributeID(const char*, unsigned int);
	void Bind(GLenum);
	void Fill(GLsizeiptr, const void*, GLenum);
	void LinkAttribute(unsigned int, GLenum, bool, GLsizei, const void*);
	void EnableAttribute();
	void Finalize();

private:

	unsigned int m_bufferID;
	unsigned int m_attributeID;
	GLenum m_target;

};

