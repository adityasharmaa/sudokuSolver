#include<windows.h>
void gotoxy(short c,short r)
{
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position={c,r};
    SetConsoleCursorPosition(h,position);
}
