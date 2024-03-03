#include <iostream>
#include <chrono>
#include "FileReader.h"
#include <filesystem>

namespace fs = std::filesystem;

bool isBadFilename(const std::string& filename) {
    // Check if the file exists
    if (!fs::exists(filename)) {
        std::cout << "File '" << filename << "' does not exist." << std::endl;
        return true;
    }
    // Check if the file is a regular file
    if (!fs::is_regular_file(filename)) {
        std::cout << "File '" << filename << "' is not a regular file." << std::endl;
        return true;
    }
    // Check if the file is empty
    std::ifstream file(filename);
    if (file.peek() == std::ifstream::traits_type::eof()) {
        std::cout << "File '" << filename << "' is empty." << std::endl;
        file.close();
        return true;
    }
    file.close();
    // File is good
    return false;
}

int main(){

    std::string filename;
    bool isBadFile = true;

    while (isBadFile) {
        std::cout << "Enter filename: ";
        std::cin >> filename;

        isBadFile = isBadFilename(filename);
    }

    // Get the start time point
    auto start = std::chrono::high_resolution_clock::now();

    FileReader* reader = new FileReader(filename);
    FileReaderResult* frResult = reader->Eval();

    // // Set the format to fixed-point notation
    // std::cout << std::fixed;
    // // Set the precision (number of decimal places)
    // std::cout << std::setprecision(10);

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

    // Get the end time point
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration between start and end time points
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Convert duration to seconds and milliseconds
    long long seconds = duration.count() / 1000;
    long long milliseconds = duration.count() % 1000;

  // Output the time elapsed in seconds and milliseconds
    std::cout << "Time elapsed: " << seconds << " seconds and " << milliseconds << " milliseconds" << std::endl;



    delete reader; 
    return 0;
}