/***
 * AsciiCraft
 * ASCII-based open-source platform game engine
 *
 * Using Pi6 Engine Code
 *
 * @version 0.03
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

int CursorX = 10;
int CursorY = 10;

// Game config
const char* GameTitle = "AsciiCraft";

// Game Map
 // Notes:
 // No map generation, yet.
 // No side-scrolling camera system yet, so, basically a map with the screen size.
char map[18][59] = {"                                                          ",
					"                                                          ",
					"                                                          ",
					"                                                          ",
					"                                                          ",
					"                                   LLLLL                  ",
					"                                 LLLLLLLLL                ",
					"                                LLLLLLLLLLL               ",
					"                                  LLLLLLL                 ",
					"                                     T                    ",
					"                                     T                    ",
					"                                     T                    ",
					"                                     T                    ",
					"                 GGGGGGG  GGGGGG  GGGGGGGG                ",
					"                GDDDDDDDGGDDDDDDGGDDDDDDDDG               ",
					"               GDDDDDDDDDDDDDDDDDDDDDDDDDDDG              ",
					"GGGGGGGGGGGGGGGDDDDDDDDDDDDDDDDDDDDDDDDDDDDDGGGGGGGGGGGGGG"};

/* Main engine code */
void MapRender();
void PlayerRender();
void CursorRender();
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
				case 'S': //Stone
					SetDrawCoord(j,i);
					 SetEntityColor(7);
					 cout <<(char)219;
				break;
				
				case 'D': //Dirt
					SetDrawCoord(j,i);
					 SetEntityColor(6);
					 cout <<(char)219;
				break;
				
				case 'G': //Grass
					SetDrawCoord(j,i);
					 SetEntityColor(98);
                     cout << (char)223;
				break;
				
				case 'L': //Leaves
					SetDrawCoord(j,i);
					 SetEntityColor(162);
					 cout << (char)178;
				break;
				
				case 'T': //Trunk
					SetDrawCoord(j,i);
					 SetEntityColor(134);
					 cout << (char)178;
				break;
			}
		}
	}
}

void PlayerRender()
{
	SetDrawCoord(PlayerHeadX, PlayerHeadY);
	 SetEntityColor(104);
	 cout << (char)191;
	
	SetDrawCoord(PlayerHeadX, PlayerHeadY+1);
	 SetEntityColor(186);
	 cout << (char)223;
	
	SetEntityColor(0); 
}

void CursorRender()
{
	SetDrawCoord(CursorX, CursorY);
	 SetEntityColor(7);
	 cout << (char)006;
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
int JumpStep = 0;

void ParseKeys()
{
	switch(Key)
	{
		case 101: // E
			// Not implemented yet
		break;
		
		case 119: // W
			if(map[PlayerHeadY-1][PlayerHeadX] != ' ') break;
			
			IsJumping = 1;

			while(IsJumping)
			{
				if(JumpStep == 2)
				{
					IsJumping = 0;
					JumpStep = 0;
					break;
				}
				
				SetDrawCoord(PlayerHeadX, PlayerHeadY);
				 cout << " ";
				SetDrawCoord(PlayerHeadX, PlayerHeadY+1);
				 cout << " ";
			 
				PlayerHeadY--;
					
				PlayerRender();

				JumpStep++;
				Sleep(50);

			}
		break;
		
		case 97: // A
			if(map[PlayerHeadY][PlayerHeadX-1] != ' ' || map[PlayerHeadY+1][PlayerHeadX-1] != ' ') break;
			
			SetDrawCoord(PlayerHeadX, PlayerHeadY);
			 cout << " ";
			SetDrawCoord(PlayerHeadX, PlayerHeadY+1);
			 cout << " ";
			 
			PlayerHeadX--;
			 
			PlayerRender();
		break;
		
		case 100: // D
			if(map[PlayerHeadY][PlayerHeadX+1] != ' ' || map[PlayerHeadY+1][PlayerHeadX+1] != ' ') break;
			
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
	//system("COLOR 30");
	
	MapRender();
	PlayerRender();
	CursorRender();
	
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
		
	SetDrawCoord(80, 0);
}

/* Game boot */
int main()
{
	SetDrawCoord(1, 0);
	
	SetConsoleTitle(GameTitle);
	SetEntityColor(7);
	 cout << "Indev 3";

	while(Key != 113)
	{
		DoRenderStep();
		
		Sleep(50);
	}
	return 0;
}
