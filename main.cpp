#include <iostream>
#include <clock.h>
#include <random.h>
#include <Car.cpp>
#include <Lane.cpp>
#include <Event.cpp>

int main(int argc, char* argv[]) {
	using namespace utility;
	Clock c = *(new Clock(3605500));
	Clock d = *(new Clock(7200000));
	Event* spwn = new Event(*(new Clock(123456789)), new Car(), nullptr, new Lane());
	Event* fechou = new Event(*(new Clock()), new Traffic_light(), false);
	Event* abriu = new Event(c+d+600, new Traffic_light(), true);
	Event* queued = new Event(c-800, new Car(), new Lane());
	std::cout << spwn->to_string() << std::endl;
	std::cout << fechou->to_string() << std::endl;
	std::cout << abriu->to_string() << std::endl;
	std::cout << queued->to_string() << std::endl;

	return 0;
}
