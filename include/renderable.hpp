#ifndef __RENDERABLE__HPP
#define __RENDERABLE__HPP

#include <GL/glew.h>
#include <camera.hpp>
#include <SOIL/SOIL.h>
#include <math2d.hpp>

class Renderable {

public:
	GLuint vao;
	GLuint buffer;
	// GLuint colorBuffer;
	GLuint program;
	GLuint texture;

	~Renderable () {}

	virtual void initBuffers (Vector2f p[8], const char* textureFile);
	virtual void render (Camera) const = 0;

	void setVao (const GLuint vao) {
		this->vao = vao;
	}
	GLuint getVao () const {
		return vao;
	}

	void setBuffer (const GLuint buffer) {
		this->buffer = buffer;
	}
	GLuint getBuffer () const {
		return buffer;
	}

	void setTexture (const GLuint texture) {
		this->texture = texture;
	}
	GLuint getTexture () const {
		return texture;
	}


	void setProgram (const GLuint program) {
		this->program = program;
	}
	GLuint getProgram () const {
		return program;
	}
};
#endif
