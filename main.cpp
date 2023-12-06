#include <cstdlib>

#include <iostream>

#ifdef __linux__
#include <unistd.h>
#endif

#include "hw.hpp"

static void pauseScreen();
static void clearScreen();

int main()
{
    char cmd_input = 0;

    while (cmd_input != 'q')
    {
        std::cout
            << "1: HW3-1\n"
            << "2: HW3-2\n"
            << "3: HW3-Bonus\n"
            << "q: quit\n"
            << "Enter the question number to select output result: ";
        std::cin >> cmd_input;

        switch (cmd_input)
        {
        case '1':
            HW3_1();
            break;

        case '2':
            HW3_2();
            break;

        case '3':
            HW3_Bonus();
            break;

        default:
            clearScreen();
            continue;
        }

        std::cout << std::endl;
        pauseScreen();
        clearScreen();
    }
}

static void pauseScreen()
{
#ifdef _WIN32
    std::system("pause");
#elif __linux__
    pause();
#endif
}

static void clearScreen()
{
#ifdef _WIN32
    std::system("cls");
#elif __linux__
    std::system("clear");
#endif
}