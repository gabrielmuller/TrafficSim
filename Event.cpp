#ifndef EVENT_CPP_
#define EVENT_CPP_

#include <sstream>
#include <Car.cpp>
#include <Traffic_light.cpp>
#include <simple_time.h>
/** Usado como valor nulo para structs
 *
 */
struct nothing{};

/** Enumeração dos tipos de evento
 *
 */
enum event_type {car_enter_lane = 0, car_enter_queue = 1, light_switch = 2};

/** Struct dos possíveis tipos de info adicional
 *
 */
struct extra_info {
	/** Caso light_switch
	 * true se semáforo mudou para verde
	 */
	bool to_green;

	/** Caso car_enter_lane
	 * from -> pista origem (nullptr se carro surgiu)
	 * to -> pista destino (nullptr se carro sumiu)
	 * Caso car_enter_queue
	 * from = to = pista do carro
	 */
	Lane* from;
	Lane* to;

	extra_info() {
		to_green = false;
		from = nullptr;
		to = nullptr;
	}
};

/** Objeto participando do evento
 *
 */

struct relevant_obj {
	/** Caso car_enter_lane
	 * ou car_enter_queue
	 */
	Car* car;

	/** Caso light_switch
	 *
	 */
	Traffic_light* light;

	relevant_obj() {
		car = nullptr;
		light = nullptr;
	}
};

class Event {
private:
	event_type event_; /**< tipo do evento */
	utility::Simple_time time_; /**< tempo em que o evento ocorreu */

	relevant_obj object_; /**< objeto que participa do evento */
	extra_info extra_; /**< informação adicional */

public:
	/** Construtor no caso car_enter_lane
	 *	\param time tempo do evento
	 *	\param car carro
	 *	\param from pista origem
	 *	\param to pista destino
	 */
	Event (utility::Simple_time time, Car* car, Lane* from, Lane* to) {
		event_ = car_enter_lane;
		time_ = time;
		object_ = *(new relevant_obj());
		object_.car = car;
		extra_ = *(new extra_info());
		extra_.from = from;
		extra_.to = to;
	}

	/** Construtor no caso car_enter_queue
	 *  \param time tempo do evento
	 *  \param car carro
	 *  \param current pista atual do carro
	 */
	Event (utility::Simple_time time, Car* car, Lane* current) {
		event_ = car_enter_queue;
		time_ = time;
		object_ = *(new relevant_obj());
		object_.car = car;
		extra_ = *(new extra_info());
		extra_.from = current;
		extra_.to = current;
	}

	/** Construtor no caso light_switch
	 *  \param time tempo do evento
	 *  \param light semáforo
	 *  \param to_green mudou para verde?
	 */
	Event (utility::Simple_time time, Traffic_light* light, bool to_green) {
		event_ = light_switch;
		time_ = time;
		object_ = *(new relevant_obj());
		object_.light = light;
		extra_ = *(new extra_info());
		extra_.to_green = to_green;
	}

	/** Um evento aconteceu antes do outro?
	 *  \return true se lado esquerdo aconteceu antes do direito
	 */
	bool operator< (const Event other) const {
		return time_ < other.time_;
	}

	/** Representação em string do evento.
	 *
	 */
	std::string to_string () {
		std::ostringstream output;
		std::string parts[7];
		output << time_.to_string() << " ";

		if (event_ == car_enter_lane) {
			std::string from_str, to_str;
			if (extra_.from == nullptr) {
				from_str = "o nada";
			} else {
				from_str = "a pista " + extra_.from->name();
			}
			if (extra_.to == nullptr) {
				to_str = "o nada";
			} else {
				to_str = "a pista " + extra_.to->name();
			}
			output << "Carro " << object_.car->name() << " vindo d"
					<< from_str << " foi para " << to_str << ".";
		} else if (event_ == car_enter_queue) {
			output << "Carro " << object_.car->name() << " entrou na sua fila " << extra_.from->name() << ".";
		} else if (event_ == light_switch) {
			std::string color = extra_.to_green ? "verde" : "vermelho";
			output << "Semáforo " << object_.light->name() << " mudou sua cor para " << color << ".";
		} else {
			throw "Tipo inválido de evento";
		}
		return output.str();
	}
};

#endif
