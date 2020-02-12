#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include <stdio.h>

//Colors Defn
unsigned int red =4;
unsigned int blue =1;
unsigned int green =10;
unsigned int yellow =6;
unsigned int white =15;
unsigned int gray =8;
unsigned int pink =5;
unsigned int black =32;
unsigned int lightblue =3;
unsigned int lightyellow =14;
unsigned int lightgreen =10;
unsigned int lightred =36;


void setColor(unsigned int fg_Color, unsigned int bg_Color)
{
	HANDLE hStdOut;
 
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hStdOut == INVALID_HANDLE_VALUE) {
		return;
	}

	SetConsoleTextAttribute(hStdOut, (bg_Color << 4) | fg_Color);
}

void con_def_Color(void)
{
	HANDLE hStdOut;

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hStdOut == INVALID_HANDLE_VALUE) {
		return;
	}

	/* set default gray on black attributes */
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void con_set_pos(unsigned int x, unsigned int y)
{
	COORD c;
	HANDLE hStdOut;

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hStdOut == INVALID_HANDLE_VALUE) {
		return;
	}

	c.X = (SHORT) x;
	c.Y = (SHORT) y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void con_clear(void)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD c = { 0, 0 };
	HANDLE hStdOut;
	DWORD dwNumWritten;

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hStdOut == INVALID_HANDLE_VALUE) {
		return;
	}

	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		return;
	}

	/* fill console buffer with spaces */
	FillConsoleOutputCharacter(hStdOut, ' ', csbi.dwSize.X * csbi.dwSize.Y, c, &dwNumWritten);

	/* set cursor to position 0,0 */
	SetConsoleCursorPosition(hStdOut, c);
}

void fontSize(int a, int b){  
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE); 
  PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();  
  lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);  
  GetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);  
  lpConsoleCurrentFontEx->dwFontSize.X = a;  
  lpConsoleCurrentFontEx->dwFontSize.Y = b;  
  SetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);  
 }  
 
void setFill(unsigned int fg_Color, unsigned int bg_Color)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD c = { 0, 0 };
	HANDLE hStdOut;
	DWORD dwNumWritten;

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hStdOut == INVALID_HANDLE_VALUE) {
		return;
	}

	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		return;
	}

	/* fill console buffer attributes */
	FillConsoleOutputAttribute(hStdOut, (bg_Color << 4) | fg_Color, csbi.dwSize.X * csbi.dwSize.Y, c, &dwNumWritten);
}

void animateTxt(char text[]){
	for(int i;i<strlen(text);i++){
		cout<<text[i];
		_sleep(50);
	}
}

void fullscreen()
{
keybd_event(VK_MENU,0x38,0,0);
keybd_event(VK_RETURN,0x1c,0,0);
keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}


void gotoxy ( int x, int y )
{
    COORD dwCursorPosition = { x, y };
    SetConsoleCursorPosition ( GetStdHandle ( STD_OUTPUT_HANDLE ), dwCursorPosition );
}

void con_wait_key(void)
{
	INPUT_RECORD ir;
	HANDLE hStdIn;
	DWORD dwNumEvents, dwNumRead;

	hStdIn = GetStdHandle(STD_INPUT_HANDLE);

	if (hStdIn == INVALID_HANDLE_VALUE) {
		return;
	}

	FlushConsoleInputBuffer(hStdIn);

	/* wait loop */
	while (1) {
		WaitForSingleObject(hStdIn, INFINITE);

		if (GetNumberOfConsoleInputEvents(hStdIn, &dwNumEvents) && dwNumEvents) {
			while (dwNumEvents--) {
				if (ReadConsoleInput(hStdIn, &ir, 1, &dwNumRead) && dwNumRead) {
					/* if it's a key being released, return */
					if (ir.EventType == KEY_EVENT && ir.Event.KeyEvent.bKeyDown == 0) {
						return;
					}
				}
			}
		}
	}
}
