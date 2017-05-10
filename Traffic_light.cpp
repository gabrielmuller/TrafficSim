#ifndef TRAFFIC_LIGHT_CPP_
#define TRAFFIC_LIGHT_CPP_

#include "array_list.h"

enum direction {NORTH, SOUTH, EAST, WEST};

class Traffic_light {
private:
	direction direction_ = NORTH;

public:
	Traffic_light() {

	}

	std::string name() {
		return "pisca pisca";
	}

	direction direction() {
		return direction_;
	}

	void switch_light() {
		closed_ = !closed_;
	}

	bool get_closed() {
		return closed_;
	}
};

#endif
