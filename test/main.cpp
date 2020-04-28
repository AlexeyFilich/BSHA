#include <iostream>
#include <string>

// #include "ColorType.h"
#include "argp/argp.hpp"
#include "ColorType/ColorType.h"
#include "JSON.hpp"

int main(int argc, char *argv[]) {
    bool generateNew = false;
    std::string jsonFilePath = "";
    argp::Options options("BSHA", "Build .sh assembler for C++");
    options.addOption("-g", "--generate", "Generate new BSHA JSON file", &generateNew);
    options.addOption("-f", "--file", "File to generate .sh script from. If --generate is set, file name will be used for new JSON file", &jsonFilePath);
    std::cout << colortype::getFormattedString("Welcome to BSHA", colortype::Colors::BRIGHT_CYAN, colortype::Colors::GREEN, colortype::Mode::BIT_8, true, false, true);
}