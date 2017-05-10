#ifndef LANE_CPP_
#define LANE_CPP_

#include <Car.cpp>
#include "linked_queue.h"
#include "Traffic_light.cpp"

enum direction {NORTH, SOUTH, EAST, WEST};

class Lane {
private:
	Traffic_light& light_;
	direction direction_;
	int* probabilities_;  // [0] left, [1] right
	structures::LinkedQueue<Car*> queue;
	int velocity_ = 0, size_ = 0, freeSpace_ = 0;
	static int totalIn_ = 0, totalOut_ = 0;

public:

	Lane(Traffic_light& light, direction dir, int* probabilities, int velocity, int size) {
		light_ = light;
		direction_ = dir;
		probabilities_ = probabilities;
		velocity_ = velocity;
		size_ = size;
		freeSpace_ = size;
	}

	void addCar(Car car) {
		if (car.size() >= freeSpace_) {
			throw std::runtime_error("Full lane");
		}
		queue.enqueue(&car);
		freeSpace_ -= car.size();
		++totalIn_;
	}

	Car removeCar() {
		Car car = queue.dequeue();
		freeSpace_ += car.size();
		++totalOut_;
		return car;
	}

	bool empty() {
		return queue.empty();
	}

	Car* frontCar() {
		return queue.front();
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
	Lane &leftExit, &straightExit, &rightExit;
public:
	void createCar() {
		Car car;
		addCar(car);
	}

	Lane& moveCar() {
		if (light_.direction() != direction) {
			throw std::runtime_error("Traffic lights red");
		}

		auto car = removeCar();

		int r = rand() % 100;

		if (r < probabilities_[0]) {
			leftExit.addCar(car);
			return leftExit;
		} else if (r > probabilities_[1]) {
			rightExit.addCar(car);
			return rightExit;
		} else {
			straightExit.addCar(car);
			return straightExit;
		}
	}
};

class Edge : public Lane {
private:
public:
};

class CentralLane : public Lane {
private:
	Lane &leftExit, &straightExit, &rightExit;
public:
	Lane& moveCar() {
		if (light_.direction() != direction) {
			throw std::runtime_error("Traffic lights red");
		}

		auto car = removeCar();

		int r = rand() % 100;

		if (r < probabilities_[0]) {
			leftExit.addCar(car);
			return leftExit;
		} else if (r > probabilities_[1]) {
			rightExit.addCar(car);
			return rightExit;
		} else {
			straightExit.addCar(car);
			return straightExit;
		}
	}
};

#endif
