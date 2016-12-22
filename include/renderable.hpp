#ifndef __RENDERABLE__HPP
#define __RENDERABLE__HPP

#include <GL/glew.h>
#include <camera.hpp>

class Renderable {

public:
	GLuint vao;
	GLuint buffer;
	GLuint colorBuffer;
	GLuint program;

	~Renderable () {}

	virtual void initBuffers () = 0;
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

	void setColorBuffer (const GLuint colorBuffer) {
		this->colorBuffer = colorBuffer;
	}
	GLuint getColorBuffer () const {
		return colorBuffer;
	}

	void setProgram (const GLuint program) {
		this->program = program;
	}
	GLuint getProgram () const {
		return program;
	}
};
#endif
