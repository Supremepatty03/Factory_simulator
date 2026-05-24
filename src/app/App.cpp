#include "../../include/app/App.hpp"
#include "../../include/infrastructure/InputFileParser.hpp"
#include "../../include/application/SimulationEngine.hpp"

void App::run(const std::string& inputFilePath) {
    InputFileParser parser(inputFilePath);
    SimulationConfig config = parser.parse();

    SimulationEngine engine(config);
    engine.run();
}