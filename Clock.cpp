#include "linked_list.h"
#include <string>
#include <sstream>
#include <Event.cpp>

#ifndef CLOCK_CPP_
#define CLOCK_CPP_

class Clock {
public:

	std::string to_string() {
		std::ostringstream output;
		output << "Lista de eventos:\n---------------------------\n" << events.to_string();
		return output.str();
	}

	void push(Event event) {
		events.insert_sorted(event);
	}


private:
	structures::LinkedList<Event> events;
};
#endif
