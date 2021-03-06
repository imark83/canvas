#include <renderable.hpp>

void Renderable::initBuffers (Vector2f p[8], const char* textureFile) {

		glUseProgram (getProgram());
		// VERTEX ARRAY Y BUFFER
		GLuint vao, buffer;
		glGenVertexArrays (1, &vao);
		glGenBuffers (1, &buffer);
		glBindVertexArray (vao);
		glBindBuffer (GL_ARRAY_BUFFER, buffer);



		glBufferData (GL_ARRAY_BUFFER, 8*sizeof (Vector2f), p, GL_STATIC_DRAW);


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
		image = SOIL_load_image(textureFile, &img_width, &img_height, 0, SOIL_LOAD_RGBA);
		glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		SOIL_free_image_data(image);

		setVao (vao); setBuffer (buffer); setTexture (texture);
}
