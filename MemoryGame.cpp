// contains windows dependent header files. 

#include<conio.h>
#include<iostream>
#include<string>
#include<windows.h>
#include<direct.h>
#include<stdio.h>
#include<stdlib.h>
#include "RandomGeneration.h"

using namespace std;

void gotoxy(short x, short y)   //used for positioning the cursor on the screen
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x-1;                                                        // x axis for positioning
    pos.Y = y-1;                                                        // y axis for positioning
    SetConsoleCursorPosition(hcon,pos);
}

class Game 
{
    char boardDefault[5][4];                                            // board with @ values
    char boardSet[5][4];                                                // board with real values 
    char boardCurrent[5][4];                                            // current values held in the board
    char cmp1,cmp2 ;                                                    // comparing the cell values 
    int tries;                                                          // Tracks the number of attempts
    int t1,t2;                                                          // holds the temprory cell numbers
    int t3,t4;                                                          // holds the temprory cell numbers
    int i; 

public:
    Game()                                                              //default constructor for initializing the values of i and tries with default values
    {
        i=0;
        tries=0;
    }
    
void CreateBoard()                                                      // 1. prints the column headings, 2.then underlines the headings and then 3.fills the board with default characters 
{
    int k=0;            
    cout<<"\n\n\n\n";
    cout<<"\t\t";
    for(int i=0;i<4;i++)                                                // 1.
    {
        cout<<"\t"<<i;
    }
    cout<<endl<<endl;
    cout<<"\t\t";
    for(int i = 0;i<25;i++)                                             // 2.
    {
        cout<<"*";
    }
    cout<<endl<<endl;
    cout<<"\t";
    char row = 'A';                                                     // 3.
    for(int i=0;i<5;i++)    
    {
        cout<<"\t"<<row;
        for(int j=0;j<4;j++)
        {
            boardDefault[i][j] = '@';
            boardCurrent[i][j] = boardDefault[i][j];
            cout<<"\t"<<boardDefault[i][j];
        }
        cout<<endl<<endl;
        cout<<"\t";
        row++;
    }
}

void fillBoard()                                                                // matrix with values that should be made visible  
{
    char a[10];
    int randno[10];
    int rno;
    RandomGeneration *rg;
    rg = new RandomGeneration();
    rno = rg -> drawRandomNumber();
    for(int k=0; k<10; k++)
    {
        randno[k] = rno*k;
        a[k] = randno[k];
        if(a[k]=='\0')
        {
            a[k]='%';
        }
    }
    int k=0 ;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<4;j++)
        {
            boardSet[i][j]=a[k];
            if(k==9)
                    k=0;
            else
                    k++;
        }
    }
}

void changeCell()
{
    int bb,cnt=0;
    int counter=0;
    int cell_1=0,cell_2=0;
    char cellno[2];
    char choice;
    
    do
    {
        tries=0;
        cout<<"Enter -1 to exit ";
        CreateBoard();                                                                           // Creates board
        i=0;
        while(true)
        {
            i++;
            int flag=0;

            for(int m=0;m<5;m++)
            {
                for(int n=0;n<4;n++)
                {
                    if(boardCurrent[m][n]=='@')
                    {
                        flag=1;
                        continue;
                    }

                }
            }

            if(flag==0)                                                                            // The matrix does not have @ that implies that all the cells have turned out  
            {
                system("cls");
                gotoxy(24,9);
                cout<<"CONGTRATULATIONS!!!"<<endl<<endl;
                gotoxy(26,10);
                cout<<"You have completed in"<<tries<<"Tries:";
                gotoxy(28,13);
                cout<<endl<<"PLAY AGAIN!(Y/N)";
                goto clearScreen;                                                                   // clearScreen is a tag that clears the entire screen 
            }

            else
            {
                drawCurrentMatrix: if(counter>2)                                                    // drawCurrentMatrix is a label that clears the screen and draws the cirrent matrix 
                                    {                                                               // COunter >2 means that the number of failed tries is greater than 2.
                                        system("cls");
                                        CurrentMatrix();
                                        counter=0;
                                        cnt=0;
                                        goto cellChangeAndConverter;                              // label that performs cell changing and cell number converter
                                    }
                                
                cellChangeAndConverter:  
                                        cout<<"Enter the cell number to be opened:";
                                        cin>>cellno;
                                        counter++;
                                        
                                        if(strlen(cellno)>2)
                                        {
                                            cout<<"\n Enter valid cell no...";
                                            counter++;
                                            goto drawCurrentMatrix;
                                        }
                                        else
                                        {
                                            tries++;
                                            if(i==3)
                                            {
                                                if(cmp1 != cmp2)
                                                {
                                                    ReplaceWithDefault(t1,t2);
                                                    boardCurrent[t1][t2]='@';
                                                    ReplaceWithDefault(t3,t4);
                                                    boardCurrent[t3][t4]='@';
                                                    t1=t2=t3=t4=0;
                                                    i=1;
                                                }
                                                else 
                                                    {i=1;}
                                            }
                                            
                                            if(cellno[0]=='-' && cellno[1]=='1')
                                            {
                                                system("cls");
                                                gotoxy(28,13);
                                                cout<<endl<<"Play Again(Y/N)";
                                                goto clearScreen;
                                                break;
                                            }
                                            else                                                            // Converting A B C D E to 0 1 2 3 4 
                                            {
                                                switch(cellno[0])
                                                {
                                                    case 'A':
                                                    case 'a':
                                                                cell_1=0; break;
                                                    
                                                    case 'B':
                                                    case 'b':
                                                                cell_1=1; break;
                                                    case 'C':
                                                    case 'c':
                                                                cell_1=2; break;
                                                    case 'D':
                                                    case 'd':
                                                                cell_1=3; break;
                                                    case 'E':
                                                    case 'e':
                                                                cell_1=4; break;
                                                    default:
                                                                {
                                                                    gotoxy(1,22+cnt);
                                                                    cout<<"\nEnter a valid cell number:";
                                                                    counter++;
                                                                    goto drawCurrentMatrix;
                                                                }
                                                }

                                                switch(cellno[1])
                                                {
                                                    case '0': 
                                                                cell_2=0; break;
                                                    case '1':
                                                                cell_2=1; break;
                                                    case '2':
                                                                cell_2=2; break;
                                                    case '3':
                                                                cell_2=3; break;
                                                    default:
                                                            {
                                                                gotoxy(1,22+cnt);
                                                                cout<<"\nEnter an valid cell number:";
                                                                counter++;
                                                                goto drawCurrentMatrix;
                                                            }
                                                }

                                                if(boardCurrent[cell_1][cell_2] != '@')
                                                {
                                                    gotoxy(1,22+cnt);
                                                    cout<<"Cell is already opened!\n";
                                                    goto cellChangeAndConverter;
                                                }

                                                else 
                                                {
                                                    IdentifyLocation(cell_1,cell_2,cnt);
                                                    if(i==1)
                                                    {
                                                        cmp1=boardSet[cell_1][cell_2];
                                                        t1=cell_1;
                                                        t2=cell_2;
                                                    }
                                                    if(i==2)
                                                    {
                                                        cmp2=boardSet[cell_1][cell_2];
                                                        t3=cell_1;
                                                        t4=cell_2;
                                                    }
                                                    cout<<boardSet[cell_1][cell_2];
                                                    //storing the current instance of the matrix

                                                    boardCurrent[cell_1][cell_2] = boardSet[cell_1][cell_2];
                                                    gotoxy(1,22+cnt);
                                                    cnt++;
                                                }

                                         }
             }
        }
        }   
     clearScreen: cin>>choice ;
                system("cls");
    }while(choice=='Y' || choice=='y'); 
 }


void CurrentMatrix()
{
    int i,j;
    cout<<"\n\n\n\n";
    cout<<"\t\t";

    for(j=0;j<4;j++)
    {
        cout<<"\t"<<j;
    }
    cout<<endl<<endl;
    cout<<"\t\t\t";

    for(j=0;j<25;j++)
    {
        cout<<"*";
    }
    cout<<endl<<endl;
    cout<<"\t";
    char row='A';

    for(i=0;i<5;i++)
    {
        cout<<"\t"<<row;
        for(j=0;j<4;j++)
        {
            if(boardCurrent[i][j]!='\0')
            {
                cout<<"\t"<<boardCurrent[i][j];
            }
            else
            {
                boardCurrent[i][j]='@';
                cout<<"\t"<<boardCurrent[i][j];
            }
        }
          cout<<"\n";
          row++;
          cout<<"\n\t";
    }
}

void IdentifyLocation(int cell_1,int cell_2,int cnt)
{
    if(cell_1==0)               //'A'
    {
        switch(cell_2)
        {
            case 0: gotoxy(25,9); break;
            case 1: gotoxy(33,9); break;
            case 2: gotoxy(41,9); break;
            case 3: gotoxy(49,9); break;
            default:
                {
                    gotoxy(1,22+cnt);
                    cout<<"\nEnter valid cell no";
                    break;
                }

        }
    }
    if(cell_1==1)               //'B'
    {
        switch(cell_2)
        {
            case 0: gotoxy(25,11); break;
            case 1: gotoxy(33,11); break;
            case 2: gotoxy(41,11); break;
            case 3: gotoxy(49,11); break;
        }
    }
     if(cell_1==2)               //'C'
    {
        switch(cell_2)
        {
            case 0: gotoxy(25,13); break;
            case 1: gotoxy(33,13); break;
            case 2: gotoxy(41,13); break;
            case 3: gotoxy(49,13); break;
        }
    }
     if(cell_1==3)               //'C'
    {
        switch(cell_2)
        {
            case 0: gotoxy(25,15); break;
            case 1: gotoxy(33,15); break;
            case 2: gotoxy(41,15); break;
            case 3: gotoxy(49,15); break;
        }
    }
     if(cell_1==4)               //'E'
    {
        switch(cell_2)
        {
            case 0: gotoxy(25,17); break;
            case 1: gotoxy(33,17); break;
            case 2: gotoxy(41,17); break;
            case 3: gotoxy(49,17); break;
        }
    }
}

void ReplaceWithDefault(int val1,int val2)
{
    switch(val1)
    {
        case 0: //'A'
        {
            switch(val2)
            {
                case 0: gotoxy(25,9);cout<<'@'; break;
                case 1: gotoxy(33,9);cout<<'@'; break;
                case 2: gotoxy(41,9);cout<<'@';break;
                case 3: gotoxy(49,9);cout<<'@'; break;
            }
            break;
        }
        case 1: //'B'
        {
            switch(val2)
            {
                case 0: gotoxy(25,11);cout<<'@'; break;
                case 1: gotoxy(33,11);cout<<'@'; break;
                case 2: gotoxy(41,11);cout<<'@';break;
                case 3: gotoxy(49,11);cout<<'@'; break;
            }
            break;
        }
        case 2: //'C'
        {
            switch(val2)
            {
                case 0: gotoxy(25,13);cout<<'@'; break;
                case 1: gotoxy(33,13);cout<<'@'; break;
                case 2: gotoxy(41,13);cout<<'@';break;
                case 3: gotoxy(49,13);cout<<'@'; break;
            }
            break;
        }
        case 3: //'D'
        {
            switch(val2)
            {
                case 0: gotoxy(25,15);cout<<'@'; break;
                case 1: gotoxy(33,15);cout<<'@'; break;
                case 2: gotoxy(41,15);cout<<'@';break;
                case 3: gotoxy(49,15);cout<<'@'; break;
            }
            break;
        }
        case 4: //'D'
        {
            switch(val2)
            {
                case 0: gotoxy(25,17);cout<<'@'; break;
                case 1: gotoxy(33,17);cout<<'@'; break;
                case 2: gotoxy(41,17);cout<<'@';break;
                case 3: gotoxy(49,17);cout<<'@'; break;
            }
            break;
        }
     }
}
};

int main()
{
    Game g;
    g.fillBoard();
    g.changeCell();
    return 0;
}





















































