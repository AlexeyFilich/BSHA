#pragma once
#define SCRIPTS_H
#ifdef SCRIPTS_H

#include <string>

namespace bsha {

std::string template_json =
"{\n"
"    \"compiler_executable_path\": \"g++\",\n"
"    \"global_compiler_flags\": [\n"
"        \"-std=c++17\"\n"
"    ],\n"
"    \"main\": {\n"
"        \"file\": \"test/main.cpp\",\n"
"        \"output_name\": \"main.out\",\n"
"        \"flags\": [\n"
"        ],\n"
"        \"bin_libs\": [\n"
"        ]\n"
"    },\n"
"    \"libraries\": [\n"
"        { \"file\": \"src/lib.cpp\", \"flags\": [], \"bin_libs\": [] }\n"
"    ],\n"
"    \"include_path\": [\n"
"        \"include/\",\n"
"        \"third-party/toolbox/\"\n"
"    ],\n"
"    \"library_path\": [\n"
"    ],\n"
"    \"other_commands\": [\n"
"        \"cp build/main.out bin/main\",\n"
"        \"./bin/main\"\n"
"    ]\n"
"}\n";

std::string header =
"#!/bin/bash\n"
"# Generated using BSHA - Build .sh assembler for C++\n"
"# GitHub: https://github.com/AlexeyFilich/bsha\n"
"\n"
"if [ \"$1\" == \"--full\" ] || [ \"$1\" == \"-f\" ]; then\n"
"    rm -rf build\n"
"fi\n"
"\n"
"[ ! -d build ] && mkdir build\n"
"[ ! -d build/sources ] && mkdir build/sources\n"
"\n"
"main_should_recompile=\"True\""
"\n";

std::string compile_func =
"";

} // namespace bsha

#endif