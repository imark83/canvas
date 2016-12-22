#include <matrix.hpp>


int main(int argc, char const *argv[]) {
	Mat a(6,7);
	Mat b(6,7);

	b(0,4) = 2;
	b(2,2) = -5;

	std::cout << "rot (30) = " << rotMatrix (30) << std::endl;
	return 0;
}
