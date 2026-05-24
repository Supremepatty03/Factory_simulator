#include "../../include/app/App.hpp"
#include "../../include/infrastructure/InputFileParser.hpp"
#include "../../include/application/SimulationEngine.hpp"

using namespace std;

void App::run(const string& inputFilePath) {
    InputFileParser parser(inputFilePath);
    SimulationConfig config = parser.parse();

    SimulationEngine engine(config);
    engine.run();
}