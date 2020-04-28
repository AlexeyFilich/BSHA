# BSHA - Build .sh assembler for C++
BSHA is a tool for simplifying process of creating build shell files for C++ programs using g++.

## Building
To build BSHA for Linux use:
```
$ ./build.sh
```
Built file will be located at `bin/bsha`

## Usage
To create `build.sh` file you need to create `.json` file with all the configurations required:
```jsonc
{
    // Main file to compile
    "main_executable": "src/main.cpp",

    // Main output file name
    "executable_output_name": "main.out",
    
    // Compiler flags for main file
    "compiler_flags": [
        "-std=c++17"
    ],

    // Binary libraries for main file
    "bin_libraries": [

    ],

    "libraries": [
        {
            "path": "src/test.cpp", // test.h must be in the same folder or in folder specified in "include_path"
            "flags": [
                "-std=c++17"
            ],
            "bin_libraries": [
        
            ]
        }
    ],

    // Path to search for .h or .hpp files
    "include_path": [
        "include"
    ],

    // Path to search for binary libraries
    "library_path": [

    ],

    "other_commands": [
        "mv build/main.out bin/bsha" // This command will be executed after compiling all files
    ]
}
```
Then type:
```
$ bsha json_file_name.json
```
Your build.json will be located in the folder, where command was executed