#include "linked_list.h"
#include <string>
#include <iostream>
#include <sstream>
#include <Event.cpp>
#include <simple_time.h>

#ifndef CLOCK_CPP_
#define CLOCK_CPP_

class Clock {
public:

	/** Lista de eventos a serem executados como string
	 *  para debug
	 */
	std::string to_string() {
		std::ostringstream output;
		output << "Lista de eventos:\n---------------------------\n" << events.to_string();
		return output.str();
	}

	/** Adiciona evento cronologicamente.
	 * 	\param event evento a ser adicionado.
	 */
	void push(Event event) {
		events.insert_sorted(event);
	}

	/** Anda um passo no relógio.
	 *
	 */
	void step() {
		Event step = events.pop_back();
		std::cout << step.to_string() << std::endl;
		step.run();
		time_ = step.get_time();
		delete &step;
	}
private:
	structures::LinkedList<Event> events;
	utility::Simple_time time_;
};
#endif
