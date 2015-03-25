#include "utility.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <fstream>

bool ReadFile(const char* pFileName, string& outFile)
{
    ifstream f(pFileName);

    bool ret = false;

    if (f.is_open()){
        string line;
        while (getline(f, line)){
            outFile.append(line);
            outFile.append("\n");
        }

        f.close();

        ret = true;
    }
    else{
        //--TODO some warning msg
        printf("read file  error");
    }
    return ret;
}




