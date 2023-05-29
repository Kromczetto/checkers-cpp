#pragma once


class Counter
{
	int countedMoveWhite;
	int countedMoveBlack;
	int topS;

public:
	Counter();

	void inWhite();
	void inBlack();

	int returnCountedMoveWhite();
	int returnCountedMoveBlack();

	void saveScore();
	
};

