#pragma once
class Pin_control
{
public:
	Pin_control();
	virtual ~Pin_control();
	virtual void read_pin();
	virtual int get_pin();

private:
	static int pin_to_control_;
};

