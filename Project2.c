#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#pragma warning(disable: 4101)


#include <stdio.h>
#include <conio.h>                                      // За всички операции свързани с конзолата, 'kbhit', 'getch'
#include <windows.h>                                    // За всички неща свързани със системата 'system ("cls")'


// Бутони за движение

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77


// Глобални променливи
int length;
int len;
int turns0;
char input;
unsigned int lifes;
int i, j;




// Стартиращи функции
void gotoxy(int x, int y);
void Start();
int Score();

// Функции за принтиране
void Cage();
void Food();

// За преместване и позиция
void Moving();
void Level();

void Right();
void Up();
void Down();
void Left();
void Turns();

// За краят на играта
void EndGame();
void WinGame();




typedef struct {                                                        // Typedef, за да пишем по - малко
    int x;
    int y;
    int direction;
} coordinates;                                                         // Използва се като папка за променливи

coordinates head, turns[1000], apple, tail[30];                        // 1000 е максималният брой на завоите

coordinates apple = { 0 , 0 , 0 };                                       // Инициализираме началните координати на ябълката

int main()
{
    Start();

    //*****************
    length = 5;                                                        // Дължината на Червеят
    head.x = 25;                                                       // Стартовата позиция
    head.y = 20;
    head.direction = RIGHT;
    turns[0] = head;
    lifes = 3;                                                         // Животите, които имаме
    //*****************

    Moving();                                                          // Извикваме функцията за движение

    return 0;
}

// Закача координатите според нуждата
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}



void Start()
{
    gotoxy(24, 12);
    printf("Welcome to my first game 'The Worm game'!");

    gotoxy(30, 14);
    printf("(press any key to continue)");

    getch();
    system("cls");

    printf("\n\t->-> Game Play Instructions <-<-\n\n");

    printf("\n->-> Use arrow keys to move the worm.\n");
    printf("\n->-> You can pause the game in every tyme by pressing 'p' key. To continue the paused game press any other key once again.\n\n");

    printf("\n->-> You will be provided apple which you have to make your worm eat. Everytime you eat a apple the length of the worm will be increased by 1 element.\n");
    printf("\n->-> The speed of the worm will increase on every 5 elements.\n");
    printf("\n->-> You will have three lives. Your lifes will decrease as you hit the wall or worm's tail.\n\n");

    printf("\n->-> You have to reach high level to win!\n");

    printf("\n->-> If you want to exit press esc.\n");
    printf("\n->-> Press any key to continue...");

    if (getch() == 27)                                                  // 27 е ASCII кода за 'esc'
        exit(0);


    system("cls");


    gotoxy(24, 12);
    printf("If you are ready\t(Press any key!)\n\n\t\t\tIf you are not - wait to be raedy or press 'esc' to exit");

    if (getch() == 27)
        exit(0);
}

// Изчислява и записва резултатът
int Score()

{
    int score;

    score = length - 5;                                                 // score се изчислява като извадим 5 от дължината 'length'

    gotoxy(20, 8);
    printf("Your score : %d\n", score);

    gotoxy(20, 9);
    printf("Your length : %d\n", length);

    gotoxy(50, 8);
    printf("Life : %d", lifes);
    return score;

}



// Задаваме от къде да започне да принтира клетката, в която се движи змията
void Cage()
{
    gotoxy(33, 2);
    printf(">>>Worm game<<<");

    gotoxy(35, 4);
    printf("Let's play");

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

// За принтиране на ябълката
void Food()
{
    if (head.x == apple.x && head.y == apple.y)                         // head.x=25 head.y=20 в main() функцията
    {

        length++;                                                       // Ако Ябълката и главата на червея се озоват на едни координати, то той се издължава с едно деление

        apple.x = rand() % 70;                                          // rand() се използва, за да се генерира различно число, което да се използва за координати на ябълката вътре в клетката
                                                                        // тоест до 70 по 'x', тогава използваме %70
        if (apple.x <= 10)
            apple.x += 11;                                              // Понеже клетката се принтира между 10 и 70 трябва да принтираме там,
                                                                        // а ако е преди 10 му задаваме 'x' координати след 11
        apple.y = rand() % 30;

        if (apple.y <= 10)                                              // Същото като за x
            apple.y += 11;

    }

    else if (apple.x == 0)                                              // С това принтираме ябълката за първи път

    {
        apple.x = rand() % 70;

        if (apple.x <= 10)
            apple.x += 11;

        apple.y = rand() % 30;

        if (apple.y <= 10)
            apple.y += 11;

    }

    gotoxy(apple.x, apple.y);

    printf("%c", 219);

}




void Moving()
{

    system("cls");

    //********************
    char clr[60];                                                          // Правим string с 60 елемента
    memset(clr, ' ', sizeof(clr));                                         // Пълним целият буфер с 'space'
    clr[59] = '\0';                                                        // Край
    //********************

start:                                                                     // Този Lable ни задава точка, до която можем да достигнем чрез go to, това не може да се използва за презкачане през функции
    do {

        Food();                                                            // Тази функция ни извиква ябълката
        Score();                                                           // Тази е за изписването на резултатът
        len = 0;                                                           // Извиква функция за изписване на нивата
        for (i = 0; i < 30; i++)
        {
            tail[i].x = 0;
            tail[i].y = 0;
            if (i == length)
                break;
        }
        Level();
        Sleep(200 - length * 5);                                           // Това задава скоростта на червя
        Cage();                                                            // Извиква функцията, която изчертава клетката
        for (j = 11; j < 30; j++)                                          // Използва се за изчистване, със system("cls") много мига
        {
            gotoxy(11, j);
            printf("%s", clr);
        }

        //********************
        if (head.direction == RIGHT)
            Right();
        else if (head.direction == LEFT)                                   // Накъдето е насочена главата - нея функция да използва
            Left();
        else if (head.direction == DOWN)
            Down();
        else if (head.direction == UP)
            Up();
        //********************
        EndGame();                                                         // Там са зададени границите на клетката
    } while (!kbhit());                                                    // Прави докато не е натиснато
    input = getch();
    if (input == 27)
    {
        system("cls");
        exit(0);
    }

    input = getch();

    // Чрез бутоните за задвижване се извикват техните функции
    if ((input == RIGHT && head.direction != LEFT && head.direction != RIGHT) || (input == LEFT && head.direction != RIGHT && head.direction != LEFT) || (input == UP && head.direction != DOWN && head.direction != UP) || (input == DOWN && head.direction != UP && head.direction != DOWN))
    {
        turns0++;                                                          // 'turns0' е един вид междинна променлива, тя е заедно с масива 'Turns' и при всеки завой прибавя по еднаединица докто не запълни масива
        
        turns[turns0] = head;                                              // Задава координати на завоят спрямо главата
        
        head.direction = input;                                            // Задава посока на главата спрямо бутонът, който сме натиснали
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
        printf("\a");                                                      // Когато натиснем някой бутон повече от два пъти то изписква, един вид като грешка,
                                                                           // за да ни съобщи, че трябва да натиснем друго
        goto start;

    }
}

// Изписва нивото спрямо дължината
void Level()
{

    if (length == 5)
    {
        for (i = length; i < 10; i++)
        {
            gotoxy(35, 6);
            printf("Level 1");
        }
    }

    else if (length == 10)
    {
        for (i = length; i < 15; i++)
        {
            gotoxy(35, 6);
            printf("Leve 2");

        }
    }

    else if (length == 15)
    {
        for (i = length; i < 20; i++)
        {
            gotoxy(35, 6);
            printf("Leve 3");

        }
    }

    else if (length == 20)
    {
        for (i = length; i < 25; i++)
        {
            gotoxy(35, 6);
            printf("Level 4");

        }
    }

    else if (length == 25)
    {
        for (i = length; i < 30; i++)
        {
            gotoxy(35, 6);
            printf("Level 5");

        }
    }
    else
    {
        if (length == 30)
        {
            WinGame();
        }
    }

}



void Right()                                                            // 'Right' е първо, защото започваме надясно, мда естетика
{
    for (i = 0; i <= (head.x - turns[turns0].x) && len < length; i++)

    {


        tail[len].x = head.x - i;                                       // За да върви направо в дясната посока
        tail[len].y = head.y;                                            // 'x' се изменя спрямо 'i', 'y' си остава същото

        gotoxy(tail[len].x, tail[len].y);

        printf("%c", 254);

        len++;
    }

    Turns();

    if (!kbhit())
        head.x++;                                                       // Ако не е натиснат, нека продължи
}

void Up()

{
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

/*  < Turns() >
 - Функцията се разпорежда върху работата по изграждане на завой
 - Тя взема опашката, върти завоите й и пренарежда блоковете чрез оператор FOR в съответната посока
 - Реализирани са 4 блока за пренареждане на посоката:
    < по оста У:
        - Нагоре
        - Надолу
    >
    < по оста Х:
        - Надясно
        - Наляво
    >
 */
void Turns() {

    int difference;                                                      // Тези се използват за for-овете, в променлива difference се попълва дължината от завой до завой

    // turns е масив, в който се съхраняват кординатите на завоите, които прави
    for (i = turns0; i >= 0 && len < length; i--) {

        // Ако този завой с координати по Х [...] e = предния завой с координати по Х [...]
        if (turns[i].x == turns[i - 1].x) {

            // Взема се разстоянието между координатите по оста У между тези два завоя
            difference = turns[i].y - turns[i - 1].y;

            if (difference < 0) {                                       // Ако разтоянието е отрицателно    ( тоест се движи надолу )
                for (j = 1; j <= (-difference); j++) {                  // Правим модул |разликата| за да е положителна
                                                                      // И въртим от j = 1  до колкото е разликата
                                                                      // ( 1 понеже има поне едно иначе няма да има разлика )
                    tail[len].x = turns[i].x;                           // Прави координатите( по Х ) на последното блокче от опашката да е равно на текущото блокче i
                    tail[len].y = turns[i].y + j;                       // прави координати на последното блокче ( по У ) да е равно на текущото блокче по y + J

                    gotoxy(tail[len].x, tail[len].y);                   // Тук задава преместване до координати на последното блокче от опашката
                    printf("%c", 254);                                  // и поставя символ - 254 ■ блокчето
                    len++;
                    // Дължината нараства, докато не е равно на дължинатa на опашката
                    if (len == length)
                        break;
                }
            }
            else if (difference > 0)                                    // Ако разтоянието е положително     ( тоест се движи нагоре )
                for (j = 1; j <= difference; j++) {
                    tail[len].x = turns[i].x;
                    tail[len].y = turns[i].y - j;                       // Единствената разлика с другото е че обръщаме чрез -

                    gotoxy(tail[len].x, tail[len].y);
                    printf("%c", 254);
                    len++;
                    if (len == length)
                        break;
                }
        }
        // Ако този завой с координати по Y[...] е до предишния завой с координати по оста Y[...]
        else if (turns[i].y == turns[i - 1].y) {
            // Взимаме разтоянието между двете точки където се намират завоите по оста Х
            difference = turns[i].x - turns[i - 1].x;

            if (difference < 0) {                                       // Ако разтоянието е отрицателно     ( тоест се движи наляво )
                for (j = 1; j <= (-difference) && len < length; j++) {
                    tail[len].x = turns[i].x + j;                       // прибавяме J
                    tail[len].y = turns[i].y;
                    gotoxy(tail[len].x, tail[len].y);
                    printf("%c", 254);
                    len++;
                    if (len == length)
                        break;
                }
            }
            else if (difference > 0) {                                  // А ако разтоянието е положително ( демек се движи надясно )
                for (j = 1; j <= difference && len < length; j++) {
                    tail[len].x = turns[i].x - j;                       // изваждаме J
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
}




void EndGame()
{
    int i, check = 0;

    for (i = 4; i < length; i++)                                       // Стартира от 4, защото толкова са достатъчно, за да се захапе
    {
        if (tail[0].x == tail[i].x && tail[0].y == tail[i].y)
        {
            check++;                                                   // Проверява дали нарастването на координатите на главата са равни на тези на опашката
        }
    }

    if (head.x <= 10 || head.x >= 70 || head.y <= 10 || head.y >= 30 || check != 0)
    {

        lifes--;

        if (lifes >= 0)

        {
            head.x = 25;
            head.y = 20;
            turns0 = 0;                                                // Ако е друго число запасът от завои в масива ще свърши по бързо
            head.direction = RIGHT;

            Moving();

        }
        else if (lifes <= -1)
        {
            exit(0);
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
