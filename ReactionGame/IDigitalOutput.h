#pragma once

class IDigitalOutput {
public:
	virtual void turn_on(int led) = 0;

	virtual void turn_off(int led) = 0;

	virtual bool out_state() const = 0;

	// virtual destructor, as always!
	virtual ~IDigitalOutput() = 0;
};