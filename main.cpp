#include <iostream>
#include <clock.h>
#include <random.h>

int main(int argc, char* argv[]) {
	using namespace utility;
	Clock c = *(new Clock(7200100));
	Clock d = *(new Clock(3610200));
	seed();
	std::cout << (c+d).to_string() << " " << random_range(5, 15) << std::endl;
	return 0;
}
