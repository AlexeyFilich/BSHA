/*
./build.sh && ./bin/main
*/

#include <iostream>
#include <fstream>
#include <string>

#include "ColorType/ColorType.h"
#include "JSON.hpp"
#include "argp/argp.hpp"
#include "stringtools/stringtools.hpp"
#include "templates.h"

std::string getFlags(JSON::json json) {
    std::string flags = "";
    for (int i = 0; i < json.size(); i++) {
        if (std::string(json[i])[0] != '-')
            flags += "-";
        flags += std::string(json[i]);
        if (i != json.size() - 1)
            flags += " ";
    }
    if (flags.size() == 0)
        flags = "\b";
    return flags;
}

std::string getPath(JSON::json json, std::string ch) {
    std::string path = "";
    for (int i = 0; i < json.size(); i++) {
        path += "-" + ch + "\"" + std::string(json[i]) + "\"";
        if (i != json.size() - 1)
            path += " ";
    }
    if (path.size() == 0)
        path = "\b";
    return path;
}

int main(int argc, char *argv[]) {
    bool generate_new = false;
    std::string json_file_path = "build.json";
    argp::Options options("BSHA", "Build .sh assembler for C++");
    options.addOption("g", "generate", "Generate new BSHA JSON file", &generate_new);
    options.addOption("f", "file", "File to generate .sh script from. If --generate is set, file name will be used for new JSON file", &json_file_path);
    options.parse(argc, argv);

    if (generate_new) {
        std::ofstream out(json_file_path);
        out << bsha::template_json;
        out.close();
        exit(0);
    }

    colortype::setColorMode(colortype::Mode::BIT_8);
    // std::cout << colortype::getFormattedString("Welcome to BSHA", colortype::Colors::BRIGHT_CYAN, colortype::Colors::GREEN, true, false, true);

    try {
        JSON::json json;
        {
            std::ifstream input_file(json_file_path);
            input_file >> json;
            input_file.close();
        }
        std::string compiler_command = "{compiler} {include_path} {library_path} {global_flags} {c} {local_flags} -o {output} {input_main} {input_libs}";
        compiler_command = stringtools::replaceAllInstances(compiler_command, "{compiler}", json["compiler_executable_path"]);
        compiler_command = stringtools::replaceAllInstances(compiler_command, "{include_path}", getPath(json["include_path"], "I"));
        compiler_command = stringtools::replaceAllInstances(compiler_command, "{library_path}", getPath(json["library_path"], "L"));
        compiler_command = stringtools::replaceAllInstances(compiler_command, "{global_flags}", getFlags(json["global_compiler_flags"]));
        std::cout << compiler_command;
    } catch (const std::exception& e) {
        std::cout << "Internal error occured during execution:\n" << e.what() << "\n";
    }

    return 0;
}