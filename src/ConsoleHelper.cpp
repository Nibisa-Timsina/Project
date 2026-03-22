#include "../include/ConsoleHelper.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <iomanip>
using namespace std;
void ConsoleHelper::SetColor(int ColorCode)
{
    static bool utf8_initialized = false;
    if (!utf8_initialized) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleOutputCP(65001); // UTF-8
        SetConsoleCP(65001); // UTF-8
        utf8_initialized = true;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ColorCode);
}
void ConsoleHelper::ResetColor()
{
    SetColor(7);
}
void ConsoleHelper::ClearScreen() 
{
    system("cls"); 
}
void ConsoleHelper::PrintError() 
{
    SetColor(12);
    cout << "Error :(" << endl; 
}
void ConsoleHelper::PrintDivider()
{
    cout << setfill('-') << setw(10) << endl;
}
void ConsoleHelper::PrintSuccess()
{
    SetColor(10);
    cout << "SUCCESS :)" << endl;
}
void ConsoleHelper::PrintHeader(std::string title)
{
    SetColor(11);
    cout << setfill('-') << setw(10) << endl;
    cout << "  " << title << endl;
    cout << setfill('-') << setw(10) << endl;
} 