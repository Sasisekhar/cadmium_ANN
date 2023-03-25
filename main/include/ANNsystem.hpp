#ifndef CADMIUM_EXAMPLE_BLINKY_HPP_
#define CADMIUM_EXAMPLE_BLINKY_HPP_

#include <../../components/cadmium_v2/include/cadmium/core/modeling/coupled.hpp>

#ifdef RT_ESP32
	#include <../../components/cadmium_v2/include/cadmium/core/real_time/ESP32/io/serialInput.hpp>
#endif

#include "ANNatomic.hpp"

#ifndef RT_ESP32
	#include "generator.hpp"
#endif

namespace cadmium::ANNsystem {

	struct ANNsystem : public Coupled {

		/**
		 * Constructor function for the ANNsystem model.
		 * @param id ID of the ANNsystem model.
		 */
		ANNsystem(const std::string& id) : Coupled(id) {
            auto annatomic = addComponent<cadmium::TFLMSystem::ANNatomic>("annatomic");
#ifdef RT_ESP32		
			// ESP32
			// auto digitalOutput = addComponent<DigitalOutput>("digitalOuput", 2);
			// auto digitalInput  = addComponent<DigitalInput>("digitalInput", 0);
			// BLUE PILL
			// auto digitalOutput = addComponent<DigitalOutput>("digitalOuput", PC_13);
			// auto digitalInput  = addComponent<DigitalInput>("digitalInput", PB_14);

			auto serialInput = addComponent<SerialInput>("serialInput");

			addCoupling(serialInput->out, annatomic->in);
#else
			// auto generator = addComponent<Generator>("generator");
			// addCoupling(generator->out, blinky->in);
#endif
		}
	};
}  //namespace cadmium::blinkySystem

#endif //CADMIUM_EXAMPLE_BLINKY_HPP_
