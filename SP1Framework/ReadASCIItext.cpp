#include "readASCIItext.h"

std::vector<std::string> readfile(std::string filename)
{
    std::ifstream readfile(filename);
    std::string outputStr;
    std::vector<std::string> returnVec;
    while (std::getline(readfile, outputStr)) {
        returnVec.push_back(outputStr);
    }
    return returnVec;
}
