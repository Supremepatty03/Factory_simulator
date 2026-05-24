#include "infrastructure/InputFileParser.hpp"

#include <limits>
#include <string>
#include <utility>
#include "infrastructure/TokenReader.hpp"
#include "infrastructure/ValidationError.hpp"

namespace {
constexpr long long kMaxM = 100;
constexpr long long kMaxN = 100;
constexpr long long kMaxT = 10000;
constexpr long long kMaxTotalProducts = 100000;
}

using namespace std;

InputFileParser::InputFileParser(const string& filePath)
    : filePath_(move(filePath)) {}

SimulationConfig InputFileParser::parse() {
    TokenReader reader(filePath_);
    SimulationConfig cfg;

    long long m = 0;
    long long n = 0;

    if (!reader.nextLine()) {
        throw ValidationError("Unexpected end of file");
    }

    if (!reader.readInt(m) || !reader.readInt(n) || !reader.hasOnlyWhitespaceLeft()) {
        throw ValidationError(reader.currentLine());
    }

    if (m < 1 || m > kMaxM || n < 1 || n > kMaxN) {
        throw ValidationError(reader.currentLine());
    }

    cfg.M = static_cast<int>(m);
    cfg.N = static_cast<int>(n);

    cfg.processingTime.assign(cfg.M - 1, vector<domain::Time>(cfg.N, 0));

    for (int i = 0; i < cfg.M - 1; ++i) {
        if (!reader.nextLine()) {
            throw ValidationError("Unexpected end of file");
        }

        for (int j = 0; j < cfg.N; ++j) {
            long long t = 0;
            if (!reader.readInt(t)) {
                throw ValidationError(reader.currentLine());
            }
            if (t < 0 || t > kMaxT) {
                throw ValidationError(reader.currentLine());
            }
            cfg.processingTime[i][j] = static_cast<domain::Time>(t);
        }

        if (!reader.hasOnlyWhitespaceLeft()) {
            throw ValidationError(reader.currentLine());
        }
    }

    cfg.initialQueues.assign(cfg.N, {});

    long long totalProducts = 0;
    const long long maxType = static_cast<long long>(cfg.M) - 2;

    for (int j = 0; j < cfg.N; ++j) {
        if (!reader.nextLine()) {
            throw ValidationError("Unexpected end of file");
        }

        long long q = 0;
        if (!reader.readInt(q)) {
            throw ValidationError(reader.currentLine());
        }

        if (q < 0) {
            throw ValidationError(reader.currentLine());
        }

        if (totalProducts + q > kMaxTotalProducts) {
            throw ValidationError(reader.currentLine());
        }

        cfg.initialQueues[j].reserve(static_cast<size_t>(q));

        for (long long p = 0; p < q; ++p) {
            long long type = 0;
            if (!reader.readInt(type)) {
                throw ValidationError(reader.currentLine());
            }

            if (type < 0 || type > maxType) {
                throw ValidationError(reader.currentLine());
            }

            cfg.initialQueues[j].push_back(static_cast<domain::TypeId>(type));
        }

        if (!reader.hasOnlyWhitespaceLeft()) {
            throw ValidationError(reader.currentLine());
        }

        totalProducts += q;
    }

    return cfg;
}