/***
 * AsciiCraft
 * ASCII-based minecraft-like game
 *
 * @version 0.11
 * @copyright GPL (c) 2007
**/

#include <iostream>
using namespace std;

#include <windows.h>
#include <process.h>
#include <conio.h>
#include <stdlib.h>

// System variables
int Key;

int PlayerHeadX = 1;
int PlayerHeadY = 37;

int IsJumping = 0;
int JumpStep = 0;

int SelectedBlock = 0;

int CursorX = 5;
int CursorY = 37;
const int WindowX = 80;
const int WindowY = 40;

// Game config
const char* GameTitle = "AsciiCraft - Don't kill the pigs! (nah, kill them)";

// GUI
int curInvSlot = 0;
char invSlots[4][37] = {"*--!*--!*--!*--!*--!*--!*--!*--!*--!",
						",33,,22,,11,,44,,55,,66,,77,,88,,99,",
						",33,,22,,22,,44,,55,,66,,77,,88,,99,",
						".--@.--@.--@.--@.--@.--@.--@.--@.--@"};

char selSlot[4][5] = {"QWWE",
					  "R  R",
					  "R  R",
					  "TWWY"};

// Game Map
 // Notes:
 // No map generation, yet.
 // No side-scrolling camera system yet, so, basically a map with the screen size.
char map[40][81] = {"                                                                               ",
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
void selInvSlot(int num);
void ParseKeys();
void DoRenderStep();

void GUIRender()
{
	SetDrawCoord(0, 0);
	
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 36; j++)
		{
			switch(invSlots[i][j])
			{
				case '.':
					SetDrawCoord(j + 33,i);
					 SetEntityColor(15);
					 cout << (char)192;
				break;
				
				case '-':
					SetDrawCoord(j + 33,i);
					 SetEntityColor(15);
					 cout << (char)196;
				break;
				
				case ',':
					SetDrawCoord(j + 33,i);
					 SetEntityColor(15);
					 cout << (char)179;
				break;
				
				case '@':
					SetDrawCoord(j + 33,i);
					 SetEntityColor(15);
					 cout << (char)217;
				break;
				
				case '*':
					SetDrawCoord(j + 33,i);
					 SetEntityColor(15);
					 cout << (char)218;
				break;
				
				case '!':
					SetDrawCoord(j + 33,i);
					 SetEntityColor(15);
					 cout << (char)191;
				break;
				
				case '1':
					SetDrawCoord(j + 33,i);
					 SetEntityColor(98);
                     cout << (char)219;
				break;
				
				case '2':
					SetDrawCoord(j + 33,i);
					 SetEntityColor(6);
                     cout << (char)219;
				break;
				
				case '3':
					SetDrawCoord(j + 33,i);
					 SetEntityColor(7);
                     cout << (char)219;
				break;
				
				case '4':
					SetDrawCoord(j + 33,i);
					 SetEntityColor(134);
                     cout << (char)178;
				break;
				
				case '5':
					SetDrawCoord(j + 33,i);
					 SetEntityColor(162);
                     cout << (char)178;
				break;
				
				case '6':
					SetDrawCoord(j + 33,i);
					 SetEntityColor(135);
                     cout << (char)178;
				break;
				
				case '7':
					SetDrawCoord(j + 33,i);
					 SetEntityColor(110);
                     cout << (char)178;
				break;
				
				case '8':
					SetDrawCoord(j + 33,i);
					 SetEntityColor(59);
                     cout << (char)178;
				break;
				
				case '9':
					SetDrawCoord(j + 33,i);
					 SetEntityColor(6);
                     cout << (char)197;
				break;
			}
		}
	}
}

void MapRender()
{
	SetDrawCoord(0, 0);
	
	for(int i = 0; i < 40; i++)
	{
		for(int j = 0; j < 80; j++)
		{
			switch(map[i][j])
			{
				case 'F':
					if(map[i-1][j] == ' ' || map[i-1][j] != 'W' and map[i-1][j] != 'F' and map[i-1][j] != 'g' and map[i-1][j] != 's')
					{
						map[i-1][j] = 'f';
					}
					
					SetDrawCoord(j,i);
					 SetEntityColor(6);
					 cout << "#";
				break;
				
				case 'f':
					if(map[i+1][j] != 'F')
					{
						SetDrawCoord(j,i);
						 SetEntityColor(0);
						 cout << ' ';
						map[i][j] = ' ';
					}
				break;	
				
				case 'S':
					SetDrawCoord(j,i);
					 SetEntityColor(7);
					 cout << (char)219;
				break;
				
				case 'D':
					SetDrawCoord(j,i);
					 SetEntityColor(6);
					 cout << (char)219;
				break;
				
				case 'G':
					SetDrawCoord(j,i);
					 SetEntityColor(98);
                     cout << (char)223;
				break;
				
				case 'T':
					SetDrawCoord(j,i);
					 SetEntityColor(134);
					 cout << (char)178;
				break;
				
				case 'L':
					SetDrawCoord(j,i);
					 SetEntityColor(162);
					 cout << (char)178;
				break;
				
				case 'g':
					SetDrawCoord(j,i);
					 SetEntityColor(135);
					 cout << (char)178;
					SetEntityColor(0);
					 
					FallingBlockPhysics(j, i, 1);
				break;
				
				case 's':
					SetDrawCoord(j,i);
					 SetEntityColor(110);
					 cout << (char)178;
					SetEntityColor(0);
					 
					FallingBlockPhysics(j, i, 2);
				break;
				
				case 'W':
					SetDrawCoord(j,i);
					 SetEntityColor(59);
					 cout << (char)178;
					 
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
	 SetEntityColor(15);
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
	if(map[y+1][x] == ' ' || map[y+1][x] == 'W' || map[y+1][x] == 'f')
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
	if(map[y+1][x] == 'W' and map[y-1][x] != 'W')
	{
		SetDrawCoord(x,y);
		 SetEntityColor(0);
		 cout << " ";
		map[y][x] = ' ';
	}
	else if(map[y][x+1] == ' ' and map[y][x-1] != ' ' and map[y+1][x] != ' ' and map[y+1][x] != 'W') map[y][x+1] = 'W';
	else if(map[y][x+1] != ' ' and map[y][x-1] == ' ' and map[y+1][x] != ' ' and map[y+1][x] != 'W') map[y][x-1] = 'W';
	else if(map[y][x+1] != ' ' and map[y][x-1] != ' ' and map[y+1][x] != ' ' and map[y][x+1] != 'W' and map[y][x-1] != 'W') map[y][x] = 'W';
	else if(map[y][x+1] == ' ' and map[y][x-1] == ' ' and map[y+1][x] != ' ' and map[y+1][x] != 'W'){ map[y][x+1] = 'W'; map[y][x-1] = 'W'; }
	else if(map[y][x+1] == ' ' and map[y][x-1] != ' ' and map[y+1][x] == ' ') map[y+1][x] = 'W';
	else if(map[y][x+1] != ' ' and map[y][x-1] == ' ' and map[y+1][x] == ' ') map[y+1][x] = 'W';
	else if(map[y][x+1] != ' ' and map[y][x-1] != ' ' and map[y+1][x] == ' ') map[y+1][x] = 'W';
	else if(map[y][x+1] == ' ' and map[y][x-1] == ' ' and map[y+1][x] == ' ') map[y+1][x] = 'W';
};

void selInvSlot(int num)
{
	SelectedBlock = num;
	
}

void ParseKeys()
{
	switch(Key)
	{
		case 105: //I - Inventory
		break;
		
		case 116: //T - Interact
		break;
		
		case 49: selInvSlot(0); break;
		case 50: selInvSlot(1); break;
		case 51: selInvSlot(2); break;
		case 52: selInvSlot(3); break;
		case 53: selInvSlot(4); break;
		case 54: selInvSlot(5); break;
		case 55: selInvSlot(6); break;
		case 56: selInvSlot(7); break;
		case 57: selInvSlot(8); break;
		
		case 101:
			if(map[CursorY][CursorX] != ' ' and map[CursorY][CursorX] != 'W') break;
			
			if(CursorX == PlayerHeadX and CursorY == PlayerHeadY) break;
			if(CursorX == PlayerHeadX and CursorY == PlayerHeadY + 1) break;
			
			switch(SelectedBlock)
			{
				case 0: map[CursorY][CursorX] = 'S'; break;
				case 1: map[CursorY][CursorX] = 'D'; break;
				case 2: map[CursorY][CursorX] = 'G'; break;
				case 3: map[CursorY][CursorX] = 'T'; break;
				case 4: map[CursorY][CursorX] = 'L'; break;
				case 5: map[CursorY][CursorX] = 'g'; break;
				case 6: map[CursorY][CursorX] = 's'; break;
				case 7: map[CursorY][CursorX] = 'W'; break;
				case 8: map[CursorY][CursorX] = 'F'; break;
			}
		break;
		
		case 113:
			if(map[CursorY][CursorX] == 'f') break;
			
			map[CursorY][CursorX] = ' ';
		break;
		
		case 72:
			if(CursorY == 0) break;
			
			SetDrawCoord(CursorX, CursorY);
			 cout << " ";
			 
			CursorY--;
			CursorRender();
		break;
		
		case 80:
			if(CursorY == 39) break;
			
			SetDrawCoord(CursorX, CursorY);
			 cout << " ";
			 
			CursorY++;
			CursorRender();
		break;
		
		case 75:
			if(CursorX == 0) break;
			
			SetDrawCoord(CursorX, CursorY);
			 cout << " ";
			 
			CursorX--;
			CursorRender();
		break;
		
		case 77:
			if(CursorX == 78) break;
			
			SetDrawCoord(CursorX, CursorY);
			 cout << " ";
			 
			CursorX++;
			CursorRender();
		break;
		
		case 119:
			if(map[PlayerHeadY-1][PlayerHeadX] != ' ' and map[PlayerHeadY-1][PlayerHeadX] != 'W') break;
			
			IsJumping = 1;

			while(IsJumping)
			{
				if(map[PlayerHeadY-1][PlayerHeadX] != ' ' and map[PlayerHeadY-1][PlayerHeadX] != 'W'){ IsJumping = 0; JumpStep = 0; break; }
				if(JumpStep == 2){ IsJumping = 0; JumpStep = 0; break; }
				
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
		
		case 97:
			if(map[PlayerHeadY][PlayerHeadX-1] != ' ' and map[PlayerHeadY][PlayerHeadX-1] != 'W'|| map[PlayerHeadY+1][PlayerHeadX-1] != ' ' and map[PlayerHeadY+1][PlayerHeadX-1] != 'W') break;
			
			SetDrawCoord(PlayerHeadX, PlayerHeadY);
			 cout << " ";
			SetDrawCoord(PlayerHeadX, PlayerHeadY+1);
			 cout << " ";
			 
			PlayerHeadX--;
			PlayerRender();
		break;
		
		case 100:
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
	GUIRender();
	
	SetDrawCoord(1, 1);
	 SetEntityColor(15);
	 cout << "AsciiCraft - Indev 4e";
	
	if(IsJumping == 0)
	{
		if(map[PlayerHeadY+2][PlayerHeadX] == ' ' || map[PlayerHeadY+2][PlayerHeadX] == 'W' || map[PlayerHeadY+2][PlayerHeadX] == 'f')
		{
			SetDrawCoord(PlayerHeadX, PlayerHeadY);
			 cout << " ";
			SetDrawCoord(PlayerHeadX, PlayerHeadY+1);
			 cout << " ";

			PlayerHeadY = PlayerHeadY + 1;
			PlayerRender();
		}
	} //
		
	SetDrawCoord(80, 0);
}

/* Game boot */
int main()
{
	system("MODE CON: COLS=80 LINES=40");
	SetConsoleTitle(GameTitle);
	
	//PlaySound("menu_bg.wav", NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);

	while(Key != 27)
	{
		if(kbhit())
		{
			Key = getch();
			ParseKeys();
		}
		
		DoRenderStep();
	}
	return 0;
}
