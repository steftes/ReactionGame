#pragma once

#pragma once

#include "IGameStatistic.h"


class Dummy_game_statistic final : public IGameStatistic {
public:
	// constructor, default initial state is off
	Dummy_game_statistic();

	virtual void max_rounds_init() override;

	virtual int max_rounds() override;

	virtual int won_games_pl1() override;

	virtual int won_games_pl2() override;

	virtual void won_games_pl1_cnt() override;

	virtual void won_games_pl2_cnt() override;

	virtual int rounds_left() override;

	virtual int current_round() override;

	virtual void current_round_cnt_up() override;

	virtual void stats_reset() override;

private:
	int rounds_left_;
	int max_rounds_;
	int current_round_ = 0;;
	int won_pl1_ = 0;
	int won_pl2_ = 0;
};