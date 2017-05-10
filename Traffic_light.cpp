#ifndef TRAFFIC_LIGHT_CPP_
#define TRAFFIC_LIGHT_CPP_

#include "array_list.h"

enum direction {NORTH, SOUTH, EAST, WEST};

class Traffic_light {
private:
	direction direction_ = NORTH;
	bool closed_ = false; // Coloquei só porque Event ta usando metodos com closed, é pra mudar
public:
	Traffic_light() {

	}

	std::string name() {
		return "pisca pisca";
	}

	direction direction() {
		return direction_;
	}

	void changeDirection() {
		switch(direction_) {
			case NORTH: direction_ = EAST; break;
			case EAST: direction_ = SOUTH; break;
			case SOUTH: direction_ = WEST; break;
			case WEST: direction_ = NORTH; break;
		}
	}

	void switch_light() {
		closed_ = !closed_;
	}

	bool get_closed() {
		return closed_;
	}
};

#endif
