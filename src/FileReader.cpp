#include "FileReader.h"

FileReader::FileReader()
{
    this->_result = new FileReaderResult;
};

FileReader::FileReader(std::string filename) : _filename(filename)
{
    this->_result = new FileReaderResult;
}

FileReader::~FileReader()
{
    delete _result;
}

void FileReader::setFileName(std::string filename)
{
    this->_filename = filename;
}

std::string FileReader::getFileName()
{
    return _filename;
}

void FileReader::findMaxAndMin()
{
    std::ifstream file(this->_filename, std::ios::in);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << _filename << std::endl;
        {
            std::lock_guard<std::mutex> lock(_resultMutex);             // Lock the mutex
            _result->maxNum = std::numeric_limits<double>::quiet_NaN(); // Return NaN if file cannot be opened
        }
    }

    double maxValue = -std::numeric_limits<double>::infinity(); // Initialize to negative infinity
    double minValue = std::numeric_limits<double>::infinity(); // Initialize to positive infinity

    double value;
    while (file >> value)
    {
        if (value > maxValue)
        {
            maxValue = value;
        }
        if (value < minValue)
        {
            minValue = value;
        }
    }

    file.close();
    {
        std::lock_guard<std::mutex> lock(_resultMutex); // Lock the mutex
        _result->maxNum = maxValue;
        _result->minNum = minValue;
    }

    return;
}

void FileReader::findMedianAndMean()
{
    std::ifstream file(this->_filename, std::ios::in);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << _filename << std::endl;
        {
            std::lock_guard<std::mutex> lock(_resultMutex);             // Lock the mutex
            _result->median = std::numeric_limits<double>::quiet_NaN(); // Return NaN if file cannot be opened
        }
    }

    std::vector<double> values; // All values
    double sum = 0.0;
    double value;
    while (file >> value) {
        values.push_back(value);
        sum += value;
    }
    file.close();
    

    if (values.empty()) {
        std::lock_guard<std::mutex> lock(_resultMutex); // Lock the mutex
        std::cerr << "No values found in file: " << _filename << std::endl;
        _result->median = std::numeric_limits<double>::quiet_NaN(); // Return NaN if file is empty
        _result->mean = std::numeric_limits<double>::quiet_NaN(); // Return NaN if file is empty
        return;
    }


    // Calculate the mean (average)
    {
        std::lock_guard<std::mutex> lock(_resultMutex); // Lock the mutex
        _result->mean = sum / values.size();
    }


    // Sort the values
    std::sort(values.begin(), values.end());

    // Calculate the median
    size_t size = values.size();
    {
        std::lock_guard<std::mutex> lock(_resultMutex); // Lock the mutex
        if (size % 2 == 0)
        {
            _result->median = (values[size / 2 - 1] + values[size / 2]) / 2.0;
        }
        else
        {
            _result->median = values[size / 2];
        }
    }

    return;
}

// Function to find the longest ascending and descending sequence of numbers in a file
void FileReader::findAscendingAndDescendingSequence() {
    std::ifstream file(_filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << _filename << std::endl;
        return;
    }

    double value;
    double prevValue = std::numeric_limits<double>::infinity();
    std::vector<double> ascendingSequence;
    std::vector<double> maxAscendingSequence;
    std::vector<double> descendingSequence;
    std::vector<double> maxDescendingSequence;

    while (file >> value) {
        if (value > prevValue) {
            ascendingSequence.push_back(value);
            if (ascendingSequence.size() > maxAscendingSequence.size()) {
                maxAscendingSequence = ascendingSequence;
            }
            descendingSequence.clear(); // Reset descending sequence
        } else if (value < prevValue) {
            descendingSequence.push_back(value);
            if (descendingSequence.size() > maxDescendingSequence.size()) {
                maxDescendingSequence = descendingSequence;
            }
            ascendingSequence.clear(); // Reset ascending sequence
        } else {
            ascendingSequence.clear(); // Reset both sequences
            descendingSequence.clear();
        }
        prevValue = value;
    }

    file.close();

    {
        std::lock_guard<std::mutex> lock(_resultMutex); // Lock the mutex
        _result->ascendingSequence = maxAscendingSequence;
        _result->descendingSequence = maxDescendingSequence;
    }

    return;


}

FileReaderResult* FileReader::Eval()
{
    std::vector<std::thread> threads;

    void (FileReader::*funcPtrArr[])() = {&FileReader::findMaxAndMin, &FileReader::findMedianAndMean, &FileReader::findAscendingAndDescendingSequence};

    for (auto funcPtr : funcPtrArr) {
        threads.push_back(std::thread(funcPtr, this));
    }

    // Join all threads
    for (auto& thread : threads) {
        thread.join();
    }

    return _result;
}