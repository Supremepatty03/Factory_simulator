#pragma once

#include <string>
#include "../infrastructure/SimulationConfig.hpp"

using namespace std;

class InputFileParser {
public:
    explicit InputFileParser(const string& filePath);

    SimulationConfig parse();

private:
    const string& filePath_;

    void validateDimensions(const SimulationConfig& cfg) const;
};