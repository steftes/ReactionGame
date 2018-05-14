#pragma once

class IDigital_input {
public:
	virtual bool read(int pin) = 0;

	virtual void init(int pin) = 0;

	virtual bool last_state() = 0;

	virtual void buttonISR() = 0;

	virtual bool get_button() = 0; 

	virtual int time_point() = 0; 

	virtual void buttonISR_reset() = 0;

	// virtual destructor, as always!
	virtual ~IDigital_input() = 0;
};
