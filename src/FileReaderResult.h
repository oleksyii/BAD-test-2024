#include <vector>

struct FileReaderResult
{
    double maxNum = 0;
    double minNum = 0;
    double median = 0;
    double mean = 0;
    std::vector<double> ascendingSequence;
    std::vector<double> descendingSequence;

    // FileReaderResult()
    // {
    //     ascendingSequence = new std::vector<double>;
    //     descendingSequence = new std::vector<double>;
    // }

    // ~FileReaderResult()
    // {
    //     delete ascendingSequence;
    //     delete descendingSequence;
    // }
};
