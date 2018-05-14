#pragma once

class IDigital_output {  
public:
	virtual void turn_on(int led) = 0; 

	virtual void turn_off(int led) = 0;

	virtual bool out_state() const = 0;

	// virtual destructor, as always!
	virtual ~IDigital_output() = 0;
};