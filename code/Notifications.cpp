#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <sstream>
#include "./Notifications.hpp"

using namespace std;

void Notifications::notifyUser()
{
   cout << "Enter the command you want:" << endl;
   cout << "1: register a report" << endl;
   cout << "2: read the summarize of your report" << endl;
   cout << "3: finish package of report" << endl;
   return;
}

void Notifications::notifyUserAboutIntroduction()
{
   cout << endl << endl << endl << endl;
   cout << "Author: Hao Bai, Yihong Jin, Liyang Qian, Jiahao Wei. Our team always intend to create great codes." << endl;
   cout << "Now welcome to the world of patients. Follow the directions to gain full experience. Enjoy!" << endl << endl;
}
