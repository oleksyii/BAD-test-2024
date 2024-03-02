#include <fstream>
#include <string>
#include <map>
#include <FileReaderResult.h>

/**
 * @brief A class that calculates data for the task 
 */
class FileReader{
public:

    FileReader();
    FileReader(std::string filename);
    
    FileReaderResult* Eval();

private:
    std::string _filename;
};