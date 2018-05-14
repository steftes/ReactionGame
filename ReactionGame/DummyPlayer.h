#pragma once

#include "IPlayer.h"

class Dummy_player final : public IPlayer {
public:
	// constructor, default initial state is off
	Dummy_player();

	virtual void name() override;
	virtual std::string give_name() override;
private:
	std::string name_;
};