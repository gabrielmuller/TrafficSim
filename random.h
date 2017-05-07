#ifndef RANDOM_H_
#define RANDOM_H_

#include <ctime>
#include <cstdlib>

namespace utility {

void seed() {
	srand(time(NULL) * 1000);
}
double random_value () {
	return double (rand()) / float (RAND_MAX + 1.0);
}

/** Inteiro aleatório em [start, end)
 * \param start resultado mínimo inclusivo.
 * \param end resultado máximo exclusivo.
 * \return número inteiro aleatório no intervalo especificado.
 */
int random_range (int start, int end) {
	return int ((random_value() * (end-start)) + start);
}

/** Valor aleatório entre 0 e 1
 * \return número real aleatório no intervalo [0, 1)
 */


}

#endif /* RANDOM_H_ */
