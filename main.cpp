/***
 * AsciiCraft
 * ASCII-based open-source platform game engine
 *
 * Using Pi6 Engine Code
 *
 * @version 0.01
 * @copyright GPL (c) 2007
**/

// Notes:
// Work on movement physics pretty much done!
// Now started working on mouse tracking, camera movement and water physics.

#include <iostream>
using namespace std;

#include <windows.h>
#include <conio.h>
#include <stdlib.h>

// System variables
int Key;

int PlayerHeadX = 0;
int PlayerHeadY = 0;

// Game config
const char* GameTitle = "AsciiCraft - Indev 0.1 (0.01)";

// Game Map
 // Notes:
 // No map generation, yet.
 // No side-scrolling camera system yet, so, basically a map with the screen size.
char map[18][59] = {"                                                          ",
					"                                                          ",
					"                                                          ",
					"                                                          ",
					"                                                          ",
					"                                                          ",
					"                                                          ",
					"                                                          ",
					"                                                          ",
					"                                                          ",
					"                                                          ",
					"                                                          ",
					"                                                          ",
					"                 ### ###  ###   ###    ###                ",
					"                #                                         ",
					"               #                                          ",
					"##########################################################"};

/* Main engine code */
void MapRender();
void PlayerRender();
void SetDrawCoord(int cX, int cY);
void SetEntityColor(int cO);
void ParseMovement();
void DoRenderStep();

void MapRender()
{
	SetDrawCoord(0, 0);
	
	for(int i = 0; i < 18; i++)
	{
		for(int j = 0; j < 58; j++)
		{
			switch(map[i][j])
			{
				case '#':
					SetDrawCoord(j,i);
                     cout << (char)219;
				break;
			}
		}
	}
}

void PlayerRender()
{
	SetDrawCoord(PlayerHeadX, PlayerHeadY);
	 SetEntityColor(6);
	 cout << (char)001;
	
	SetDrawCoord(PlayerHeadX, PlayerHeadY+1);
	 SetEntityColor(11);
	 cout << (char)219;
	
	SetEntityColor(0); 
}

void SetDrawCoord(int cX, int cY)
{
	COORD DrawPos;
	DrawPos.X = cX;
	DrawPos.Y = cY;
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), DrawPos);
}

void SetEntityColor(int cO)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cO);
}

int IsJumping = 0;
int i;

void ParseKeys()
{
	switch(Key)
	{
		case 101: // E
			// Not implemented yer
		break;
		
		case 119: // W
			if(map[PlayerHeadY-1][PlayerHeadX] == '#') break;
			
			IsJumping = 1;
			
			for(i=0;i<=2;i++)
			{
				if(i == 2)
				{
					IsJumping = 0;
				}
				
				SetDrawCoord(PlayerHeadX, PlayerHeadY);
				 cout << " ";
				SetDrawCoord(PlayerHeadX, PlayerHeadY+1);
				 cout << " ";
			 
				PlayerHeadY--;
			 
				PlayerRender();
				
				Sleep(100);
			}
		break;
		
		case 115: // S
			// Not implemented yet
		break;
		
		case 97: // A
			if(map[PlayerHeadY][PlayerHeadX-1] == '#' || map[PlayerHeadY+1][PlayerHeadX-1] == '#') break;
			
			SetDrawCoord(PlayerHeadX, PlayerHeadY);
			 cout << " ";
			SetDrawCoord(PlayerHeadX, PlayerHeadY+1);
			 cout << " ";
			 
			PlayerHeadX--;
			 
			PlayerRender();
		break;
		
		case 100: // D
			if(map[PlayerHeadY][PlayerHeadX+1] == '#' || map[PlayerHeadY+1][PlayerHeadX+1] == '#') break;
			
			SetDrawCoord(PlayerHeadX, PlayerHeadY);
			 cout << " ";
			SetDrawCoord(PlayerHeadX, PlayerHeadY+1);
			 cout << " ";
			 
			PlayerHeadX++;
			 
			PlayerRender();
		break;
	}
}

void DoRenderStep()
{
	if(IsJumping == 0)
	{
		if(map[PlayerHeadY+2][PlayerHeadX] == ' ')
		{
			SetDrawCoord(PlayerHeadX, PlayerHeadY);
			 cout << " ";
			SetDrawCoord(PlayerHeadX, PlayerHeadY+1);
			 cout << " ";

			PlayerHeadY = PlayerHeadY + 1;
		 
			PlayerRender();
		}
	} //
	
	if(kbhit())
	{
		Key = getch();
		ParseKeys();
	}
		
	SetDrawCoord(79, 0);
	Sleep(50);
}

/* Game boot */
int main()
{
	SetConsoleTitle(GameTitle);
	
	MapRender();
	PlayerRender();
	
	while(Key != 113)
	{
		DoRenderStep();
	}
	return 0;
}
