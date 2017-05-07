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

/** Inteiro aleat�rio em [start, end)
 * \param start resultado m�nimo inclusivo.
 * \param end resultado m�ximo exclusivo.
 * \return n�mero inteiro aleat�rio no intervalo especificado.
 */
int random_range (int start, int end) {
	return int ((random_value() * (end-start)) + start);
}

/** Valor aleat�rio entre 0 e 1
 * \return n�mero real aleat�rio no intervalo [0, 1)
 */


}

#endif /* RANDOM_H_ */
