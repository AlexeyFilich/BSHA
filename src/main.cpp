/*
g++ -std=c++17 -static-libstdc++ -static-libgcc -I"include/" -I"third-party/toolbox" src/main.cpp -o bin/bsha
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "ColorType/ColorType.h"
#include "JSON.hpp"
#include "argp/argp.hpp"
#include "stringtools/stringtools.hpp"
#include "templates.h"

int main(int argc, char *argv[]) {
    bool generate_new = false;
    std::string json_file_path = "build.json";
    std::string outfile = "build.sh";
    argp::Options options("BSHA", "Build .sh assembler for C++");
    options.addOption("g", "generate", "Generate new BSHA JSON file", &generate_new);
    options.addOption("f", "file", "File to generate .sh script from. If --generate is set, file name will be used for new JSON file", &json_file_path);
    options.addOption("o", "output", "file .sh script will be generated to.", &outfile);
    options.parse(argc, argv);

    if (generate_new) {
        std::ofstream out(json_file_path);
        out << bsha::template_json;
        out.close();
        exit(0);
    }

    colortype::setColorMode(colortype::Mode::BIT_8);

    std::vector<std::string> obj(0);

    try {
        JSON::json json;
        {
            std::ifstream input_file(json_file_path);
            input_file >> json;
            input_file.close();
        }
        std::string compiler = (std::string)json["compiler"]["path"];
        std::string gflags = (std::string)json["compiler"]["flags"];
        if (gflags != "")
            gflags = " " + gflags;
        std::string cpath = "";
        for (int i = 0; i < json["compiler"]["include_path"].size(); i++)
            cpath += " -I\"" + (std::string)json["compiler"]["include_path"][i] + "\"";
        for (int i = 0; i < json["compiler"]["library_path"].size(); i++)
            cpath += " -L\"" + (std::string)json["compiler"]["library_path"][i] + "\"";

        // std::cout << bsha::header << "Hi\n";

        std::string output = stringtools::replaceAllInstances(bsha::header, "{total}", std::to_string(json["sources"].size() + 1));
        output = stringtools::replaceAllInstances(output, "{compiler}", compiler);

        for (auto item : json["sources"]) {
            std::string path_src = (std::string)item["path"];
            std::size_t found = path_src.find_last_of("/\\");
            std::string path = path_src.substr(0, found + 1);
            std::string file_ext = path_src.substr(found + 1);
            std::string file = file_ext.substr(0, file_ext.find_last_of("."));
            std::string lobj = "build/" + path + file + ".o";
            obj.push_back(lobj);

            std::string lflags = (std::string)item["flags"];
            if (lflags != "")
                lflags = " " + lflags;

            output += "recompile=\"False\"\n";
            output += "printHeader " + path_src + "\n";
            output += "checkRecomp " + path_src + " build/" + path + file + ".hash build/" + path + " build/" + path + file + ".o \n";
            output += "if [ $recompile == \"True\" ]\nthen\n";
            output += "    ";
            output += compiler + " -c" + gflags + lflags + cpath + " " + path_src + " -o " + lobj + " " + (std::string)item["binaries"];
            output += "\n    checkSuccess " + lobj + " build/" + path + file + ".hash\n    echo \"$(md5sum " + path_src + ")\" > build/" + path + file + ".hash\nfi\n";

            output += "\n";
        }

        {
            std::string path_src = (std::string)json["main"]["path"];
            std::size_t found = path_src.find_last_of("/\\");
            std::string path = path_src.substr(0, found + 1);
            std::string file_ext = path_src.substr(found + 1);
            std::string file = file_ext.substr(0, file_ext.find_last_of("."));
            std::string mout = (std::string)json["main"]["output_name"];

            std::string lflags = (std::string)json["main"]["flags"];
            if (lflags != "")
                lflags = " " + lflags;

            output += "recompile=\"False\"\n";
            output += "printHeader " + path_src + "\n";
            output += "checkRecomp " + path_src + " build/" + path + file + ".hash build/" + path + " build/" + path + file + ".o \n";
            output += "if [ $recompile == \"True\" ] || [ $main_should_recompile == \"True\" ]\nthen\n";
            output += "    ";
            output += compiler + gflags + lflags + cpath + " " + path_src + " -o build/" + path + mout + " " + (std::string)json["main"]["binaries"];
            for (auto item : obj)
                output += " " + item;
            output += "\n    checkSuccess build/" + path + mout + " build/" + path + file + ".hash\n    echo \"$(md5sum " + path_src + ")\" > build/" + path + file + ".hash\nfi\n";
        }

        {
            output += "\n";
            for (auto subcmd : json["extra_commands"])
                output += (std::string)subcmd + "\n";
        }

        {
            output += "\n";
            output += "printf -- \"\\n\\e[38;05;2;49;24;27mDone! in \\e[0m\e[38;05;3;49;04;27m$(($(date '+%s') - $start))sec.\e[0m\\n\"\n";
        }

        {
            std::ofstream output_file(outfile);
            output_file << output;
            output_file.close();
        }

    } catch (const std::exception& e) {
        std::cout << "Internal error occurred during execution:\n" << e.what() << "\n";
    }

    return 0;
}
