#pragma once


class IGameStatistic {
public:
	virtual void max_rounds_init() = 0;

	virtual int max_rounds() = 0;

	virtual int current_round() = 0;

	virtual void current_round_cnt_up() = 0;

	virtual int won_games_pl1() = 0;

	virtual int won_games_pl2() = 0;

	virtual void won_games_pl1_cnt() = 0;

	virtual void won_games_pl2_cnt() = 0;

	virtual int rounds_left() = 0;

	virtual void stats_reset() = 0;


	// virtual destructor, as always!
	virtual ~IGameStatistic() = 0;

private:
	int rounds_left_;
	int max_rounds_;
	int current_round_ = 0;;
	int won_pl1_ = 0;
	int won_pl2_ = 0;
};