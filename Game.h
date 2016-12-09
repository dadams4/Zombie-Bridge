/* Daniel Adams
   CPSC 340
   Game.h
*/

#ifndef GAMEH
#define GAMEH
#include "linked_list.h"
#include "single_node.h"
#include <iostream>
#include <string>

using namespace std;

class Game
{
	public:
		/* Default constructor? */
		Game();

		/*Determine if the player has won */
		bool isWon();
		/* Determine if the player has lost */
		bool isLost(const linked_list <string> &east);
		/* Determine if a game is currently being played */
		bool isPlaying();
		/* Set up either side of the board, as well as the location of the lantern */
		void setUp();
		/* Displays the instructions on how to play the game */
		void displayInstructions();
		/* Displays what items are on either side of the gorge */
		void displayStat();

		/* Move a player from one side to the other */
		void transportPeople(linked_list<string> &fromSide, linked_list<string> &toSide);
		
		/* Function that plays the game */
		void Play(); 
	private:
		static const string WEST;//left side of the gorge
		static const string EAST; //right side of the gorge
		static const string  BRIDGE; //obviously the bridge
		static const int INTERN; //time it takes for intern to cross (1)
		static const int LAB; //time it takes for assistant to cross (2)
		static const int JANITOR; //time it takes for the janitor to cross (5)
		static const int PROFESSOR; //time it takes for the professor to cross (10)

		static const int NUM_PIECES = 6; //6 Pieces: INTERN, LAB, JANITOR, PROFESSOR, LANTERN
		static const string GAME_PIECES[NUM_PIECES]; //What pieces are on the bridge currently
		
		linked_list<string> westSide; //West side of the gorge
		linked_list<string> eastSide; //East side of the gorge
		linked_list<string> bridge; //The bridge itself
	
		string lightLocation; //Which side of the bridge that the lantern is on
		string whoIsHoldingLight; //Which game piece is holding the lantern
		int runningTime; //I'm assuming this is how much time has been spent crossing the bridge by the various pieces

};
#endif
