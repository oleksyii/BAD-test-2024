#include <vector>

struct FileReaderResult
{
    double maxNum;
    double minNum;
    double median;
    double mean;
    std::vector<double> *ascendingSequence;
    std::vector<double> *descendingSequence;

    FileReaderResult()
    {
        ascendingSequence = new std::vector<double>;
        descendingSequence = new std::vector<double>;
    }

    ~FileReaderResult()
    {
        delete ascendingSequence;
        delete descendingSequence;
    }
};
