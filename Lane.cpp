#include <Car.cpp>
#include "linked_queue.h"

class Lane {
private:
	structures::LinkedQueue<Car> queue;
	int velocity_, size_, freeSpace_;
public:
	Lane(int velocity, int size) {
		velocity_ = velocity;
		size_ = size;
	}

	void addCar(Car car) {
		if (car.size() <= freeSpace_) {
			queue.enqueue(car);
			freeSpace_ -= car.size();
		}
	}

	Car removeCar() {
		Car car = queue.dequeue();
		freeSpace_ += car.size();
		return car;
	}

	bool empty() {
		return queue.empty();
	}
};

class Spawn : public Lane {
private:
public:
	void createCar() {
		Car car;
		addCar(car);
	}
};
