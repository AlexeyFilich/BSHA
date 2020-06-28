[![CodeFactor](https://www.codefactor.io/repository/github/alexeyfilich/bsha/badge/master)](https://www.codefactor.io/repository/github/alexeyfilich/bsha/overview/master)

# BSHA - Build .sh assembler for C++
BSHA is a tool for simplifying process of creating build shell files for C++ programs.

## Building
To build BSHA for Linux use:
```
$ ./build.sh
```
Built binary can be found in `bin/bsha`

## Usage
To create `build.sh` file bsha uses special `.json` files with all the configurations for program or library:
```jsonc
{
    "project": "program",
    "compiler": {
        "path": "g++",
        "flags": "-std=c++17 -static-libstdc++ -static-libgcc",
        "include_path": [
            "include/",
            "third-party/toolbox/"
        ],
        "library_path": [
            "lib/"
        ]
    },
    "main": {
        "path": "src/main.cpp",
        "output_name": "main.out",
        "flags": "",
        "binaries": ""
    },
    "sources": [
        {
            "path": "src/a.cpp",
            "flags": "",
            "binaries": ""
        }
    ],
    "extra_commands": [
        "echo Hello, world!"
    ]
}
```
Variable descriptions:

`"project"` - type of project. Possible values: `program` and `library` \
`"compiler"`: \
. . . . . `"path"` - path to compiler executable (ex: `g++`, `g++.exe`) \
. . . . . `"flags"` - compiler flags that will be used in all compiled files \
. . . . . `"include_path"` - array of string each containing include paths \
. . . . . `"include_path"` - array of string each containing library paths \
`"main"`: \
. . . . . `"path"` - path to main executable \
. . . . . `"output_name"` - name of output file \
. . . . . `"flags"` - compiler flags for main file \
. . . . . `"binaries"` - ... \
`"sources"`: \
. . . . . `"path"` - path to file \
. . . . . `"flags"` - flags for this file \
. . . . . `"binaries"` - ... \
`"extra_commands"` - commands that will be executed after successful compilation
