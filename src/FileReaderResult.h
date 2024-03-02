#include <vector>

struct FileReaderResult
{
    double maxNum;
    double minNum;
    double median;
    double mean;
    std::vector<double> ascendingSequence;
    std::vector<double> descendingSequence;
};
