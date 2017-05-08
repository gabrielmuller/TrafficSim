/*
 * time_format.h
 *
 *  Created on: 7 de mai de 2017
 *      Author: gabri
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include <string>
#include <sstream>
#include <iomanip>

const unsigned int MILLIS_IN_DAY = 86400000;
namespace utility {

/** Relógio.
 * Armazena tempo em milissegundos, com operações e conversões.
 */

class Clock {

private:
	unsigned int milli_;

public:
	/** Construtor padrão.
	 *
	 */
	Clock() {
		milli_ = 0;
	}
	/** Construtor.
	 * \param milli tempo em milissegundos.
	 */
	Clock(unsigned int milli) {
		milli_ = milli % MILLIS_IN_DAY;
	}

	/** Converte para std::string.
	 * \return tempo em formato HH:DD:MM::mmm
	 */
	std::string to_string () {
		int hours = (milli_ / 3600000) % 24;
		int minutes = (milli_ / 60000) % 60;
		int seconds = (milli_ / 1000) % 60;
		int milliseconds = milli_ % 1000;

		std::ostringstream output;

		output << std::setw(2) << std::setfill('0') << hours << ":"
		<< std::setw(2) << std::setfill('0') << minutes << ":"
		<< std::setw(2) << std::setfill('0') << seconds << "::"
		<< std::setw(3) << std::setfill('0') << milliseconds;
		return output.str();
	}

	/** Adiciona milissegundos ao tempo.
	 * \param milli inteiro com sinal a adicionar.
	 * \return tipo Clock com o valor de tempo resultante.
	 */
	Clock operator+ (int milli) {
		Clock c =  *(new Clock (milli));
		milli = milli % MILLIS_IN_DAY;
		c.milli_ = (milli + milli_) % MILLIS_IN_DAY;
		return c;

	}

	Clock operator-(int milli) {
		return *this + (-milli);
	}

	/** Soma dois Clocks.
	 *
	 */
	Clock operator+ (Clock other) {
		unsigned int a, b, sum;
		a = this->milli_;
		b = other.milli_;
		sum = (a + b) % MILLIS_IN_DAY;
		return *(new Clock(sum));
	}

};

}

#endif /* CLOCK_H_ */
