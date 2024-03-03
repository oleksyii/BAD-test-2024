#ifndef FILE_READER 
#define FILE_READER 

#include <string>
#include <map>
#include <thread>
#include <fstream>
#include <mutex>
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "FileReaderResult.h"



/**
 * @brief A class that calculates data for the task 
 */
class FileReader{
public:

    FileReader();
    FileReader(std::string filename);
    ~FileReader();
    
    FileReaderResult* Eval();

    void setFileName(std::string filename);
    std::string getFileName();

private:
    FileReaderResult* _result;
    std::string _filename;

    std::mutex _resultMutex;

    void findMaxAndMin();
    void findMedianAndMean();
    void findAscendingAndDescendingSequence();
};

#endif
