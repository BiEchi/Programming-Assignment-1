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

void appendPermanentRegisterRecord(string data)
{
   system(" cat 'temporaryData.dat' >> 'permanentData.dat' ");	
   return;
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

void appendTemporaryToPermanent(string data)
{ 
   cout << endl << endl;
   appendPermanentRegisterRecord(data);
   cout << "Successfully put your information into the Permanent Database." << endl;
   return;
}

void localizeAndDeleteTemporaryRegisterRecord(string data)
{
   IOManipulations vectorIOManipulation;
   vectorIOManipulation.buildTheVectorOfPersonInformationWithIO(data);

   cout << "Successfully built your information into Data Structure inside C++." << endl;
   vectorIOManipulation.dumpTemporaryRegisterRecord(data);
   cout << "Successfully dumped your information in the Temporary Database." << endl;
}

void forwardToCentralQueue(string data)
{

}

void forwardToCentralQueueAtNoon(string data)
{
    cout << "Half a day (w.l.o.g. 1 sec) is gone." << endl;
    forwardToCentralQueue(data);
    cout << "Successfully forwarded your information to the Central Queue." << endl;
}

int main()
{
    Notifications notification;
    TemporaryRegisterRecord temporaryRegisterRecordMethods;
    notification.notifyUserAboutIntroduction();
    string data; // buffer
    temporaryRegisterRecordMethods.buildTemporaryRegisterRecord(data);
    appendTemporaryToPermanent(data);
    localizeAndDeleteTemporaryRegisterRecord(data);
    forwardToCentralQueueAtNoon(data);
   
    return 0;
}
