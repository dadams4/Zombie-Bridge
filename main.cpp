/* Daniel Adams
   CPSC 340
   main.cpp 
*/
#include <iostream>
#include <cstdlib>
#include "Game.h"
#include "linked_list.h"
#include "single_node.h"

using namespace std;

int main(void)
{
	Game game;
	system("clear");
	bool playAgain = true;
	char choice;
	bool validInput = false;
	do{
		game.displayInstructions();
		game.Play();
		cout<<"Do you wish to play again? Type 'y' for yes or 'n' for no: "<<endl; 
		while(!validInput)
		{
			if(cin.peek() == 'y' || cin.peek() == 'n')
			{
				cin>>choice;
				if(choice == 'n')
					playAgain = false;

				validInput = true;
			}
			else
			{
				continue;
			}
		}
	}while(playAgain);
	return 0;
}

