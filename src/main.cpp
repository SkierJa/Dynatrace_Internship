// do not edit this file
#include "internship.h"

int main(int argc, char** argv) {
    std::string jsonFileName(argv[1]);
    int elementsCount(std::stoi(argv[2]));
    internship::solution(jsonFileName, elementsCount);

    return 0;
}