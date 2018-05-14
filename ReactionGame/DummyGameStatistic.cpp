////jHsdlkahslckjhasldkjh alles klar
#include <wiringPi.h>
#include <iostream>
#include "IGameStatistic.h"
#include "DummyGameStatistic.h"


Dummy_game_statistic::Dummy_game_statistic()
{
}

void Dummy_game_statistic::max_rounds_init()
{
	std::cin >> max_rounds_;
}

int Dummy_game_statistic::max_rounds()
{
	return max_rounds_;
}


int Dummy_game_statistic::won_games_pl1()
{
	return won_pl1_;
}

int Dummy_game_statistic::won_games_pl2()
{
	return won_pl2_;
}
///// serwas es is as gleiche ahahhaahahah
void Dummy_game_statistic::won_games_pl1_cnt()
{
	won_pl1_++;
}

void Dummy_game_statistic::won_games_pl2_cnt()
{
	won_pl2_++;
}

int Dummy_game_statistic::rounds_left()
{
	return max_rounds_ - current_round_;
}

int Dummy_game_statistic::current_round()
{
	return current_round_;
}

void Dummy_game_statistic::current_round_cnt_up()
{
	current_round_ = current_round_ + 1;
}

void Dummy_game_statistic::stats_reset()
{
	rounds_left_ = 0;
	max_rounds_ = 0;
	current_round_ = 0;
	won_pl1_ = 0;
	won_pl2_ = 0;
}


