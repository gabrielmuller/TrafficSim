#ifndef SIMPLE_TIME_H_
#define SIMPLE_TIME_H_

#include <string>
#include <sstream>
#include <iomanip>

const unsigned int MILLIS_IN_DAY = 86400000;
namespace utility {

/** Relógio.
 * Armazena tempo em milissegundos, com operações e conversões.
 */

class Simple_time {

private:
	unsigned int milli_;

public:
	/** Construtor padrão.
	 *
	 */
	Simple_time() {
		milli_ = 0;
	}
	/** Construtor.
	 * \param milli tempo em milissegundos.
	 */
	Simple_time(unsigned int milli) {
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
	Simple_time operator+ (int milli) {
		Simple_time c =  *(new Simple_time (milli));
		milli = milli % MILLIS_IN_DAY;
		c.milli_ = (milli + milli_) % MILLIS_IN_DAY;
		return c;

	}

	Simple_time operator-(int milli) {
		return *this + (-milli);
	}

	/** Soma dois Clocks.
	 *
	 */
	Simple_time operator+ (Simple_time other) {
		unsigned int a, b, sum;
		a = this->milli_;
		b = other.milli_;
		sum = (a + b) % MILLIS_IN_DAY;
		return *(new Simple_time(sum));
	}

	bool operator< (const Simple_time other) const {
		return milli_ < other.milli_;
	}
};

}

#endif /* SIMPLE_TIME_H_ */
