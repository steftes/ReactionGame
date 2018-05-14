
#include <wiringPi.h>
#include <iostream>

#include "GameStatistic.h"


Game_statistic::Game_statistic() 
{
}

void Game_statistic::max_rounds_init()
{
	std::cin >> max_rounds_; // MFA this might fail, you might want to handle this
}

int Game_statistic::max_rounds()
{
	return max_rounds_;
}


int Game_statistic::won_games_pl1()
{
	return won_pl1_;
}

int Game_statistic::won_games_pl2()
{
	return won_pl2_;
}

void Game_statistic::won_games_pl1_cnt()
{
	won_pl1_++;
}

void Game_statistic::won_games_pl2_cnt()
{
	won_pl2_++;
}

int Game_statistic::rounds_left()
{
	return max_rounds_ - current_round_;
}

int Game_statistic::current_round()
{
	return current_round_;
}

void Game_statistic::current_round_cnt_up()
{
	current_round_ = current_round_ + 1;
}

void Game_statistic::stats_reset()
{
	rounds_left_ = 0;
	max_rounds_ = 0;
	current_round_ = 0;
	won_pl1_ = 0;
	won_pl2_ = 0;
}


