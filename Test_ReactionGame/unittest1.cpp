#include "stdafx.h"
#include "CppUnitTest.h"
#include "../ReactionGame/GameStatistic.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test_ReactionGame
{		
	
	TEST_CLASS(UnitTest1_Stats)
	{
	public:
		
		TEST_METHOD(TestMethod1_Initial_Conditions)
		{ // MFA: this is a good test for testing intial conditions
			Game_statistic stats;
			// members must be zero, set by default constructor
			Assert::AreEqual(0, stats.get_current_round());
			Assert::AreEqual(0, stats.max_rounds());
			Assert::AreEqual(0, stats.rounds_left());
			Assert::AreEqual(0, stats.won_games_pl1_cnt());
			Assert::AreEqual(0, stats.won_games_pl2_cnt());
		}

		TEST_METHOD(TestMethod2_Count_Up)
		{ // MFA this one should be split into three tests, one for testing each cnt_up-method
			Game_statistic stats;
			// does it count up?
			stats.current_round_cnt_up();
			stats.won_games_pl1_cnt_up();
			stats.won_games_pl2_cnt_up();

			Assert::AreEqual(1, stats.get_current_round());
			Assert::AreEqual(1, stats.won_games_pl1_cnt());
			Assert::AreEqual(1, stats.won_games_pl2_cnt());
		}

		TEST_METHOD(TestMethod3_Rounds_Init)
		{ // MFA this is a good test! small and testing one thing and one thing only
			Game_statistic stats;
			// init maximum rounds
			stats.max_rounds_init(4);
			Assert::AreEqual(4, stats.max_rounds());
		}

		TEST_METHOD(TestMethod3_Reset)
		{ // MFA this is a good test, too. the correct functionality of the cnt_up-methods has been tested already, the reset is now tested
			Game_statistic stats;
			// reset everything 
			stats.current_round_cnt_up();
			stats.won_games_pl1_cnt_up();
			stats.won_games_pl2_cnt_up();
			stats.max_rounds_init(4);

			stats.stats_reset();

			Assert::AreEqual(0, stats.get_current_round());
			Assert::AreEqual(0, stats.max_rounds());
			Assert::AreEqual(0, stats.rounds_left());
			Assert::AreEqual(0, stats.won_games_pl1_cnt());
			Assert::AreEqual(0, stats.won_games_pl2_cnt());
		}

		TEST_METHOD(TestMethod3_Rounds_Left)
		{ // MFA: the sequence of operations seems strange to me. I would have expected init first, then the cnt_ups. You should also do Asserts after each cnt_up (which is difficult with your sequence of operations)
			Game_statistic stats;
			// is the calculation of rounds_left right? 
			stats.current_round_cnt_up();
			stats.current_round_cnt_up();
			stats.current_round_cnt_up();
			stats.max_rounds_init(4);

			Assert::AreEqual(1, stats.rounds_left());
		}
	};
}
