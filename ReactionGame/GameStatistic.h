#pragma once

class Game_statistic{
public:
	// constructor, default initial state is off
	Game_statistic();

	virtual void max_rounds_init(int rounds);

	virtual int get_max_rounds();

	virtual int get_won_games_pl1();

	virtual int get_won_games_pl2();

	virtual void won_games_pl1_cnt_up();

	virtual void won_games_pl2_cnt_up();

	virtual int get_rounds_left();

	virtual int get_current_round();

	virtual void current_round_cnt_up();

	virtual void stats_reset();

private:
	int rounds_left_;
	int max_rounds_;
	int current_round_;
	int won_pl1_;
	int won_pl2_;;
};