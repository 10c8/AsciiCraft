/***
 * AsciiCraft
 * ASCII-based open-source platform game engine
 *
 * Using Pi6 Engine Code
 *
 * @version 0.07
 * @copyright GPL (c) 2007
**/

// Notes:
// Work on movement physics pretty done!
// Block placing pretty done!
// Block breaking pretty done!
// Working to make the resources finite. :D
// Water physics pretty much done! Just need to make it finite too.
// Falling block physics done!
// Redstone work started!

#include <iostream>
using namespace std;

#include <windows.h>
#include <conio.h>
#include <stdlib.h>

// System variables
int Key;

int PlayerHeadX = 0;
int PlayerHeadY = 37;

int IsJumping = 0;
int JumpStep = 0;

int SelectedBlock = 0;

int CursorX = 4;
int CursorY = 37;
const int WindowX = 80;
const int WindowY = 40;

// Game config
const char* GameTitle = "AsciiCraft - Don't kill the pigs! (nah, kill them)";

// Game Map
 // Notes:
 // No map generation, yet.
 // No side-scrolling camera system yet, so, basically a map with the screen size.
char map[40][80] = {"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"                                                                               ",
					"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG"};

/* Main engine code */
void MapRender();
void PlayerRender();
void CursorRender();
void SetDrawCoord(int cX, int cY);
void SetEntityColor(int cO);
void FallingBlockPhysics(int x, int y, int b);
void LiquidPhysics(int x, int y);
void ParseMovement();
void DoRenderStep();

void MapRender()
{
	SetDrawCoord(0, 0);
	
	for(int i = 0; i < 40; i++)
	{
		for(int j = 0; j < 80; j++)
		{
			switch(map[i][j])
			{
				case 'S': //Stone
					SetDrawCoord(j,i);
					 SetEntityColor(7);
					 cout << (char)219;
				break;
				
				case 'D': //Dirt
					SetDrawCoord(j,i);
					 SetEntityColor(6);
					 cout << (char)219;
				break;
				
				case 'G': //Grass
					SetDrawCoord(j,i);
					 SetEntityColor(98);
                     cout << (char)223;
				break;
				
				case 'T': //Trunk
					SetDrawCoord(j,i);
					 SetEntityColor(134);
					 cout << (char)178;
				break;
				
				case 'L': //Leaves
					SetDrawCoord(j,i);
					 SetEntityColor(162);
					 cout << (char)178;
				break;
				
				case 'g': //Gravel
					SetDrawCoord(j,i);
					 SetEntityColor(135);
					 cout << (char)178;
					SetEntityColor(0);
					 
					FallingBlockPhysics(j, i, 1);
				break;
				
				case 's': //Sand
					SetDrawCoord(j,i);
					 SetEntityColor(110);
					 cout << (char)178;
					SetEntityColor(0);
					 
					FallingBlockPhysics(j, i, 2);
				break;
				
				case 'W': //Water
					LiquidPhysics(j, i);
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

void FallingBlockPhysics(int x, int y, int b)
{
	if(map[y+1][x] == ' ' || map[y+1][x] == 'W')
	{
		SetDrawCoord(x,y);
		 cout << " ";
		
		map[y][x] = ' ';
		
		y++;
		
		if(b == 1) map[y][x] = 'g';
		if(b == 2) map[y][x] = 's';
	}
}

void LiquidPhysics(int x, int y)
{
	if(map[y][x] == 'W')
	{
		map[y][x] == ' ';
		
		//Bottom = Block
		if(map[y][x+1] == ' ' and map[y][x-1] != ' ' and map[y+1][x] != ' ' and map[y+1][x] != 'W') map[y][x+1] = 'W'; // Left=Block, Right=None, Bottom=Block
		if(map[y][x+1] != ' ' and map[y][x-1] == ' ' and map[y+1][x] != ' ' and map[y+1][x] != 'W') map[y][x-1] = 'W'; // Right=Block, Left=None, Bottom=Block
		if(map[y][x+1] != ' ' and map[y][x-1] != ' ' and map[y+1][x] != ' ' and map[y][x+1] != 'W' and map[y][x-1] != 'W') map[y][x] = 'W'; // Right and Left=Block, Bottom=Block
		if(map[y][x+1] == ' ' and map[y][x-1] == ' ' and map[y+1][x] != ' ' and map[y+1][x] != 'W') // Right and Left=None, Bottom=Block
		{
			map[y][x+1] = 'W';
			map[y][x-1] = 'W';
		}
		
		// Bottom = None
		if(map[y][x+1] == ' ' and map[y][x-1] != ' ' and map[y+1][x] == ' ') map[y+1][x] = 'W'; // Left=Block, Right=None, Bottom=None
		if(map[y][x+1] != ' ' and map[y][x-1] == ' ' and map[y+1][x] == ' ') map[y+1][x] = 'W'; // Right=Block, Left=None, Bottom=None
		if(map[y][x+1] != ' ' and map[y][x-1] != ' ' and map[y+1][x] == ' ') map[y+1][x] = 'W'; // Right and Left=Block, Bottom=None
		if(map[y][x+1] == ' ' and map[y][x-1] == ' ' and map[y+1][x] == ' ') map[y+1][x] = 'W'; // Right and Left=None, Bottom=None
		
		SetDrawCoord(x,y);
		 SetEntityColor(59);
		 cout << (char)178;
	}
};

// Test Redstone
void updateRedstone(int x, int y);
void useButton(int x, int y);
void useRepeater(int x, int y);

void updateRedstone(int x, int y)
{
	if(map[y][x] == '.')
	{
		if(map[y-1][x] == ',') map[y][x] == ','; //Up
		if(map[y+1][x] == ',') map[y][x] == ','; //Down
		if(map[y][x-1] == ',') map[y][x] == ','; //Left
		if(map[y][x+1] == ',') map[y][x] == ','; //Right
	}
}

void useButton(int x, int y){};
void useRepeater(int x, int y){};
//

void ParseKeys()
{
	switch(Key)
	{
		case 105: //I - Inventory
		break;
		
		case 116: //T - Interact
			if(map[CursorY][CursorX] == '<') map[CursorY][CursorX] == '>'; //Lever Off
			if(map[CursorY][CursorX] == '>') map[CursorY][CursorX] == '<'; //Lever On
			if(map[CursorY][CursorX] == '*') //useButton(); //Button
			if(map[CursorY][CursorX] == ':') //useRepeater(); //Repeater
		break;
		
		case 49: //1 - Stone
			SelectedBlock = 0;
		break;
		
		case 50: //2 - Dirt
			SelectedBlock = 1;
		break;
		
		case 51: //3 - Grass
			SelectedBlock = 2;
		break;
		
		case 52: //4 - Trunk
			SelectedBlock = 3;
		break;
		
		case 53: //5 - Leaves
			SelectedBlock = 4;
		break;
		
		case 54: //6 - Gravel
			SelectedBlock = 5;
		break;
		
		case 55: //7 - Sand
			SelectedBlock = 6;
		break;
		
		case 56: //8 - Water
			SelectedBlock = 7;
		break;
		
		case 101: //E - Build
			if(map[CursorY][CursorX] != ' ' and map[CursorY][CursorX] != 'W') break;
			
			switch(SelectedBlock)
			{
				case 0: //Stone
					map[CursorY][CursorX] = 'S';
				break;
				
				case 1: //Dirt
					map[CursorY][CursorX] = 'D';
				break;
				
				case 2: //Grass
					map[CursorY][CursorX] = 'G';
				break;
				
				case 3: //Trunk
					map[CursorY][CursorX] = 'T';
				break;
				
				case 4: //Leaves
					map[CursorY][CursorX] = 'L';
				break;
				
				case 5: //Gravel
					map[CursorY][CursorX] = 'g';
				break;
				
				case 6: //Sand
					map[CursorY][CursorX] = 's';
				break;
				
				case 7: //Water
					map[CursorY][CursorX] = 'W';
				break;
			}
		break;
		
		case 113: //Q - Remove
			map[CursorY][CursorX] = ' ';
		break;
		
		case 72: //Arrow Up
			SetDrawCoord(CursorX, CursorY);
			 cout << " ";
			 
			CursorY--;
			CursorRender();
		break;
		
		case 80: //Arrow Down
			SetDrawCoord(CursorX, CursorY);
			 cout << " ";
			 
			CursorY++;
			CursorRender();
		break;
		
		case 75: //Arrow Left
			SetDrawCoord(CursorX, CursorY);
			 cout << " ";
			 
			CursorX--;
			CursorRender();
		break;
		
		case 77: //Arrow Right
			SetDrawCoord(CursorX, CursorY);
			 cout << " ";
			 
			CursorX++;
			CursorRender();
		break;
		
		case 119: //W
			if(map[PlayerHeadY-1][PlayerHeadX] != ' ' and map[PlayerHeadY-1][PlayerHeadX] != 'W') break;
			
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
				Sleep(100);
			}
		break;
		
		case 97: //A
			if(map[PlayerHeadY][PlayerHeadX-1] != ' ' and map[PlayerHeadY][PlayerHeadX-1] != 'W'|| map[PlayerHeadY+1][PlayerHeadX-1] != ' ' and map[PlayerHeadY+1][PlayerHeadX-1] != 'W') break;
			
			SetDrawCoord(PlayerHeadX, PlayerHeadY);
			 cout << " ";
			SetDrawCoord(PlayerHeadX, PlayerHeadY+1);
			 cout << " ";
			 
			PlayerHeadX--;
			PlayerRender();
		break;
		
		case 100: //D
			if(map[PlayerHeadY][PlayerHeadX+1] != ' ' and map[PlayerHeadY][PlayerHeadX+1] != 'W' || map[PlayerHeadY+1][PlayerHeadX+1] != ' ' and map[PlayerHeadY+1][PlayerHeadX+1] != 'W') break;
			
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
	MapRender();
	PlayerRender();
	CursorRender();
	
	if(IsJumping == 0)
	{
		if(map[PlayerHeadY+2][PlayerHeadX] == ' ' || map[PlayerHeadY+2][PlayerHeadX] == 'W')
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
	system("MODE CON: COLS=80 LINES=40");
	
	SetConsoleTitle(GameTitle);
	
	SetDrawCoord(1, 0);
	 SetEntityColor(7);
	 cout << "Indev 4b";

	while(Key != 27)
	{
		DoRenderStep();
	}
	return 0;
}
