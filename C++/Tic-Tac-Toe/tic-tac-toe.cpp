#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;
int i,r,s,x,y,player,n,win,z;
char field [20][20];
char number [100];
void Line1() {
    cout<<" ";
    for(x=1;x<s+1;x++)
        cout<<"+-";
    cout<<"+"<<endl;
}
void Line2() {
    for(x=1;x<s+1;x++) {
        cout<<"|";
        if (field[x][y]==0)
        field[x][y]=' ';
        cout<<field[x][y];
    }
    cout<<"|"<<endl;
}
void Paint() {
    cout<<" ";
    for(x=1;x<s+1;x++)
        cout<<" "<<x;
        cout<<endl;
        for(y=1;y<r+1;y++) {
            Line1();
            cout<<y;
            Line2();
        }
    Line1();
}
int check(char checknumber [100]) {
    char n=checknumber[i];
    int i=0;
    while(n!=0){
        n=checknumber[i];
        if(n==0)break;
        if(n<48 || n>57) {
            return 0;
            break;
        }
        i++;
    }
    cout<<endl;
}
void Move() {
    if (player==1) {
        cout<<"Player 1 enter coordinates, first row then column, of the space where you want to put your mark."<<endl;
        cin>>number;
        z=check(number);
        if(z==0) {
            cout<<"Your input isn't a valid number."<<endl;
            Move();
        } else {
            cout<<"Your input is valid."<<endl;
            x=atoi(number);
        }
        cin>>number;
        z=check(number);
        if(z==0) {
            cout<<"Your input isn't a valid number."<<endl;
            Move();
        } else {
            cout<<"Your input is valid"<<endl;
            y=atoi(number);
        }
        if (field[x][y]!=' ') {
            cout<<"Invalid move, try again."<<endl;
            Move();
        } else
            field[x][y]='X';
        player=2;
    } else {
        cout<<"Player 2 enter coordinates, first row then column, of the space where you want to put your mark."<<endl;
        cin>>x;
        cin>>y;
        if (field[x][y]!=' ') {
            cout<<"Invalid move, try again."<<endl;
            Move();
        } else
            field[x][y]='O';
        player=1;
    }
}
void CheckWin() {
    for(y=1;y<r+1;y++)
        for(x=1;x<s+1;x++) {
            if (field[x][y]=='X') {
                if (field[x+1][y+1]=='X')
                    if (field[x+2][y+2]=='X')
                        if (field[x+3][y+3]=='X')
                            if (field[x+4][y+4]=='X')
                                win=1;
                if (field[x][y+1]=='X')
                    if (field[x][y+2]=='X')
                        if (field[x][y+3]=='X')
                            if (field[x][y+4]=='X')
                                win=1;
                if (field[x+1][y]=='X')
                    if (field[x+2][y]=='X')
                        if (field[x+3][y]=='X')
                            if (field[x+4][y]=='X')
                                win=1;
                if (field[x-1][y+1]=='X')
                    if (field[x-2][y+2]=='X')
                        if (field[x-3][y+3]=='X')
                            if (field[x-4][y+4]=='X')
                                win=1;
            }
            if (field[x][y]=='O') {
                if (field[x+1][y+1]=='O')
                    if (field[x+2][y+2]=='O')
                        if (field[x+3][y+3]=='O')
                            if (field[x+4][y+4]=='O')
                                win=2;
                if (field[x][y+1]=='O')
                    if (field[x][y+2]=='O')
                        if (field[x][y+3]=='O')
                            if (field[x][y+4]=='O')
                                win=2;
                if (field[x+1][y]=='O')
                    if (field[x+2][y]=='O')
                        if (field[x+3][y]=='O')
                            if (field[x+4][y]=='O')
                                win=2;
                if (field[x-1][y+1]=='O')
                    if (field[x-2][y+2]=='O')
                        if (field[x-3][y+3]=='O')
                            if (field[x-4][y+4]=='O')
                                win=2;
            }
        }
}
int main() {
    win=0;
    player=1;
    cout<<"Insert the number of columns from 5 to 9: ";
    cin>>number;
    z=check(number);
    if(z==0) {
        cout<<"Your input isn't a valid number."<<endl;
        main();
    } else {
        cout<<"Your input is valid."<<endl;
        s=atoi(number);
    }
    cout<<"Insert the number of rows from 5 to 9: ";
    cin>>number;
    z=check(number);
    if(z==0) {
        cout<<"Your input isnt a valid number."<<endl;
        main();
    } else {
        cout<<"Your input is valid."<<endl;
        r=atoi(number);
    }
    for(y=1;y<r+1;y++)
        for(x=1;x<s+1;x++)
            field[x][y]=0;
    if (s<5)
        s=5;
    if (s>9)
        s=9;
    if (r<5)
        r=5;
    if (r>9)
        r=9;
    while (win==0) {
        Paint();
        Move();
        system("clear");
        CheckWin(); }
    Paint();
    if (win==1)
        cout<<endl<<"GAME OVER! Player 1 wins!";
    if (win==2)
        cout<<endl<<"GAME OVER! Player 2 wins!";
    cout<<endl<<endl<<"Made by Vix!";
    cin.get();
    cin.get();
    return 0;
}
