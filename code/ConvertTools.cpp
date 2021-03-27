//
//  ConvertTools.cpp
//  code
//
//  Created by Jack's Macbook Pro on 2021/3/25.
//

#include <cstring>
#include <iostream>

#include "ConvertTools.hpp"

using namespace std;

string convertFromCharArrayToString(char* charArray)
{
    string temporaryString;
    int i;
    for (i = 0; i < strlen(charArray); i++) temporaryString.push_back(charArray[i]);
    return temporaryString;
}
