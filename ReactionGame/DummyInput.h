#pragma once

#include "IDigitalInput.h"

class Dummy_input final : public IDigitalInput {
public:
	// constructor, default initial state is off
	Dummy_input();

	virtual bool read(int pin) override;

	virtual bool last_state() override;

	virtual void init(int pin) override;

	virtual void buttonISR() override;

	virtual bool button() override;

	virtual int time() override;

	virtual void buttonISR_reset() override;

private:
	bool in_value_;
	bool button_ = 0;
	int time_ = 0;

};