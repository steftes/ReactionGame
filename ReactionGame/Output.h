#pragma once

#include "IDigitalOutput.h"

class Output final : public IDigital_output {
public:
	// constructor, default initial state is off
	Output(bool initial_state = false);

	virtual void turn_on(int led) override;

	virtual void turn_off(int led) override;

	virtual bool out_state() const override;

private:
	bool out_state_;
};