#ifndef __RENDERABLE__HPP
#define __RENDERABLE__HPP

#include <GL/glew.h>

class Renderable {

public:
	GLuint vao;
	GLuint buffer;
	GLuint program;
	GLuint colorBuffer;

	Renderable () {}
	Renderable (GLuint _program) {program = _program;}
	~Renderable () {}

	virtual void initBuffers () = 0;
	virtual void render () const = 0;

	void setProgram (const GLuint program) {
		this->program = program;
	}
	GLuint getProgram () const {
		return program;
	}
};
