#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <string>

#define ToRadian(x) (float)(((x) * M_PI / 180.0f))
#define ToDegree(x) (float)(((x) * 180.0f / M_PI))

using namespace std;
class Utility
{
    bool ReadFile(const char* fileName, string& outFile);
};

#endif // UTILITY_H
