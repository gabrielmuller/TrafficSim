#include <iostream>
#include <random.h>
#include <Car.cpp>
#include <Lane.cpp>
#include <Event.cpp>
#include <Clock.cpp>
#include <simple_time.h>

int main(int argc, char* argv[]) {
	using namespace utility;
	Simple_time c = *(new Simple_time(3605500));
	Simple_time d = *(new Simple_time(7200000));

	Event* spwn = new Event(*(new Simple_time(123456789)), new Car(), nullptr, new Lane());
	Event* fechou = new Event(*(new Simple_time()), new Traffic_light(), false);
	Event* abriu = new Event(c+d+600, new Traffic_light(), true);
	Event* queued = new Event(c-800, new Car(), new Lane());

	Clock clock = *(new Clock());
	clock.push(*spwn);
	clock.push(*fechou);
	clock.push(*abriu);
	clock.push(*queued);

	std::cout << clock.to_string() << std::endl;
	return 0;
}
