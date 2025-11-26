#include"pch.h"
#include "../16_SFML_Games/TetrisPlayer.h"

TEST(TetrisPlayer, CheckPositionFalse)
{
	TetrisPlayer piece;

	shape[0] = { 10, 20 };

	EXPECT_FALSE(piece.check());
}

TEST(TetrisPlayer, CheckPositionTrue)
{
	TetrisPlayer piece;

	shape[0] = { 0, 0 };
	shape[0] = { 9, 19 };

	EXPECT_TRUE(piece.check());
}

TEST(TetrisPlayer, CheckRotate)
{
	TetrisPlayer piece;

	shape[0] = { 0, 0 };

	EXPECT_TRUE(piece.rotatePlayer());
}