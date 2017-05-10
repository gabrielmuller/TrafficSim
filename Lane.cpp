#ifndef LANE_CPP_
#define LANE_CPP_

#include <cstdlib>
#include "Car.cpp"
#include "linked_queue.h"
#include "Traffic_light.cpp"

class Lane {
protected:

	Traffic_light* light_;
	direction direction_;
	int* probabilities_;  				// [0] left, [1] straight, [2] right
	int velocity_, size_, freeSpace_;

	int totalIn_ = 0, totalOut_ = 0;
	structures::LinkedQueue<Car*> queue;
  
public:

	Lane(Traffic_light *light, direction dir, int* prob, int vel, int size):
		light_(light),
		direction_(dir),
		probabilities_(prob),
		velocity_(vel),
		size_(size),
		freeSpace_(size)
	{}

	void addCar(Car* car) {
		if (car->size() >= freeSpace_) {
			throw std::runtime_error("Full lane");
		}

		queue.enqueue(car);
		freeSpace_ -= car->size();
		++totalIn_;
	}

	Car* removeCar() {
		Car* car = queue.dequeue();
		freeSpace_ += car->size();
		++totalOut_;
		return car;
	}

	bool empty() {
		return queue.empty();
	}

	std::string name() {
		return "copa pistão";
	}

	int timeTaken() {
		return size_ / velocity_ / 3.6;
	}
};

class Spawn : public Lane {
private:
	int fixedFreq, varFreq;
	Lane *rightExit, *straightExit, *leftExit;
public:
	Spawn(Traffic_light* light, direction dir, int* prob, int vel, int size, int ff, int vf, Lane* r, Lane* s, Lane* l):
		Lane(light, dir, prob, vel, size),
		fixedFreq(ff - vf), varFreq(2*vf),
		rightExit(r), straightExit(s), leftExit(l)
	{}

	void createCar() {
		Car* car;
		addCar(car);
	}

	Lane* moveCar() {
		if (light_->direction() != direction_) {
			throw std::runtime_error("Traffic light's red");
		}

		auto car = removeCar();

		int r = rand() % 100;

		if (r < probabilities_[0]) {
			leftExit->addCar(car);
			return leftExit;
		} else if (r < probabilities_[0] + probabilities_[1]) {
			rightExit->addCar(car);
			return rightExit;
		} else {
			straightExit->addCar(car);
			return straightExit;
		}
	}

	int timeForNewCar() {
		return fixedFreq + varFreq*float(rand())/RAND_MAX;
	}
};

class CentralLane : public Lane {
private:
	Lane *rightExit, *straightExit, *leftExit;
public:
	CentralLane(Traffic_light* light, direction dir, int* prob, int vel, int size, Lane* r, Lane* s, Lane* l):
		Lane(light, dir, prob, vel, size),
		rightExit(r), straightExit(s), leftExit(l)
	{}

	Lane* moveCar() {
		if (light_->direction() != direction_) {
			throw std::runtime_error("Traffic light's red");
		}

		auto car = removeCar();

		int r = rand() % 100;

		if (r < probabilities_[0]) {
			leftExit->addCar(car);
			return leftExit;
		} else if (r < probabilities_[0] + probabilities_[1]) {
			rightExit->addCar(car);
			return rightExit;
		} else {
			straightExit->addCar(car);
			return straightExit;
		}
	}
};

class Edge : public Lane {
public:
	Edge(Traffic_light* light, direction dir, int* prob, int vel, int size):
		Lane(light, dir, prob, vel, size)
	{}
};

#endif
