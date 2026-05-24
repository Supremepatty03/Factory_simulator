#include "infrastructure/TokenReader.hpp"

#include <charconv>
#include <cctype>
#include <system_error>

using namespace std;

TokenReader::TokenReader(const string& path)
    : input_(path) {}

bool TokenReader::nextLine() {
    if (!getline(input_, currentLine_)) {
        return false;
    }

    ++currentLineNumber_;
    cursor_ = 0;
    return true;
}

void TokenReader::skipSpaces() {
    while (cursor_ < currentLine_.size() &&
           isspace(static_cast<unsigned char>(currentLine_[cursor_]))) {
        ++cursor_;
    }
}

bool TokenReader::readInt(long long& value) {
    skipSpaces();

    if (cursor_ >= currentLine_.size()) {
        return false;
    }

    const char* begin = currentLine_.data() + cursor_;
    const char* end = currentLine_.data() + currentLine_.size();

    long long parsed = 0;
    auto [ptr, ec] = from_chars(begin, end, parsed);

    if (ec != errc() || ptr == begin) {
        return false;
    }

    cursor_ = static_cast<size_t>(ptr - currentLine_.data());
    value = parsed;
    return true;
}

bool TokenReader::hasOnlyWhitespaceLeft() const {
    size_t pos = cursor_;
    while (pos < currentLine_.size() &&
           isspace(static_cast<unsigned char>(currentLine_[pos]))) {
        ++pos;
    }
    return pos >= currentLine_.size();
}

const string& TokenReader::currentLine() const {
    return currentLine_;
}

size_t TokenReader::currentLineNumber() const {
    return currentLineNumber_;
}