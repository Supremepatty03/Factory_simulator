#pragma once

#include <fstream>
#include <optional>
#include <string>

using namespace std;

class TokenReader {
public:
    explicit TokenReader(const string& path);

    bool nextLine();

    const string& currentLine() const;
    size_t currentLineNumber() const;

    bool readInt(long long& value);

    bool hasOnlyWhitespaceLeft() const;
    

private:
    std::ifstream input_;
    std::string currentLine_;
    std::size_t currentLineNumber_ = 0;
    std::size_t cursor_ = 0;

    void skipSpaces();
};