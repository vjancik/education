#include <Windows.h>
#include <cstdlib>
#include <cstdio>

using namespace std;

int main()
{
	HWND hWnd;
	SetConsoleTitle("Matrix");
	hWnd = FindWindow(NULL, "Matrix");
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD NewSBSize = GetLargestConsoleWindowSize(hOut);
	SMALL_RECT DisplayArea = {0, 0, 0, 0};
	NewSBSize.X-=3;
	NewSBSize.Y-=1;
	SetConsoleScreenBufferSize(hOut, NewSBSize);
	ShowWindow(hWnd, SW_MAXIMIZE);
	char c;
	system("color A");
	while(1){
		for(int i=1;i<NewSBSize.X;++i){
			c=rand() % 93 + 33;
			printf("%c",c);
		}
		printf("\n");
	}
    return 0;
}