#include <wiringPi.h>
#include <iostream>
#include "DummyOutput.h"
#include "IDigitalOutput.h"
#include "DummyInput.h"
#include "IDigitalInput.h"
#include "DummyPlayer.h"
#include "IPlayer.h"
#include "IGameStatistic.h"
#include "DummyGameStatistic.h"
#include <chrono>

// button pins
#define	BUTTON_PL1 15
#define	BUTTON_PL2 16

// led pins
#define	LED_PL1 8
#define	LED_PL2 9
#define	LED_SIG 7

// state machine
#define	START 1
#define	COUNTDOWN 2
#define	WAIT_FOR_SIGNAL 3
#define	SIGNAL 4
#define STATS 5
#define RESULT 6
///


int64_t start_time_us = 0;
auto now = std::chrono::system_clock::now().time_since_epoch();
auto delta = std::chrono::duration_cast<std::chrono::microseconds>(now).count() - start_time_us;

// Output
Dummy_output led_pl1;
Dummy_output led_pl2;
Dummy_output led_signal;

// Input
Dummy_input button_pl1;
Dummy_input button_pl2;

// Player classes
Dummy_player player1;
Dummy_player player2;

// Statistic
Dummy_game_statistic stats;

// Prototypes
void ISR1();
void ISR2();

int main(void)
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

	// game starts
	while (true)
	{
		switch (game)
		{
			case START: 
			{
				// turn all leds off
				led_pl1.turn_off(LED_PL1);
				led_pl2.turn_off(LED_PL2);
				led_signal.turn_off(LED_SIG);

				// player names
				std::cout << "Player one type in your name: ";
				player1.name();
				std::cout << "Player two type in your name: ";
				player2.name();
				while (player1.give_name() == player2.give_name())
				{
					std::cout << "Player two your name is not unique! \nType in a new name: ";
					player2.name();
				}

				// maximum rounds
				std::cout << "Maximum rounds: ";
				stats.max_rounds_init();
				
				game = COUNTDOWN;
				break;
			}

			case COUNTDOWN:
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
				break;
			}

			case WAIT_FOR_SIGNAL:
			{
				// button reset
				button_pl1.buttonISR_reset();
				button_pl2.buttonISR_reset();

				// time measuring
				int random = rand() % 10000000 + 5000000; // from 5 to 10sec
				now = std::chrono::system_clock::now().time_since_epoch();
				start_time_us = std::chrono::duration_cast<std::chrono::microseconds>(now).count();
				delta = std::chrono::duration_cast<std::chrono::microseconds>(now).count() - start_time_us;

				while ((delta < random) && (button_pl1.button() == 0) && (button_pl2.button() == 0))
				{
					now = std::chrono::system_clock::now().time_since_epoch();
					delta = std::chrono::duration_cast<std::chrono::microseconds>(now).count() - start_time_us;
				}

				// did player 1 press the button before red light?
				if ((button_pl1.button() == 1) && (button_pl2.time() == 0))
				{
					led_pl1.turn_on(LED_PL1);
					stats.current_round_cnt_up();
					stats.won_games_pl2_cnt();
					game = STATS;
				}
				if ((button_pl1.button() == 1) && (button_pl1.time() < button_pl1.time()))
				{
					led_pl1.turn_on(LED_PL1);
					stats.current_round_cnt_up();
					stats.won_games_pl2_cnt();
					game = STATS;
				}

				// did player 2 press the button before red light?
				if ((button_pl2.button() == 1) && (button_pl1.time() == 0))
				{
					led_pl1.turn_on(LED_PL2);
					stats.current_round_cnt_up();
					stats.won_games_pl1_cnt();
					game = STATS;
				}
				if ((button_pl2.button() == 1) && (button_pl2.time() < button_pl1.time()))
				{
					led_pl1.turn_on(LED_PL2);
					stats.current_round_cnt_up();
					stats.won_games_pl1_cnt();
					game = STATS;
				}


				if (game == WAIT_FOR_SIGNAL)
					game = SIGNAL;
				break;
			}

			case SIGNAL:
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
				while ((button_pl1.button() == 0) && (button_pl2.button() == 0))
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
				}


				// Player1 
				if ((button_pl1.button() == 1) && (button_pl2.time() == 0))
				{
					led_pl1.turn_on(LED_PL1);
					stats.current_round_cnt_up();
					stats.won_games_pl1_cnt();
				}
				if ((button_pl1.button() == 1) && (button_pl1.time() < button_pl2.time()))
				{
					led_pl1.turn_on(LED_PL1);
					stats.current_round_cnt_up();
					stats.won_games_pl1_cnt();
				}

				// Player2
				if ((button_pl2.button() == 1) && (button_pl1.time() == 0))
				{
					led_pl1.turn_on(LED_PL2);
					stats.current_round_cnt_up();
					stats.won_games_pl2_cnt();
				}
				if ((button_pl2.button() == 1) && (button_pl2.time() < button_pl1.time()))
				{
					led_pl1.turn_on(LED_PL2);
					stats.current_round_cnt_up();
					stats.won_games_pl2_cnt();
				}

				if(game == SIGNAL)
					game = STATS;
				break;
			}

			case STATS:
			{
				delay(3000);
				led_pl1.turn_off(LED_PL1);
				led_pl2.turn_off(LED_PL2);
				led_signal.turn_off(LED_SIG);

				button_pl1.buttonISR_reset();
				button_pl2.buttonISR_reset();

				std::cout << "\n" << stats.rounds_left() << " Rounds left.\n";
				std::cout << "Won games " << player1.give_name()<< ": " << stats.won_games_pl1() << "\n";
				std::cout << "Won games " << player2.give_name()<< ": " << stats.won_games_pl2() << "\n";
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
				break;
			}

			case RESULT:
			{
				// who won
				if (stats.won_games_pl1() > stats.won_games_pl2())
				{
					std::cout << player1.give_name() << " won the game!\n";
				}
				else if (stats.won_games_pl1() < stats.won_games_pl2())
					std::cout << player2.give_name() << " won the game!\n";
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
		}	
	}
	return 0;
}


// interrupt routine
void ISR1()
{
	button_pl1.buttonISR();
}

void ISR2()
{
	button_pl2.buttonISR();
}




