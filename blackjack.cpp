#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;


int deal (int size, int deck[])
{
	return deck [size - 1];
}

int newDeck (int size, int deck [])
{
	for (int i = 0; i < 10; i++)
	{
		deck[i] = i + 1;
	}
	for (int i = 10; i < 13; i++)
	{
		deck[i] = 10;
	}
	
	for (int i = 13; i < 23; i++)
	{
		deck[i] = i - 12;
	}
	for (int i = 23; i < 26; i++)
	{
		deck[i] = 10;
	}
	
	for (int i = 26; i < 36; i++)
	{
		deck[i] = i - 25;
	}
	for (int i = 36; i < 39; i++)
	{
		deck[i] = 10;
	}
	
	for (int i = 39; i < 49; i++)
	{
		deck[i] = i - 38;
	}
	for (int i = 49; i < 52; i++)
	{
		deck[i] = 10;
	}
	
	//shuffle() implement algorithm
	for (int i = size - 1; i >= 0; i--)
	{
		int randNum = 1 + rand() / (RAND_MAX / ( (size - 1) - 1 + 1) + 1);
		int temp = deck[i];
		deck[i] = deck [randNum];
		deck[randNum] = temp;
		
	}
	
}







int main (const int argc, const char* const argv[])
{
    srand ((unsigned int)time(NULL));   
	//an array of 52 cards: ace (1 or 11), 2 .. 10, 10, 10, 10
	int size = 52;
	int deck [size];
	newDeck (size,deck);
	
	
	//QUESTION 4
	
	
	for (int i = 10; i < 21; i++)
	{
		double threshold = i;
		double sum = 0;
		double track = 0;
		double checkSum = 0;
		
		if ((threshold == 10) || (threshold == 11) || (threshold == 12))
		{
			track = 0;
		}
		else
		{
			for (int j = 0; j < 10000; j++)
			{
				sum = 0;
				checkSum = 0;
				
				//dealing cards to player until threshold is reached
				for (int i = 0; i <= threshold; i++)
				{
					checkSum = checkSum + deal(size, deck);
					
					size--;
					sum = checkSum;
					if ((checkSum > threshold) || (checkSum > 21))
					{
						break;
					}
					
				}
								
				//reshuffling deck if it become empty
				if (size < 0)
				{
					size = 52;
					newDeck (size, deck);
				}
				if (sum > 21)
				{
					track++;
				}
			}
		}
		cout << "Busts for Threshold: " << i << ": " << (track)/10000.00 << endl;
		
		

		
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	//QUESTION 5
	//resetting deck
	size = 52;
	newDeck(size, deck);
	
	int playerWin = 0;
	int playerLoss = 0;
	int playerDraw = 0;
	
	bool checkWin = false;
	
	int runningTotal = 0;
	
	bool betLow = false;
	bool betHigh = false;
	bool betAverage = false;

	double goodDecision = 0;
	double badDecision = 0;
	
	for (int j = 0; j < 10000; j++)
	{
		int sumDealer = 0;
		int sumPlayer = 0;
		
		int checkSumDealer = 0;
		int checkSumPlayer = 0;
		
		checkWin = false;
		
		betLow = false;
		betHigh = false;
		betAverage = false;
		
		runningTotal = 0;
		
		//for dealer
		for (int i = size - 1; i >= 0; i--)
		{
			
			checkSumDealer = checkSumDealer + deal(size, deck);
			
			if ((deal(size, deck) == 2) || (deal(size, deck) == 3) || (deal(size, deck) == 4) || (deal(size, deck) == 5) || (deal(size, deck) == 6))
			{
				runningTotal++;
			}
			else if ((deal(size, deck) == 1) || (deal(size, deck) == 10))
			{
				runningTotal--;
			}
				
				
				
			size--;
			if (checkSumDealer >= 17)
			{
				sumDealer = checkSumDealer;
				break;
			}
			else
			{
				sumDealer = checkSumDealer;
			}
		}
		

		//for players
		for (int i = size - 1; i >= 0; i--)
		{
			checkSumPlayer = checkSumPlayer + deal(size, deck);
			
			if ((deal(size, deck) == 2) || (deal(size, deck) == 3) || (deal(size, deck) == 4) || (deal(size, deck) == 5) || (deal(size, deck) == 6))
			{
				runningTotal++;
			}
			else if ((deal(size, deck) == 1) || (deal(size, deck) == 10))
			{
				runningTotal--;
			}
				
				
			size--;
			if (checkSumPlayer > 21)
			{
				sumPlayer = checkSumPlayer;
				break;
			}
			else
			{
				sumPlayer = checkSumPlayer;
			}
		}

		//CONDITIONS
		if ((sumPlayer == 21) || (sumDealer > 21))
		{
			playerWin++;
			checkWin = true;
		}
		else if ((sumPlayer > 21) || (sumDealer > sumPlayer))
		{
			playerLoss++;
		}
		else if (sumPlayer == sumDealer)
		{
			playerDraw++;
		}
		
		//reshuffle
		if (size < 10)
		{
			size = 52;
			newDeck (size, deck);
			runningTotal = 0;
		}
		
		//betting
		if (runningTotal < 0)
		{
			betLow = true;
		}
		else if (runningTotal > 0)
		{
			betHigh = true;
		}
		else if (runningTotal == 0)
		{
			betAverage = true;
		}

		//decisions
		if ((checkWin == false) && (betLow == true))
		{
			goodDecision++;
		}
		else if ((checkWin == false) && ((betHigh == true)|| (betAverage == true)))
		{
			badDecision++;
		}
		else if ((checkWin == true) && (betLow == true))
		{
			badDecision++;
		}
		else if ((checkWin == true) && ((betHigh == true) || (betAverage == true)))
		{
			goodDecision++;
		}
		
		
	}
	cout << " " << endl;
	cout << "Fraction of good decisions: " << (goodDecision)/1.00 << endl;
	cout << "Fraction of bad decisions: " << badDecision/1.00 << endl;

	

    return 0;

}