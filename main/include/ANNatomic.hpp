#ifndef ANNATOMIC_HPP
#define ANNATOMIC_HPP

#include "../../components/cadmium_v2/include/cadmium/core/modeling/atomic.hpp"
#include "ANN_TFLM.hpp"
#ifndef NO_LOGGING
	#include <iostream>
#endif

namespace cadmium::TFLMSystem {
	//! Class for representing the ANN DEVS model state.struct ANNState {
	struct ANNState {
		double sigma;
		float output;
		//! ANNState state constructor.
		ANNState(): sigma(0), output(0)  {}
	};
#ifndef NO_LOGGING
	/**
	 * Insertion operator for ANNState objects. It displays the value of sigma and predicted output.
	 * @param out output stream.
	 * @param s state to be represented in the output stream.
	 * @return output stream with sigma and predicted output already inserted.
	 */
	std::ostream& operator<<(std::ostream &out, const ANNState& state) {
		out << "Status:, " << state.output << ", sigma: " << state.sigma;
		return out;
	}
#endif

	//! Atomic DEVS model of ANN.
	class ANNatomic : public Atomic<ANNState> {
	 private:
		
	 public:
		Port<float> out;  
		Port<float> in;

		/**
		 * Constructor function.
		 * @param id ID of the new Blinky model object.
		 */
		ANNatomic(const std::string& id): Atomic<ANNState>(id, ANNState()) {
			out = addOutPort<float>("out");
			in  = addInPort<float>("in");
			state.sigma = 0;
		}

		/**
		 * Doesn't do anything since everything is handled in the external transition function
		 * @param state reference to the current state of the model.
		 */
		void internalTransition(ANNState& state) const override {
			//no internal transition
		}

		/**
		 * Updates BlinkyState::fastToggle and BlinkyState::sigma.
		 * @param state reference to the current model state.
		 * @param e time elapsed since the last state transition function was triggered.
		 * @param x reference to the model input port set.
		 */
		void externalTransition(ANNState& state, double e) const override {
			
			float input = 0.0;

			if(!in->empty()){
				for( const auto x : in->getBag()){
					input = x;
				}
			}

			state.output = TFLMmodel::predict(input);
		}

		/**
		 * It outputs the already processed ANNState::output via the out port.
		 * @param state reference to the current model state.
		 * @param y reference to the atomic model output port set.
		 */
		void output(const ANNState& state) const override {
			out->addMessage(state.output);	
		}

		/**
		 * It returns the value of ANNState::sigma.
		 * @param state reference to the current model state.
		 * @return the sigma value.
		 */
		[[nodiscard]] double timeAdvance(const ANNState& state) const override {
			return state.sigma;
		}
		};
}  //namespace cadmium::TFLMSystem

#endif //ANNATOMIC_HPP