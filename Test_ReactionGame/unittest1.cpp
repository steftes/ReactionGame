#include "stdafx.h"
#include "CppUnitTest.h"
#include "/Users/Stefan Teschl/OneDrive - FH JOANNEUM/FH-Joanneum Semester 4/OSD/ReactionGame/ReactionGame/GameStatistic.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

Game_statistic stats;

namespace Test_ReactionGame
{		
	
	TEST_CLASS(UnitTest1_Stats)
	{
	public:
		
		TEST_METHOD(TestMethod1_Initial_Conditions)
		{
			// members must be zero, set by default constructor
			Assert::AreEqual(0, stats.get_current_round());
			Assert::AreEqual(0, stats.get_max_rounds());
			Assert::AreEqual(0, stats.get_rounds_left());
			Assert::AreEqual(0, stats.get_won_games_pl1());
			Assert::AreEqual(0, stats.get_won_games_pl2());
		}

		TEST_METHOD(TestMethod2_Count_Up)
		{
			// does it count up?
			stats.current_round_cnt_up();
			stats.won_games_pl1_cnt_up();
			stats.won_games_pl2_cnt_up();

			Assert::AreEqual(1, stats.get_current_round());
			Assert::AreEqual(1, stats.get_won_games_pl1());
			Assert::AreEqual(1, stats.get_won_games_pl2());
		}

		TEST_METHOD(TestMethod3_Rounds_Init)
		{
			// init maximum rounds
			stats.max_rounds_init(4);
			Assert::AreEqual(4, stats.get_max_rounds());
		}

		TEST_METHOD(TestMethod3_Reset)
		{
			// reset everything 
			stats.current_round_cnt_up();
			stats.won_games_pl1_cnt_up();
			stats.won_games_pl2_cnt_up();
			stats.max_rounds_init(4);

			stats.stats_reset();

			Assert::AreEqual(0, stats.get_current_round());
			Assert::AreEqual(0, stats.get_max_rounds());
			Assert::AreEqual(0, stats.get_rounds_left());
			Assert::AreEqual(0, stats.get_won_games_pl1());
			Assert::AreEqual(0, stats.get_won_games_pl2());
		}

		TEST_METHOD(TestMethod3_Rounds_Left)
		{
			// is the calculation of rounds_left right? 
			stats.current_round_cnt_up();
			stats.current_round_cnt_up();
			stats.current_round_cnt_up();
			stats.max_rounds_init(4);

			Assert::AreEqual(1, stats.get_rounds_left());
		}
	};
}
