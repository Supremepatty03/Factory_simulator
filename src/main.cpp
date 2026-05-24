#include <iostream>
#include <string>
#include "app/App.hpp"
// .\factory_sim.exe "D:\c++ projects\zavod\134.txt" - для запуска с файлом из примера
using namespace std;

int main(int argc, char* argv[]) {
    try {
        if (argc < 2) {
            cerr << "Missing input file path\n";
            return 1;
        }

        App app;
        app.run(argv[1]);
        return 0;
    } catch (const exception& ex) {
        cout << ex.what() << '\n';
        return 1;
    }
}