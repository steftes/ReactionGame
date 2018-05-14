#pragma once

class Player{
public:
	// constructor, default initial state is off
	Player();

	virtual void read_name();
	virtual std::string get_name();
private:
	std::string name_;
};