#include <iostream>
#include <SOIL/SOIL.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	int width, height;
	unsigned char *image;
	image = SOIL_load_image("car.png", &width, &height, 0, SOIL_LOAD_RGB);
	std::cout << "w = " << width << std::endl;
	std::cout << "h = " << height << std::endl;

	free (image);
	return 0;
}
