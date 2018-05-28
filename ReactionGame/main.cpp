#include "piproxy.h"
#include <iostream>
#include <string>
#include "Output.h"
#include "IDigitalOutput.h"
#include "Input.h"
#include "IDigitalInput.h"
#include "Player.h"
#include "GameStatistic.h"
#include <chrono>
#include "Pin_control.h"

// hallloooo
// int u = 0;

// button pins
constexpr int BUTTON_PL1 = 15;
constexpr int BUTTON_PL2 = 16;

// led pins
constexpr int LED_PL1 = 8;
constexpr int LED_PL2 = 9;
constexpr int LED_SIG = 7;

constexpr int pin_array[] = { BUTTON_PL1, BUTTON_PL2, LED_PL1, LED_PL2, LED_SIG };

// state machine
enum State_machine
{ 
	DUMMY, // Because zero isn't used 
	START, 
	COUNTDOWN, 
	WAIT_FOR_SIGNAL,
	SIGNAL, 
	STATS, 
	RESULT
};

// Output
Output led_pl1;
Output led_pl2;
Output led_signal;

// Input
Input button_pl1;
Input button_pl2;

// Player classes
Player player1;
Player player2;

// Statistic
Game_statistic stats;

// Pin check
Pin_control pin_control;
bool pin_check_end = true;

int game = 1; // State Machine

int64_t start_time_us = 0;
auto now = std::chrono::system_clock::now().time_since_epoch();
auto delta = std::chrono::duration_cast<std::chrono::microseconds>(now).count() - start_time_us;

// Prototypes
void ISR1();
void ISR2();
void start();
void countdown();
void wait_for_signal();
void signal();
void stats1();
void result();
void init_main();
void pin_check();

int main(void)  // MFA should be split in a bunch of shorter, smaller functions (20-30 lines per function is good!)
{
	pin_check();
	init_main();

	// game starts
	while (true)
	{
		switch (game)
		{
			case START: 
			{
				start();
				break;
			}

			case COUNTDOWN:
			{
				countdown();
				break;
			}

			case WAIT_FOR_SIGNAL:
			{
				wait_for_signal();
				break;
			}

			case SIGNAL:
			{
				signal();
				break;
			}

			case STATS:
			{
				stats1();
				break;
			}

			case RESULT:
			{
				result();
			}
		}	
	}
	return 0;
}







///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS /////////////////////////





// interrupt routine
void ISR1()
{
	button_pl1.buttonISR();
}

void ISR2()
{
	button_pl2.buttonISR();
}


void start()
{
	// turn all leds off
	led_pl1.turn_off(LED_PL1);
	led_pl2.turn_off(LED_PL2);
	led_signal.turn_off(LED_SIG);

	// player names
	std::cout << "Player one type in your name: ";
	player1.read_name();
	std::cout << "Player two type in your name: ";
	player2.read_name();
	while (player1.get_name() == player2.get_name())
	{
		std::cout << "Player two your name is not unique! \nType in a new name: ";
		player2.read_name();
	}

	// maximum rounds
	std::cout << "Maximum rounds: ";
//	stats.max_rounds_init();

	game = COUNTDOWN;
}

void countdown()
{
	std::cout << "\nRound starts in: \n";
	delay(1000);
	std::cout << "3\n";
	delay(1000);
	std::cout << "2\n";
	delay(1000);
	std::cout << "1\n";
	delay(1000);
	std::cout << "GO!\n";

	game = WAIT_FOR_SIGNAL;
}

void wait_for_signal()
{
	// button reset
	button_pl1.buttonISR_reset();
	button_pl2.buttonISR_reset();

	// time measuring
	int random = rand() % 10000000 + 5000000; // from 5 to 10sec
	now = std::chrono::system_clock::now().time_since_epoch();
	start_time_us = std::chrono::duration_cast<std::chrono::microseconds>(now).count();
	delta = std::chrono::duration_cast<std::chrono::microseconds>(now).count() - start_time_us;

	while ((delta < random) && (button_pl1.get_button() == 0) && (button_pl2.get_button() == 0))
	{  // MFA avoid busy waiting
		now = std::chrono::system_clock::now().time_since_epoch();
		delta = std::chrono::duration_cast<std::chrono::microseconds>(now).count() - start_time_us;
	}

	// did player 1 press the button before red light?
	if ((button_pl1.get_button() == 1) && (button_pl2.time_point() == 0))
	{
		led_pl1.turn_on(LED_PL1);
		stats.current_round_cnt_up();
		stats.won_games_pl2_cnt();
		game = STATS;
	}
	if ((button_pl1.get_button() == 1) && (button_pl1.time_point() < button_pl1.time_point()))
	{
		led_pl1.turn_on(LED_PL1);
		stats.current_round_cnt_up();
		stats.won_games_pl2_cnt();
		game = STATS;
	}

	// did player 2 press the button before red light?
	if ((button_pl2.get_button() == 1) && (button_pl1.time_point() == 0))
	{
		led_pl1.turn_on(LED_PL2);
		stats.current_round_cnt_up();
		stats.won_games_pl1_cnt();
		game = STATS;
	}
	if ((button_pl2.get_button() == 1) && (button_pl2.time_point() < button_pl1.time_point()))
	{
		led_pl1.turn_on(LED_PL2);
		stats.current_round_cnt_up();
		stats.won_games_pl1_cnt();
		game = STATS;
	}


	if (game == WAIT_FOR_SIGNAL)
		game = SIGNAL;
}
void signal()
{
	// button reset
	button_pl1.buttonISR_reset();
	button_pl2.buttonISR_reset();

	// turn on the signal led
	led_signal.turn_on(LED_SIG);

	now = std::chrono::system_clock::now().time_since_epoch();
	start_time_us = std::chrono::duration_cast<std::chrono::microseconds>(now).count();
	delta = std::chrono::duration_cast<std::chrono::microseconds>(now).count() - start_time_us;

	// wait till button is pressed or 3 seconds passed
	while ((button_pl1.get_button() == 0) && (button_pl2.get_button() == 0))
	{
		now = std::chrono::system_clock::now().time_since_epoch();
		delta = std::chrono::duration_cast<std::chrono::microseconds>(now).count() - start_time_us;

		if (delta > 3000000)
		{
			std::cout << "\nTIME OUT\n";
			led_signal.turn_off(LED_SIG);
			game = COUNTDOWN;
			break;
		}
		delay(1);
	}


	// Player1 
	if ((button_pl1.get_button() == 1) && (button_pl2.time_point() == 0))
	{
		led_pl1.turn_on(LED_PL1);
		stats.current_round_cnt_up();
		stats.won_games_pl1_cnt();
	}
	if ((button_pl1.get_button() == 1) && (button_pl1.time_point() < button_pl2.time_point()))
	{
		led_pl1.turn_on(LED_PL1);
		stats.current_round_cnt_up();
		stats.won_games_pl1_cnt();
	}

	// Player2
	if ((button_pl2.get_button() == 1) && (button_pl1.time_point() == 0))
	{
		led_pl1.turn_on(LED_PL2);
		stats.current_round_cnt_up();
		stats.won_games_pl2_cnt();
	}
	if ((button_pl2.get_button() == 1) && (button_pl2.time_point() < button_pl1.time_point()))
	{
		led_pl1.turn_on(LED_PL2);
		stats.current_round_cnt_up();
		stats.won_games_pl2_cnt();
	}

	if (game == SIGNAL)
		game = STATS;
}

void stats1()
{
	delay(3000);
	led_pl1.turn_off(LED_PL1);
	led_pl2.turn_off(LED_PL2);
	led_signal.turn_off(LED_SIG);

	button_pl1.buttonISR_reset();
	button_pl2.buttonISR_reset();

	std::cout << "\n" << stats.rounds_left() << " Rounds left.\n";
	std::cout << "Won games " << player1.get_name() << ": " << stats.won_games_pl1() << "\n";
	std::cout << "Won games " << player2.get_name() << ": " << stats.won_games_pl2() << "\n";
	delay(4000);


	if ((stats.won_games_pl1() > (stats.max_rounds() / 2)) || (stats.won_games_pl2() > (stats.max_rounds() / 2)) || (stats.rounds_left() == 0))
	{
		game = RESULT;

		// winner blinks for 5 seconds
		if (stats.won_games_pl1() > stats.won_games_pl2())
		{
			for (int s = 0; s < 25; s++)
			{
				led_pl1.turn_on(LED_PL1);
				delay(200);
				led_pl1.turn_off(LED_PL1);
				delay(200);
			}
		}
		else if (stats.won_games_pl1() < stats.won_games_pl2())
		{
			for (int s = 0; s < 25; s++)
			{
				led_pl1.turn_on(LED_PL2);
				delay(200);
				led_pl1.turn_off(LED_PL2);
				delay(200);
			}
		}
	}
	else
		game = COUNTDOWN;
}
void result()
{
	// who won
	if (stats.won_games_pl1() > stats.won_games_pl2())
	{
		std::cout << player1.get_name() << " won the game!\n";
	}
	else if (stats.won_games_pl1() < stats.won_games_pl2())
		std::cout << player2.get_name() << " won the game!\n";
	else
		std::cout << "Draw\n";

	// choose between new game and quit
	int new_game = 10;
	std::cout << "Type in 1 for new game, or 2 to quit the game. : ";
	std::cin >> new_game;

	while ((new_game < 1) || (new_game > 2))
	{
		std::cout << "No correct input!\n Type in new number: ";
		std::cin >> new_game;
	}
	if (new_game == 1)
	{
		game = START;
		stats.stats_reset();
	}
	if (new_game == 2)
		game = FALSE;
}

void init_main()
{
	wiringPiSetup();

	// initialize buttons 
	button_pl1.init(BUTTON_PL1);
	button_pl2.init(BUTTON_PL2);

	// interrupt enable
	wiringPiISR(BUTTON_PL1, INT_EDGE_FALLING, &ISR1);
	wiringPiISR(BUTTON_PL2, INT_EDGE_FALLING, &ISR2);

	// turn off all lights
	led_pl1.turn_off(LED_PL1);
	led_pl2.turn_off(LED_PL2);
	led_signal.turn_off(LED_SIG);

	// variable for state machine
	int game = START;
}

void pin_check()
{
	while(pin_check_end)
	{
		// pins to check if assigned
		std::cout << "+++ PIN-CHECK +++ \n";
		std::cout << "Type the pin you want to check or type 0 (zero) to start with the Game: ";
		pin_control.read_pin();
		if(pin_control.get_pin() == 0)
			pin_check_end = false;
		else
		{
			for (int cnt = 0; cnt < sizeof(pin_array); cnt++)
			{
				if (pin_control.get_pin() == pin_array[cnt])
					std::cout << "Pin " << pin_control.get_pin() << " is ALREADY assigned!\n";

				else
					std::cout << "Pin " << pin_control.get_pin() << " is NOT assigned!\n";
			}
		}
	}
}