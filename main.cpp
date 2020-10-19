// by : Ahmed Essam Mohammed
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

enum direction {Top = 1, Right , Down , Left };
typedef struct smap
{
    int width,height,fruitX,fruitY;

}Map;
typedef struct snake
{
    int head_x,head_y,tail_n;
    direction dir;
    int tail_x[50];
    int tail_y[50];

}Snake;
typedef struct player
{
    int score;
    int life;
    bool lose;

}Player;


Map mapObj;
Snake snakeObj;
Player playerObj;


void generateFruit();
void generateSnake();
void setup();
void draw();
void input();
void Move();
void shiftElements(int arr[],int size);

int main()
{
    setup();

    while(!playerObj.lose)
    {

        draw();
        input();
        Move();

        if(playerObj.score <= 1)
        {
          Sleep(500);
        }
        else
        {
            Sleep(50);
        }
        if(playerObj.score==7)
        {
            cout<<"The Winner \a";
            exit(0);
        }
    }
    system("pause");

    return 0;
}

void generateFruit()
{
    srand(time(NULL));
    mapObj.fruitX = rand()%(mapObj.width-2)+1;
    mapObj.fruitY = rand()%(mapObj.height-2)+1;
}

void generateSnake()
{
    snakeObj.head_x = mapObj.width/2;
    snakeObj.head_y = mapObj.height/2;
    snakeObj.tail_n = 1;
}

void shiftElements(int arr[],int Size)
{
    for(int i = Size-2;i>=0;i--)
    {
        arr[i+1]=arr[i];
    }

}

void setup()
{
    mapObj.width = 40;
    mapObj.height = 40;
    generateFruit();

     generateSnake();

    playerObj.score = 0;
    playerObj.life = 3;
    playerObj.lose = false;

}

void draw()
{
    system("CLS");

   for(int i =0; i<mapObj.width;i++)
   {
       for(int j =0; j<mapObj.height;j++)
       {
            if(j==0 || j==(mapObj.height-1) || i==0 || i==(mapObj.width-1) )
            {
                cout<<"*";
            }
            else if (i==snakeObj.head_y && j==snakeObj.head_x)
            {
                cout<<"O";
            }
            else if(i==mapObj.fruitY && j==mapObj.fruitX)
            {
                cout<<"$";
            }
            else
            {
                bool printed = false;

                for(int z =0;z<snakeObj.tail_n;z++)
                {
                    if(snakeObj.tail_x[z] == j && snakeObj.tail_y[z] == i)
                    {
                        cout<<"o";
                        printed = true;
                        break;
                    }
                }
                if(!printed)
                {
                    cout<<" ";
                }
            }

       }
       cout<<endl;
   }

   cout<<"Player score :"<<playerObj.score<<"  "<<"Player Life :"<<playerObj.life<<endl;

}

void input()
{
    if(_kbhit())
    {

        switch(getch())
        {
         case 72 : snakeObj.dir = Top;
         break;
         case 'w' : snakeObj.dir = Top;
         break;
         case 80 : snakeObj.dir = Down;
         break;
         case 's' : snakeObj.dir = Down;
         break;
         case 77 : snakeObj.dir = Right;
         break;
         case 'd' : snakeObj.dir = Right;
         break;
         case 75 : snakeObj.dir = Left;
         break;
         case 'a' : snakeObj.dir = Left;
         break;
         case 't' : exit(0);
        }
    }
}

void Move()
{
    shiftElements(snakeObj.tail_x,50);
    shiftElements(snakeObj.tail_y,50);
    snakeObj.tail_x[0] = snakeObj.head_x;
    snakeObj.tail_y[0] = snakeObj.head_y;

    switch(snakeObj.dir)
    {
    case Top : snakeObj.head_y--;
    break;
    case Down : snakeObj.head_y++;
    break;
    case Right : snakeObj.head_x++;
    break;
    case Left : snakeObj.head_x--;
    break;

    }

     for(int b=1;b<snakeObj.tail_n;b++)
         {
           if(snakeObj.head_x ==snakeObj.tail_x[b] && snakeObj.head_y == snakeObj.tail_y[b])
           {
                playerObj.life--;
                snakeObj.tail_n=snakeObj.tail_n - b;
           }
         }
    if(snakeObj.head_y>=mapObj.height || snakeObj.head_x>=mapObj.width || snakeObj.head_y<=0 || snakeObj.head_x<=0 )
    {
         generateSnake();
         playerObj.life--;


    }
    if(playerObj.life==0)
         {
             playerObj.lose=true;
             cout<<"GAME OVER "<<endl;
         }


    if(snakeObj.head_y == mapObj.fruitY && snakeObj.head_x == mapObj.fruitX)
    {
        generateFruit();
        snakeObj.tail_n++;
        playerObj.score++;
    }
}
