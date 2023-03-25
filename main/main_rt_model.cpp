#include <stdio.h>
#include "../components/cadmium_v2/include/cadmium/core/simulation/root_coordinator.hpp"
#include "../components/cadmium_v2/include/cadmium/core/logger/rt.hpp"
#include <limits>
#include "include/ANNsystem.hpp"

using namespace cadmium::ANNsystem;
extern "C" {
	#ifdef RT_ESP32
		void app_main() //starting point for ESP32 code
	#else
		int main()		//starting point for simulation code (Ugly, have to think of solution)
	#endif
	{
		std::shared_ptr<ANNsystem> model = std::make_shared<ANNsystem> ("ANNSystem");
		auto rootCoordinator = cadmium::RootCoordinator(model);

		#ifndef NO_LOGGING
			auto logger = std::make_shared<cadmium::RTLogger>(";");
			rootCoordinator.setLogger(logger);
		#endif

		rootCoordinator.start();
	// 	rootCoordinator.simulate(std::numeric_limits<double>::infinity());
		rootCoordinator.simulate(100.0);
		rootCoordinator.stop();

		#ifndef RT_ESP32
			return 0;
		#endif
	}
}
