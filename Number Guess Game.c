#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>

void setColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor | (bgColor << 4));
}

void setConsoleFontSize(int size) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    GetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
    cfi.dwFontSize.Y = size;
    SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}

void printCentered(const char *str) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int strLength = strlen(str);
    int spaces = (consoleWidth - strLength) / 2;
    for (int i = 0; i < spaces; i++) {
        printf(" ");
    }
    printf("%s\n", str);
}

void load(int *total_game_played, int *total_game_win, int *total_game_lose)
{
    FILE *file = fopen("states.txt", "r");
    if (file) {
        fscanf(file, "%d\n%d\n%d\n", total_game_played, total_game_win, total_game_lose);
        fclose(file);
    }
}

void save(int total_game_played, int total_game_win, int total_game_lose)
{
    FILE *file = fopen("states.txt", "w");
    if (file) {
        fprintf(file, "%d\n%d\n%d\n", total_game_played, total_game_win, total_game_lose);
        fclose(file);
    }
}

bool isInteger(const char *str) {
    if (*str == '\0') return false;
    if (*str == '-' || *str == '+') str++;
    while (*str) {
        if (!isdigit(*str)) {
            return false;
        }
        str++;
    }
    return true;
}

void main()
{
    int i = 0;
    int j;
    int k = 0;
    int l = 0;
    char limite_number_scan[20];
    int limite_number;
    char scaned_characters[20];
    int scaned_number;
    bool validChoise;
    bool validInput;
    char game_mode_scan[20];
    int game_mode;
    char tries_number_scan[20];
    int tries_number;
    int game = 1;
    int total_game_played = 0;
    int total_game_win = 0;
    int total_game_lose = 0;
    bool number_found = false;
    bool restart = false;
    char setting_mode_replays;
    char replay;
    setConsoleFontSize(24);
    load(&total_game_played, &total_game_win, &total_game_lose);
    while (i == 0)
    {
        setColor(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY, 0);
        printCentered("Welcome To 'NUMBER GUESS GAME'");
        setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, 0);
        do
        {
            while (validInput == false)
            {
                printf("\nChoose your game mode: \n");
                setColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY, 0);
                printf("[1] Easy Mode\n");
                setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY, 0);
                printf("[2] Normal Mode\n");
                setColor(FOREGROUND_RED | FOREGROUND_INTENSITY, 0);
                printf("[3] Hard Mode\n");
                setColor(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY, 0);
                printf("[4] Creative Mode\n");
                setColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY, 0);
                printf("[5] Setting\n");
                setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, 0);
                printf("Enter your choice: ");
                scanf("%s", &game_mode_scan);;
                if (isInteger(game_mode_scan) == true)
                {
                    game_mode = atoi(game_mode_scan);
                    validInput = true;
                } else {
                    printf("\nInvalid input! Please Try again.\n");
                }
            }
            validInput = false;
            validChoise = true;
            switch (game_mode)
            {
                case 1:
                    setColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY, 0);
                    printCentered("Easy Mode");
                    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, 0);
                    tries_number = 10;
                    limite_number = 100;
                    break;
                case 2:
                    setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY, 0);
                    printCentered("Normal Mode");
                    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, 0);
                    tries_number = 7;
                    limite_number = 100;
                    break;
                case 3:
                    setColor(FOREGROUND_RED | FOREGROUND_INTENSITY, 0);
                    printCentered("Hard Mode");
                    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, 0);
                    tries_number = 5;
                    limite_number = 100;
                    break;
                case 4:
                    setColor(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY, 0);
                    printCentered("Creative Mode");
                    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, 0);
                    while (k == 0)
                    {
                        while (validInput == false)
                        {
                            printf("\nChoose limit number :\t");
                            scanf("%s", &limite_number_scan);
                            if (isInteger(limite_number_scan))
                            {
                                limite_number = atoi(limite_number_scan);
                                if (limite_number > 0)
                                {
                                    validInput = true;
                                }
                                else
                                {
                                    printf("\nInvalid input! Please Try again.\n");
                                }
                            } else {
                                printf("\nInvalid input! Please Try again.\n");
                            }
                        }
                        validInput = false;
                        while (validInput == false)
                        {
                            printf("\nChoose number of tries :\t");
                            scanf("%s", &tries_number_scan);
                            if (isInteger(tries_number_scan))
                            {
                                tries_number = atoi(tries_number_scan);
                                if (tries_number > 0)
                                {
                                    validInput = true;
                                    k++;
                                }
                                else
                                {
                                    printf("\nInvalid input! Please Try again.\n");
                                }
                            } else {
                                printf("\nInvalid input! Please Try again.\n");
                            }
                        }
                        validInput = false;
                    }
                    break;
                case 5:
                    setColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY, 0);
                    printCentered("Setting");
                    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, 0);
                    while (l == 0)
                    {
                        printf("\n[Type : 's' to show game states, 'c' to clear the console, 'q' to quit the setting mode]\t");
                        scanf("%s", &setting_mode_replays);
                            if (setting_mode_replays == 's')
                            {
                                load(&total_game_played, &total_game_win, &total_game_lose);
                                printf("\nTotal game played : %d.", total_game_played);
                                printf("\nTotal wins : %d.", total_game_win);
                                printf("\nTotal loses : %d.\n", total_game_lose);
                            }
                            else if (setting_mode_replays == 'q')
                            {
                                restart = true;
                                printf("\n");
                                l++;
                            }
                            else if (setting_mode_replays == 'c')
                            {
                                restart = true;
                                printf("\n");
                                l++;
                                system("cls");
                            }
                            else
                            {
                                printf("\nInvalid input! Please Try again.\n");
                            }
                    }
                    break;
                default:
                    printf("\nInvalid input! Please try again.\n");
                    validChoise = false;
                    break;
            }
        } while (validChoise == false);
        if (restart == true)
        {
            i++;
            continue;
        }
        total_game_played++;
        srand(time(0));
        int the_mysterious_number = rand() % limite_number;
        printf("\nCan you guess my number between 0 and %d :), you have %d tries.\n", limite_number, tries_number);
        for(j = 1; j <= tries_number; j++)
        {
            while (validInput == false)
            {
                scanf("%s", &scaned_characters);
                if (isInteger(scaned_characters))
                {
                    scaned_number = atoi(scaned_characters);
                    if (scaned_number >= 0)
                    {
                        validInput = true;
                    }
                    else
                    {
                        printf("Oh Noo! This isn't a positive number.\n");
                    }
                } else {
                    printf("Oh Noo! This isn't an integer number.\n");
                }
            }
            if (scaned_number < the_mysterious_number)
            {
                printf("Too low, %d left\n", tries_number - j);
            }
            else if (scaned_number > the_mysterious_number)
            {
                printf("Too high, %d left\n", tries_number - j);
            }
            else if (scaned_number == the_mysterious_number)
            {
               number_found = true;
               j = tries_number + 1;
            }
            validInput = false;
        }
        validInput = false;
        if (number_found == true)
        {
            printf("\nAwsome!! You found my number %d, you found the number in %d game.\n", the_mysterious_number, game);
            game = 0;
            total_game_win++;
        }
        else
        {
            printf("\nYou Lose :(, my number was %d.\n", the_mysterious_number);
            total_game_lose++;
        }
        save(total_game_played, total_game_win, total_game_lose);
        printf("\nThank you for playing :)");
        printf("\nGame By : M4HD1\n");
        printf("\nPlay Again ? [type 'y' for yes, 'n' for no]\t");
        while (validInput == false)
        {
            scanf(" %s", &replay);
            if (replay == 'y')
            {
                k = 0;
                j = 0;
                i = 0;
                scaned_number = 0;
                game++;
                validInput = true;
                number_found = false;
            }
            else if (replay == 'n')
            {
                i++;
                validInput = true;
            }
            else
            {
                printf("\nInvalid input! Please try again.\n");
                printf("\nPlay Again ? [type 'y' for yes, 'n' for no]\t");
                validInput = false;
            }
        }
        printf("\n");
        validInput = false;
    }
    if (restart == true)
    {
        restart = false;
        main();
    }
}