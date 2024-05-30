#include "Solver.h"
#include "Exception.h"

Solver::Solver(const std::unordered_map<char, std::bitset<5>>& alphabet, const std::unordered_map<std::bitset<5>, char>& antiAlphabet) : alphabet(alphabet), antiAlphabet(antiAlphabet), NumChunk(0) {}

void Solver::encodeFile(const std::string& inputFileName, const std::string& outputFileName, int NumThread) {
    std::ifstream inputFile(inputFileName);
    if (!inputFile) {
        throw SolverException("Error: Couldn't open input file: " + inputFileName);
    }

    std::ofstream outputFile(outputFileName, std::ios::binary | std::ios::trunc);
    if (!outputFile) {
        throw SolverException("Error: Couldn't open input file: " + outputFileName);
    }

    std::vector<std::string> HelpFiles;
    std::vector<std::thread> threads;
    std::string chunk;
    char ch;
    std::string chunkPart;
    int CHARS_PER_CHUNK = NumThread*CHARS_PER_THREAD_ENCODE;

    while (inputFile.get(ch)) {
        if (alphabet.find(ch) == alphabet.end()) {
            throw SolverException("Error: Character not found in alphabet: " + std::string(1, ch));
        }
        chunkPart += ch;
        if (chunkPart.length() == CHARS_PER_CHUNK) {
            for (int i = 0; i < NumThread; i++) {
                int currentNumChunk = NumChunk++;
                std::string outputFileName2 = std::to_string(currentNumChunk) + "HelpFileToEncode.bin";
                HelpFiles.push_back(outputFileName2);
                std::string threadChunk = chunkPart.substr(i * CHARS_PER_THREAD_ENCODE, CHARS_PER_THREAD_ENCODE);
                threads.emplace_back([this, threadChunk, outputFileName2]() {
                    encodeChunk(threadChunk, outputFileName2);
                });
            }
            chunkPart.clear();
            for (int i = 0; i < NumThread; i++) {
                threads[i].join();
            }
            threads.clear();
        }
    }

    if (!chunkPart.empty()) {
        int FullThreads = chunkPart.size()/ CHARS_PER_THREAD_ENCODE;
        int RemainingChars = chunkPart.size() - FullThreads * CHARS_PER_THREAD_ENCODE;
        for (int i = 0; i < FullThreads; i++) {
            int currentNumChunk = NumChunk++;
            std::string outputFileName2 = std::to_string(currentNumChunk) + "HelpFileToEncode.bin";
            HelpFiles.push_back(outputFileName2);
            std::string threadChunk = chunkPart.substr(i * CHARS_PER_THREAD_ENCODE, CHARS_PER_THREAD_ENCODE);
            threads.emplace_back([this, threadChunk, outputFileName2]() {
                encodeChunk(threadChunk, outputFileName2);
            });
        }
        if (RemainingChars != 0){
            int currentNumChunk = NumChunk++;
            std::string outputFileName2 = std::to_string(currentNumChunk) + "HelpFileToEncode.bin";
            HelpFiles.push_back(outputFileName2);
            std::string threadChunk = chunkPart.substr(FullThreads * CHARS_PER_THREAD_ENCODE, RemainingChars );
            threads.emplace_back([this, threadChunk, outputFileName2]() {
                encodeChunk(threadChunk, outputFileName2);
            });
            FullThreads+=1;
        }
        chunkPart.clear();
        for (int i = 0; i < FullThreads ; i++) {
            threads[i].join();
        }
        threads.clear();
    }

    inputFile.close();

    for (auto& thread : threads) {
        thread.join();
    }

    for (const auto& inputFileName : HelpFiles) {
        std::ifstream inputFile(inputFileName, std::ios::binary);
        if (!inputFile) {
            throw SolverException("Error: Couldn't open input file: " + inputFileName);
        }
        outputFile << inputFile.rdbuf();

        inputFile.close();
        remove(inputFileName.c_str());
    }

    outputFile.close();
}


void Solver::encodeChunk(const std::string& chunk, const std::string& outputFileName) {
    std::ofstream outputFile(outputFileName, std::ios::binary | std::ios::trunc);
    if (!outputFile) {
        throw SolverException("Error: Couldn't open input file: " + outputFileName);
    }

    std::string buffer;

    for (char ch : chunk) {
        if (alphabet.find(ch) == alphabet.end()) {
            throw SolverException("Error: No char in alphabet " + ch);
        }
        buffer.push_back(ch);
        if (buffer.size() == CHARS_PER_TRIPLE) {
            std::bitset<BITS_PER_TRIPLE> encodedValue = encodeTriple(buffer);
            uint16_t encodedValue_int = encodedValue.to_ulong();
            outputFile.write(reinterpret_cast<const char*>(&encodedValue_int), sizeof(encodedValue_int));
            buffer.clear();
        }
    }

    if (!buffer.empty()) {
        while (buffer.size() < CHARS_PER_TRIPLE) {
            buffer.push_back(' ');
        }
        std::bitset<BITS_PER_TRIPLE> encodedValue = encodeTriple(buffer);
        uint16_t encodedValue_int = encodedValue.to_ulong();
        outputFile.write(reinterpret_cast<const char*>(&encodedValue_int), sizeof(encodedValue_int));
    }

    outputFile.close();
}

void Solver::decodeFile(const std::string& inputFileName, const std::string& outputFileName, int NumThread) {
    std::ifstream inputFile(inputFileName, std::ios::binary);
    if (!inputFile) {
        throw SolverException("Error: Couldn't open input file: " + inputFileName);
    }

    std::ofstream outputFile(outputFileName, std::ios::trunc);
    if (!outputFile) {
        throw SolverException("Error: Couldn't open input file: " + outputFileName);
    }
    outputFile.close();

    std::vector<std::string> HelpFiles;
    std::vector<std::thread> threads;
    std::vector<uint16_t> chunkPart;
    uint16_t encodedValue_int;
    int INT_PER_CHUNK = NumThread*CHUNKS_PER_THREAD;
    while (inputFile.read(reinterpret_cast<char*>(&encodedValue_int), sizeof(encodedValue_int))) {
        chunkPart.push_back(encodedValue_int);
        if (chunkPart.size() == INT_PER_CHUNK) {
            for (int i = 0; i < NumThread; i++) {
                int currentNumChunk = NumChunk++;
                std::string outputFileName2 = std::to_string(currentNumChunk) + "HelpFileToDecode.txt";
                HelpFiles.push_back(outputFileName2);
                auto start = chunkPart.begin() + i * CHUNKS_PER_THREAD;
                auto end = start + CHUNKS_PER_THREAD;
                std::vector<uint16_t> threadChunk(start, end);
                threads.emplace_back([this, threadChunk, outputFileName2]() {
                    decodeChunk(threadChunk, outputFileName2);
                });
            }
            for (auto& thread : threads) {
                thread.join();
            }
            threads.clear();
            chunkPart.clear();
        }
    }

    if (!chunkPart.empty()) {
        int FullThreads = chunkPart.size() / CHUNKS_PER_THREAD;
        int RemainingInt = chunkPart.size() - FullThreads*CHUNKS_PER_THREAD;
        for (int i = 0; i < FullThreads; i++) {
            int currentNumChunk = NumChunk++;
            std::string outputFileName2 = std::to_string(currentNumChunk) + "HelpFileToDecode.txt";
            HelpFiles.push_back(outputFileName2);
            auto start = chunkPart.begin() + i * CHUNKS_PER_THREAD;
            auto end = start + CHUNKS_PER_THREAD;
            std::vector<uint16_t> threadChunk(start, end);
            threads.emplace_back([this, threadChunk, outputFileName2]() {
                decodeChunk(threadChunk, outputFileName2);
            });
        }
        if (RemainingInt != 0){
            int currentNumChunk = NumChunk++;
            std::string outputFileName2 = std::to_string(currentNumChunk) + "HelpFileToDecode.txt";
            HelpFiles.push_back(outputFileName2);
            auto start = chunkPart.begin() + FullThreads * CHUNKS_PER_THREAD;
            auto end = start + RemainingInt;
            std::vector<uint16_t> threadChunk(start, end);
            threads.emplace_back([this, threadChunk, outputFileName2]() {
                decodeChunk(threadChunk, outputFileName2);
            });
            FullThreads+=1;
        }
        chunkPart.clear();
        for (int i = 0; i < FullThreads; i++) {
            threads[i].join();
        }
        threads.clear();
    }

    inputFile.close();

    std::ofstream finalOutputFile(outputFileName, std::ios::binary | std::ios::app);
    if (!finalOutputFile) {
        throw SolverException("Error: Couldn't open input file: " + outputFileName);
    }

    for (const auto& helpFileName : HelpFiles) {
        std::ifstream inputHelpFile(helpFileName);
        if (!inputHelpFile) {
            throw SolverException("Error: Couldn't open input file: " + helpFileName);
        }
        finalOutputFile << inputHelpFile.rdbuf();

        inputHelpFile.close();
        remove(helpFileName.c_str());
    }

    finalOutputFile.close();
}

void Solver::decodeChunk(const std::vector<uint16_t>& chunk, const std::string& outputFileName) {
    std::ofstream outputFile(outputFileName, std::ios::binary);
    if (!outputFile) {
        throw SolverException("Error: Couldn't open input file: " + outputFileName);
    }

    for (const auto& encodedValue_int : chunk) {
        std::bitset<BITS_PER_TRIPLE> buffer(encodedValue_int);
        std::string decodetriple = decodeTriple(buffer);
        outputFile.write(decodetriple.c_str(), decodetriple.size());
    }
    outputFile.close();
}

std::string Solver::decodeTriple(const std::bitset<16>& codetriple) {
    std::string codetriple_str = codetriple.to_string();
    std::bitset<5> code1(codetriple_str.substr(0, 5));
    std::bitset<5> code2(codetriple_str.substr(5, 5));
    std::bitset<5> code3(codetriple_str.substr(10, 5));

    std::string result;
    result.push_back(antiAlphabet.at(code1));
    result.push_back(antiAlphabet.at(code2));
    result.push_back(antiAlphabet.at(code3));

    return result;
}

std::bitset<16> Solver::encodeTriple(const std::string& triple) {
    std::bitset<5> code1 = alphabet.at(triple[0]);
    std::bitset<5> code2 = alphabet.at(triple[1]);
    std::bitset<5> code3 = alphabet.at(triple[2]);

    std::bitset<16> result = (code1.to_ulong() << 11) | (code2.to_ulong() << 6) | (code3.to_ulong() << 1);

    return result;
}








