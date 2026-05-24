#pragma once
#include <stdexcept>
#include <string>

using namespace std;

class ValidationError final : public runtime_error {
public:
    explicit ValidationError(const string& message)
        : runtime_error(message) {}
};