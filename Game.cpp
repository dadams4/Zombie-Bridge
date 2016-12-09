/* Daniel Adams
   CPSC 340
   Game.cpp
*/
#ifndef GAMECPP
#define GAMECPP

#include "linked_list.h"
#include "single_node.h"
#include "Game.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;

/* Intialize Board */
const string Game::WEST = "west";
const string Game::EAST = "east";
const string Game::BRIDGE = "bridge";
const string Game::GAME_PIECES[NUM_PIECES] = {"intern", "assistant", "janitor","professor", "lantern", "zombies"};

/* Initialize Pieces */
const int Game::INTERN = 1;
const int Game::LAB = 2;
const int Game::JANITOR = 5;
const int Game::PROFESSOR = 10;

Game::Game()
{
	lightLocation = WEST;
	whoIsHoldingLight = "No one";
//	linked_list<string> westSide;
//	linked_list<string> eastSide;
	runningTime = 0;
}

bool Game::isWon() 
{
	if(eastSide.length() == 1 && runningTime == 17)
	{
		cout<<"You've won!"<<endl;
		return true;
	}
	else
		return false;	
}

bool Game::isLost(const linked_list <string> &east) 
{
	if(runningTime > 17)
	{
		cout<<"You've lost!"<<endl;
		return true;
	}
	else
		return false;
}

bool Game::isPlaying() 
{
	if(!isWon() && !isLost(eastSide))
		return true;
	else
		return false;

}

void Game::setUp()
{
	//if(westSide.length() != 0 && eastSide.length() != 0)
	//{
		westSide.initList();	
		eastSide.initList();
		bridge.initList();
	//}
	for(int i = 0; i < NUM_PIECES - 2; i++)
	
		westSide.InsertInOrder(GAME_PIECES[i]);
	
}

void Game::displayInstructions() 
{
	/* I know these could all be one cout, but it looks cleaner with multiple */
	cout<<endl;
	cout<<"Welcome to Zombie Bridge!  You are currently being chased by zombies, but have reached a bridge over which you can escape. "<<endl;
	cout<<"You must ensure all four members of your group make it from the west side of the bridge to the east side safely."<<endl;  
	cout<<"The intern can cross the bridge in 1 minute, the lab assistant can cross in 2 minutes,"<<endl;
	cout<<"the janitor can cross in 5 minutes, and the professor can cross in 10 minutes."<<endl;  
	cout<<"Everyone must cross in 17 or fewer minutes, or you will lose the game. "<<endl;
	cout<<"There are some additional rules:"<<endl;
	
	cout<<"1: No more than two characters can cross the bridge at one time."<<endl;
	cout<<"2: Anyone crossing must hold the lantern, or cross with someone holding the lantern."<<endl;
	cout<<"3: Characters can safely wait on either of the bridge in the dark, so long as less than 17 game minutes have passed."<<endl;
	cout<<"4: To win, every character must cross the bridge in under 17 minutes (before the zombies arrive)."<<endl;
	cout<<"5: If the zombies arrive while a character is crossing the bridge, the game will still be lost, as the extra weight of the zombies collapses the bridge."<<endl;
	cout<<"6: If a character attempts to travel across the bridge without the lantern, they will lose their footing and fall to their death, resulting in a loss. (This is not allowed to occur, however)."<<endl;
	cout<<"Try to get everyone safely across.  Good luck!"<<endl;
}

void Game::displayStat() 
{
	cout<<endl;
	cout<<"The following characters are on the west side of the bridge: "<<endl;
	if(!westSide.IsEmpty())
	{
		westSide.PrintAll();
		cout<<endl;
	}
	else
		cout<<"None!"<<endl;

	cout<<endl;
	cout<<"The following characters are on the east side of the bridge: "<<endl;
	if(!eastSide.IsEmpty())
	{
		eastSide.PrintAll();
		cout<<endl;
	}
	else
		cout<<"None!"<<endl;

	cout<<endl;
	cout<<"The following characters are currently on the bridge: "<<endl;
	if(!bridge.IsEmpty())
	{
		bridge.PrintAll();
		cout<<endl;
	}
	else
		cout<<"None!"<<endl;

	cout<<endl;
	cout<<"The light is being held by: "<<whoIsHoldingLight<<endl;
	cout<<"Time elapsed: "<<runningTime<<endl;
	cout<<"Time remaining: "<<17 - runningTime<<endl;
	cout<<endl;
}

void Game::transportPeople(linked_list <string> &fromSide, linked_list<string> &toSide)
{
	/* Variables */
	int numToCross = 0;
	bool successfulCrossing = false;
	bool validInput = false;
	int charToCross1, charToCross2;
	string validC1, validC2;
	/* Choose number of character to cross to cross */
	cout<<"Enter number of characters to cross: "; //add error checking
	while(!validInput)
	{ 
		if(cin.peek() == '1' || cin.peek() == '2'|| cin.peek() > '9')
		{
			cin>>numToCross;
			cin.ignore();
			validInput = true;
		}
		else
		{
			cout<<"Invalid input"<<endl;
			cin.ignore();
			continue;
		}
	}
	validInput = false;
	/* Go until the player successfully cross the bridge with some characters.  Helps with error checking */
	while(!successfulCrossing)
	{
		
		if(numToCross == 1)
		{
			numToCross = 0;

			cout<<"Choose a character that you wish to have cross. "<<endl;
			cout<<"Options: 1. for the intern, 2. for the assistant, 3. for the janitor, 4. for the professor"<<endl;
			
			/* Error Checking */
			while(!validInput)
			{ 
				cout<<"Enter your choice: "; 
				if(cin.peek() == '1' || cin.peek() == '2' || cin.peek() == '3' || cin.peek() == '4')
				{
					
					cin>>charToCross1;
					cin.ignore();
					if(charToCross1 == 1)
						validC1 = "intern";
					else if(charToCross1 == 2)
						validC1 = "assistant";
					else if(charToCross1 == 3)
						validC1 = "janitor";
					else if(charToCross1 == 4)
						validC1 = "professor";

					if(!fromSide.Search(validC1))
					{
						cout<<"That character is currently unable to traverse the bridge"<<endl;
						continue;
					}
					else
					{
						whoIsHoldingLight = validC1;
						validInput = true;
					}
				}
				else
				{
					cout<<"Invalid choice"<<endl;
					cin.ignore();
					continue;
				}
			}
			
			/* Check if the character that the player wishes to move is on fromSide */
			if(fromSide.Search(validC1))
			{

				/* Remove the character and then insert it into bridge */
				fromSide.Remove(validC1);
				bridge.InsertInOrder(validC1);
				if(validC1.compare("intern") == 0)
					runningTime++;
				else if(validC1.compare("assistant") == 0) 
					runningTime+=2;
				else if(validC1.compare("janitor") == 0)
					runningTime+=5;
				else if(validC1.compare("professor") == 0)
					runningTime+=10;

				/* Now we make sure that our player is not out of time */
				displayStat();

				if(runningTime <= 17)
				{
					toSide.InsertInOrder(validC1);
					bridge.Remove(validC1);
					fromSide.Remove(validC1);
				}
				successfulCrossing = true;
			}
			else
				cout<<"That character is not able to cross at this time"<<endl;

		}

		else if(numToCross == 2)
		{
			numToCross = 0;

			cout<<"Choose two characters that you wish to have cross. "<<endl;
			cout<<"Options: 1. for the intern, 2. for the assistant, 3. for the janitor, 4. for the professor"<<endl;
			
			while(!validInput)
			{
				cout<<"Enter your first choice: "; //add error checking
				if(cin.peek() == '1' || cin.peek() == '2' || cin.peek() == '3' || cin.peek() == '4')
				{
					cin>>charToCross1;
					cin.ignore();
					if(charToCross1 == 1)
						validC1 = "intern";
					else if(charToCross1 == 2)
						validC1 = "assistant";
					else if(charToCross1 == 3)
						validC1 = "janitor";
					else if(charToCross1 == 4)
						validC1 = "professor";

				}
				else
				{
					cout<<"Invalid input."<<endl;
					cin.ignore();
					continue;
				}

				cout<<"Enter your second choice: "; //add error checking

				if(cin.peek() == '1' || cin.peek() == '2' || cin.peek() == '3' || cin.peek() == '4')
				{
					cin>>charToCross2;
					cin.ignore();
					if(charToCross2 == 1)
						validC2 = "intern";
					else if(charToCross2 == 2)
						validC2 = "assistant";
					else if(charToCross2 == 3)
						validC2 = "janitor";
					else if(charToCross2 == 4)
						validC2 = "professor";
				}
				else
				{
					cout<<"Invalid input."<<endl;
					cin.ignore();
					continue;
				}

				if(!fromSide.Search(validC1) || !fromSide.Search(validC2))
				{
					cout<<"One or both of the selected characters are currently unable to traverse the bridge."<<endl;
					continue;
				}
				else					
				{
					whoIsHoldingLight = validC1;
					validInput = true;
				}
			}
				


			/* Check that both of the characters that the player wishes to move are on fromSide */
			if(fromSide.Search(validC1) && fromSide.Search(validC2))
			{

				/* Variables to hold the times of characters chosen by the player */
				int char1RunTime = 0;
				int char2RunTime = 0;

				/* Removing from fromSide */
				fromSide.Remove(validC1);
				fromSide.Remove(validC2);

				/* Adding to the bridge */
				bridge.InsertInOrder(validC1);
				bridge.InsertInOrder(validC2);

				/* Decide how to increment the running time */
				if(validC1.compare("intern") == 0) 
					char1RunTime++;
				if(validC2.compare("intern") == 0 )
					char2RunTime++;

				if(validC1.compare("assistant") == 0)
					char1RunTime+=2;
				if(validC2.compare("assistant") == 0)
					char2RunTime+=2;

				if(validC1.compare("janitor") == 0)
					char1RunTime+=5; 
				if(validC2.compare("janitor") == 0)
					char2RunTime+=5; 

				if(validC1.compare("professor") == 0)
					char1RunTime+=10;
				if(validC2.compare("professor") == 0)
					char2RunTime+=10;

				/* Ensure we don't add too much time */
				if(char1RunTime >= char2RunTime)
					runningTime = runningTime + char1RunTime;
				else
					runningTime = runningTime + char2RunTime;

				//char1RunTime = 0;
				//char2RunTime = 0;

				/* Make sure that the game has not been lost after the previous move */
				if(runningTime <= 17)
				{
					/* Go ahead and clear the bridge off since the game isn't lost */
					bridge.Remove(validC1);
					bridge.Remove(validC2);	
					
					/* Now we can insert on the desired side */
					toSide.InsertInOrder(validC1);
					toSide.InsertInOrder(validC2);
					
				}
				if(isWon())
				{
					cout<<"Congratulations, you have successfully rescued every character!"<<endl;
					return;
				}
				if(isLost(eastSide))
				{
					cout<<"Unfortunately, you have lost.  Better luck next time!"<<endl;
					return;
				}				
				successfulCrossing = true;
				
			}
		}
	}
}

void Game::Play()
{
	setUp();
	displayStat();
	string lanternSide = "west";		

	while(!isLost(eastSide) && !isWon())
	{
		if(lanternSide.compare("west") == 0)
		{
			transportPeople(westSide,eastSide);
			lanternSide = "east";		
		}
		else if(lanternSide.compare("east") == 0)
		{
			transportPeople(eastSide,westSide);	
			lanternSide = "west";
		}
		system("clear");
		displayStat();
	}
runningTime = 0;
whoIsHoldingLight = "No one.";		
}
#include "Game.cpp"
#endif
