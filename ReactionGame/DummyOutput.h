#pragma once

#include "IDigitalOutput.h"

class Dummy_output final : public IDigitalOutput {
public:
	// constructor, default initial state is off
	Dummy_output(bool initial_state = false);

	virtual void turn_on(int led) override;

	virtual void turn_off(int led) override;

	virtual bool out_state() const override;

private:
	bool out_state_;
};