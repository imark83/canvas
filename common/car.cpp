#include <car.hpp>
#include <SOIL/SOIL.h>


void Car::initBuffers () {
	glUseProgram (getProgram());
	// VERTEX ARRAY Y BUFFER
	GLuint vao, buffer;
	glGenVertexArrays (1, &vao);
	glGenBuffers (1, &buffer);
	glBindVertexArray (vao);
	glBindBuffer (GL_ARRAY_BUFFER, buffer);
	std::cout << "size = " << sizeof (p) << std::endl;



	glBufferData (GL_ARRAY_BUFFER, sizeof (p), p, GL_STATIC_DRAW);


	glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, 0,
			(const void*) 0);
	glEnableVertexAttribArray (0);
	glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0,
			(const void*)( 8*sizeof(GLfloat)));
	glEnableVertexAttribArray (1);


	// PREPARE TEXTURE image
	glActiveTexture(GL_TEXTURE0);
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int img_width, img_height;
	unsigned char *image;
	image = SOIL_load_image("car.png", &img_width, &img_height, 0, SOIL_LOAD_RGB);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	std::cout << "sampler = " << glGetUniformLocation(getProgram(), "texSampler") << std::endl;
	// glUniform1i(glGetUniformLocation(getProgram(), "texSampler"), 0);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	SOIL_free_image_data(image);



	setVao (vao); setBuffer (buffer); setTexture (texture);

}
void Car::render (Camera cam) const {
	glBindVertexArray (getVao());
	glBindBuffer (GL_ARRAY_BUFFER, getBuffer());
	glBindTexture(GL_TEXTURE_2D, getTexture());


	Mat trans = cam.getModel() * getModel();
	glUniformMatrix4fv (glGetUniformLocation(program, "model"), 1, GL_FALSE, trans.data);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

}
