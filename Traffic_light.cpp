#include <Lane.cpp>

#include "array_list.h"

class Traffic_light {
private:
	structures::ArrayList<Lane*>* exit_lanes_;
	Lane* self_lane_;
	int* probabilities_;
	bool closed_;
public:
	Traffic_light(Lane* exit_lanes, Lane* self_lane, int* probabilities) {
		
	}
};
