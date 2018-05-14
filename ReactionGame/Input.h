#pragma once

#include "IDigitalInput.h"

class Input final : public IDigital_input {
public:
	// constructor, default initial state is off
	Input();

	virtual bool read(int pin) override;

	virtual bool last_state() override;

	virtual void init(int pin) override;

	virtual void buttonISR() override;

	virtual bool get_button() override;

	virtual int time_point() override;

	virtual void buttonISR_reset() override;

private:
	bool in_value_;
	bool button_ = 0;
	int time_ = 0;

};