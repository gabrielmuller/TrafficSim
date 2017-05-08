#ifndef CAR_CPP_
#define CAR_CPP_

#include <cstdlib>
#include <string>

class Car {

private:
	int size_;  /**< Tamanho do carro. Varia de 2 a 6m, mais 3m entre carros */

public:
	Car() {
		size_ = 5 + 4 * (rand() / RAND_MAX);
	}

	int size() {
		return size_;
	}

	std::string name() {
		return "Relampogos McDonalds";
	}
};

#endif
