#pragma once

class IDigitalInput {
public:
	virtual bool read(int pin) = 0;

	virtual void init(int pin) = 0;

	virtual bool last_state() = 0;

	virtual void buttonISR() = 0;

	virtual bool button() = 0;

	virtual int time() = 0;

	virtual void buttonISR_reset() = 0;

	// virtual destructor, as always!
	virtual ~IDigitalInput() = 0;
};
