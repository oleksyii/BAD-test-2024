#include <iostream>
#include "FileReader.h"

int main(){
    FileReader* reader = new FileReader("10m.txt");
    FileReaderResult* frResult = reader->Eval();

    std::cout << "Max num is: " << frResult->maxNum << std::endl;

    delete reader; 
    return 0;
}