#include <iostream>
#include "FileReader.h"

int main(){
    FileReader* reader = new FileReader("10m.txt");
    FileReaderResult* frResult = reader->Eval();

       // Set the format to fixed-point notation
    std::cout << std::fixed;
    // Set the precision (number of decimal places)
    std::cout << std::setprecision(10);

    std::cout << "Max num is: " << frResult->maxNum << std::endl;
    std::cout << "Min num is: " << frResult->minNum << std::endl;
    std::cout << "Median num is: " << frResult->median << std::endl;
    std::cout << "Mean num is: " << frResult->mean << std::endl;

    std::cout << "Longest ascending sequence: ";
    for (const auto& num : frResult->ascendingSequence) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "Longest descending sequence: ";
    for (const auto& num : frResult->descendingSequence) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    delete reader; 
    return 0;
}