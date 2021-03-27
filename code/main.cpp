#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <sstream>
#include <cstdlib>
#include <cstring>

#include "./Person.hpp"
#include "./TemporaryRegisterRecord.hpp"
#include "./Notifications.hpp"

using namespace std;

#include <fstream>
#include <iostream>
using namespace std;

void appendPermanentRegisterRecord(char *data)
{
   system(" cat 'temporaryData.dat' >> 'permanentData.dat' ");
   return;
}

int getTime()
{
   return clock() / (CLOCKS_PER_SEC);
}

// take 1 minute as half a day
bool halfDayIsGone(int realTimeBegin, int realTimeEnd)
{
   /* // TODO
   if (realTimeBegin - realTimeEnd) return true;
   else return false;
   */
   return true;
}

void forwardToCentralQueue(char *data)
{
}

void forwardToCentralQueueAtNoon(int realTimeBegin, int realTimeEnd, char *data)
{
   if (halfDayIsGone(realTimeBegin, realTimeEnd))
   {
      cout << "Half a day (w.l.o.g. 1 sec) is gone." << endl;
      forwardToCentralQueue(data);
      cout << "Successfully forwarded your information to the Central Queue." << endl;
   }
}

void appendTemporaryToPermanent(char *data)
{
   cout << endl
        << endl;
   appendPermanentRegisterRecord(data);
   cout << "Successfully put your information into the Permanent Database." << endl;
   return;
}

void localizeAndDeleteTemporaryRegisterRecord(char *data)
{
   IOManipulations vectorIOManipulation;
   vectorIOManipulation.buildTheVectorOfPersonInformationWithIO(data);

   cout << "Successfully built your information into Data Structure inside C++." << endl;
   vectorIOManipulation.dumpTemporaryRegisterRecord(data);
   cout << "Successfully dumped your information in the Temporary Database." << endl;
}

int main()
{
   Notifications notification;
   TemporaryRegisterRecord temporaryRegisterRecordMethods;
   int userCommandType;

   notification.notifyUserAboutIntroduction();
   // 声明变量data
   char data[100]; // buffer
   int realTimeBegin = getTime();
   // 代入data
   temporaryRegisterRecordMethods.buildTemporaryRegisterRecord(userCommandType, data);
   appendTemporaryToPermanent(data);
   localizeAndDeleteTemporaryRegisterRecord(data);
   int realTimeEnd = getTime();
   forwardToCentralQueueAtNoon(realTimeBegin, realTimeEnd, data);

   return 0;
}
