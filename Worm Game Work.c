#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#pragma warning(disable: 4101)


#include <stdio.h>
#include <time.h>                                       // For everything with time
#include <conio.h>                                      // Console operations
#include <ctype.h>                                      // String operations,(CAPS)
#include <windows.h>                                    // For somethings about system


// Moving buttons
#define UP   72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

// Global variables
int length;
int len;
int turns0;
char input;
int lifes;



// Starting functions
void Start();
void Loading();
int Score();

// Functions for priting
void Cage();
void Food();
void Delay(unsigned int);

// For moving and position
void Moving();
void gotoxy(int x, int y);

void Right();
void Up();
void Down();
void Left();
void Turns();

// For the game
void EndGame();
void WinGame();
void Level();



typedef struct{  // Typedef to write less
    int x;
    int y;
    int direction;
} coordinates;                          // Like folder with variables

coordinates head, turns[1000], apple, tail[45];                 // 1000 is max number of turns and their coordinates

coordinates apple = {0 , 0 , 0};                              // Initializing apple coordinates for genereation

int main()
{
    Start();
    system("cls");
    Loading();
    //*****************
    length = 5;                                         // Worm's length
    head.x = 25;                                        // Start position of the worm's head
    head.y = 20;
    head.direction = RIGHT;
    turns[0] = head;
    lifes = 3;                                           // That is player's lives
    //*****************
    Moving();                                           // Initializing initial turns coordinates
    return 0;
}



void Start()
{

    printf("\tWelcome to my first game 'The Worm game'.\n\n\t\t(press any key to continue)\n\n");

    getch();


    printf("\n\t->-> Game Play Instructions <-<-\n\n");

    printf("\n->-> Use arrow keys to move the worm.\n");
    printf("\n->-> You can pause the game in every tyme by pressing any another key. To continue the paused game press any other key once again.\n\n");

    printf("\n->-> You will be provided apple which you have to make your worm eat. Everytime you eat a apple the length of the worm will be increased by 1 element.\n");
    printf("\n->-> The speed of the worm will increase on every 5 elements.\n");
    printf("\n->-> You will have three lives. Your lifes will decrease as you hit the wall or worm's tail.\n\n");

    printf("\n->-> You have to reach high level to win!\n");

    printf("\n->-> If you want to exit press esc.\n");
    printf("\n->-> Press any key to continue...");

    if (getch() == 27)                                   // 27 is ASCII code for 'esc'
        exit(0);

}

void Loading()
{
    gotoxy(24, 13);
    printf("If you are ready\t(Press any key!)\n\n\t\t\tIf you are not - wait or press 'esc' to exit");
    if (getch() == 27)
        exit(0);
    
}

int Score()

{

    int score;
    score = length - 5;

    gotoxy(20, 8);

    printf("Your score : %d\n", (score));
    printf("Your length : %d\n", length);


    gotoxy(50, 8);

    printf("Life : %d", lifes);
    return score;

}




void Cage()
{
    
    int i,j;


    for (i = 10; i < 71; i++)
    {
        gotoxy(i, 10);
        printf("%c", 220);
        gotoxy(i, 30);
        printf("%c", 223);
    }

    for (i = 10; i < 31; i++)
    {
        gotoxy(10, i);
        printf("%c", 221);
        gotoxy(70, i);
        printf("%c", 222);
    }

   
}

void Food()
{
    if (head.x == apple.x && head.y == apple.y)           // head.x=25 head.y=20 in main
    {                                                   // gotoxy(apple.x,apple.y) in Cage()

        length++;                                       // If apple and Worm are at same position then length of Worm increases by 1 unit

        apple.x = rand() % 70;                           // rand() is used to generate any random number so that apple gets displayed at random positions and according to
                                                        // border 'x' cannot be greater than 70 so %70 is used
        if (apple.x <= 10)
            apple.x += 11;                               // Position less than according to border 'x' lies between 10 and 70 so if apple is at position less than 10 then it is
                                                        // incremented by some value
        apple.y = rand() % 30;

        if (apple.y <= 10)                               // Similar to x
            apple.y += 11;

    }

    else if (apple.x == 0)                               // That is to create the apple for the first time

    {
        apple.x = rand() % 70;

        if (apple.x <= 10)
            apple.x += 11;

        apple.y = rand() % 30;

        if (apple.y <= 10)
            apple.y += 11;

    }

    gotoxy(apple.x, apple.y);                              //Displaying apple

    printf("%c", 219);

}

void Delay(unsigned int w)                                 //Delay can also be without any parameter
{
    Score();

    Sleep(200 - w*5);                                    // We use 'Sleep' to slow the refreshment of the game
}



void Moving()
{
    int a, i, j;
    system("cls");

    //********************
    char clr[60];                                           // Make string with 60 elements
    memset(clr, ' ', sizeof(clr));                          // Fill whole buffer with 'space'
    clr[59] = '\0';                                         // End of string
    //********************

start:                                                      // Lable which help us to return at the begining of the function - in our case, we use it with 'goto' and it can't be uset to jump in another function
    do {
        
        Food();                                             // Take us the apple
        len = 0;
        for (i = 0; i < 45; i++)
        {
            tail[i].x = 0;
            tail[i].y = 0;
            if (i == length)
                break;
        }
        Level();
        Delay(length);                                      // Without this we can't catch the worm, its too fast
        Cage();                                          // Calls this function to draw the Cage
        for (j = 11; j < 30; j++)                           // That is for string, 'Clear the border'
        {
            gotoxy(11, j);
            printf("%s", clr);
        }

        //********************
        if (head.direction == RIGHT)
            Right();
        else if (head.direction == LEFT)                      // This is for directions, calls function for every direction to the haed
            Left();
        else if (head.direction == DOWN)
            Down();
        else if (head.direction == UP)
            Up();
        //********************
        EndGame();                                             // Use it to limit in Cage
    } while (!kbhit());                                        // Check wall hit
    a = getch();
    if (a == 27)
    {
        system("cls");
        exit(0);
    }

    input = getch();                                           // That is string, when we hit some button, we do something
    if ((input == RIGHT && head.direction != LEFT && head.direction != RIGHT) || (input == LEFT && head.direction != RIGHT && head.direction != LEFT) || (input == UP && head.direction != DOWN && head.direction != UP) || (input == DOWN && head.direction != UP && head.direction != DOWN))
    { 
        turns0++;                                               // Count turn
        turns[turns0] = head;                                    // Set's coordinates of turn
        head.direction = input;                                // Set's direction of the head
        if (input == UP)
            head.y++;

        if (input == DOWN)
            head.y--;

        if (input == RIGHT)
            head.x++;

        if (input == LEFT)
            head.x--;

        goto start;
    }

    else
    {
        printf("\a");                                          // When we use some direction command two ot more times in serial it goes 'buzz'
        goto start;
    }
}


void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}     //set the change of coordinates


void Right()                                                            // Right is first because we start at right, just for aesthetics
{
    int i;
    for (i = 0; i <= (head.x - turns[turns0].x) && len < length; i++)

    {


        tail[len].x = head.x - i;                                       // To move the worm forward in right direction

        tail[len].y = head.y;                                           // 'X' changes according to 'i' but 'y' remains same, in other direction function is same

        gotoxy(tail[len].x, tail[len].y);

        printf("%c", 254);

        len++;
    }

    Turns();

    if (!kbhit())
        head.x++;                                                       // If head din't hit the wall, countinue
}

void Up()

{
    int i;

    for (i = 0; i <= (turns[turns0].y - head.y) && len < length; i++)

    {

        gotoxy(head.x, head.y + i);

        printf("%c", 254);

        tail[len].x = head.x;
        tail[len].y = head.y + i;

        len++;

    }

    Turns();

    if (!kbhit())
        head.y--;
}

void Down()
{
    int i;
    for (i = 0; i <= (head.y - turns[turns0].y) && len < length; i++)
    {

        gotoxy(head.x, head.y - i);

        printf("%c", 254);

        tail[len].x = head.x;
        tail[len].y = head.y - i;

        len++;
    }
    Turns();

    if (!kbhit())
        head.y++;
}

void Left()
{
    int i;
    for (i = 0; i <= (turns[turns0].x - head.x) && len < length; i++)

    {

        gotoxy((head.x + i), head.y);

            printf("%c", 254);

        tail[len].x = head.x + i;
        tail[len].y = head.y;

        len++;
    }

    Turns();

    if (!kbhit())
        head.x--;
}

void Turns()
{

    int i, j, difference;

    for (i = turns0; i >= 0 && len < length; i--)

    {
        if (turns[i].x == turns[i - 1].x)

        {
            difference = turns[i].y - turns[i - 1].y;

            if (difference < 0) {
                for (j = 1; j <= (-difference); j++)

                {
                    tail[len].x = turns[i].x;

                    tail[len].y = turns[i].y + j;

                    gotoxy(tail[len].x, tail[len].y);

                    printf("%c", 254);

                    len++;

                    if (len == length)
                        break;

                }
            }

            else if (difference > 0)
                for (j = 1; j <= difference; j++)
                {

                    tail[len].x = turns[i].x;

                    tail[len].y = turns[i].y - j;

                    gotoxy(tail[len].x, tail[len].y);

                    printf("%c", 254);

                    len++;

                    if (len == length)
                        break;

                }

        }

        else if (turns[i].y == turns[i - 1].y)
        {

            difference = turns[i].x - turns[i - 1].x;

            if (difference < 0)
                for (j = 1; j <= (-difference) && len < length; j++)

                {

                    tail[len].x = turns[i].x + j;

                    tail[len].y = turns[i].y;

                    gotoxy(tail[len].x, tail[len].y);

                    printf("%c", 254);

                    len++;

                    if (len == length)
                        break;

                }

            else if (difference > 0)

                for (j = 1; j <= difference && len < length; j++)

                {


                    tail[len].x = turns[i].x - j;

                    tail[len].y = turns[i].y;

                    gotoxy(tail[len].x, tail[len].y);

                    printf("%c", 254);

                    len++;

                    if (len == length)
                        break;
                }
        }
    }
}



void EndGame()
{
    int i, check = 0;

    for (i = 4; i < length; i++)                            // Starts with 4 because it needs minimum 4 element to touch its own tail
    {
        if (tail[0].x == tail[i].x && tail[0].y == tail[i].y)
        {
            check++;                                        // Checks value increases as the coordinates of head is equal to any other tail coordinates
        }
    }

    if (head.x <= 10 || head.x >= 70 || head.y <= 10 || head.y >= 30 || check != 0)
    {

        lifes--;

        if (lifes >= 0) 

        {
            head.x = 25;
            head.y = 20;
            turns0 = 0;                                      // To know witch 'turn' number is
            head.direction = RIGHT;

            Moving();

        }

        else
        {
            system("cls");
            printf("All lives Gone\n\nBetter Luck Next Time!\n\nPress any key to quit\n\nIf you want to play again press 'y' if you don't press 'n'");
            char inputAns;
            inputAns = getch();
            if (inputAns == 'y')
            {
                system("cls");
                main();
            }
            else if (inputAns == 'n')
            {
                exit(0);
            }
        }

    }

}

void WinGame() 
{
    
    system("cls");

    printf("You win! Congratulations!!!\n\nI hope we see again\n\nPress any kay to see next page\n\nIf you want to play again press 'y' if you don't press 'n'\n\n");
    char inputAns;
    inputAns = getch();
    if (inputAns == 'y')
    {
        system("cls");
        main();
    }
    else if (inputAns == 'n')
    {
        exit(0);
    }
    
    
}

void Level()
{

    if (length == 5)
    {
        gotoxy(35, 15);
        printf("Level");
    }
    else if(length == 10)
    {
        gotoxy(35, 15);
        printf("Leve2");
    }
    else if (length == 15)
    {
        gotoxy(35, 15);
        printf("Leve3");
    }
    else if (length == 25)
    {
        gotoxy(35, 15);
        printf("Leve4");
    }
    else if (length == 35)
    {
        gotoxy(35, 15);
        printf("Leve5");
    }
    else if (length == 45)
    {
        WinGame();
    }
}
