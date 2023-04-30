# tempenv (AUR)
A script for making temporary environments for testing

## Installation
This package is available in the arch user repository. It can be installed with
```bash
yay -S tempenv
```

This package can additionally be built and installed manually

## Building
First recursively clone the tempenv repository. The tempenv binary can be built by running `make tempenv` in the project root. The binary will then be located at `./dist/tempenv`

```bash
git clone https://github.com/FuexFollets/tempenv.git --recursive-submodule
cd tempenv
make main -j 4
```
After the building is complete, there will be a symlinked directory in the project root called `bin`. Inside this directory, the tempenv binary will be a file called main (`bin/main`).

## Recommended Usage
If a test directory is successfully created, the path to the test directory will be printed to stdout. This allows you to create a test and move to it in one line.

Example:
```bash
pushd $(tempenv -n some-test)
```

## Arguments
```
Usage: tempenv [--help] [--version] --name VAR [--in VAR] [--config VAR]

Optional arguments:
  -h, --help   	shows help message and exits 
  -v, --version	prints version information and exits 
  -n, --name   	The name of the test. Will be the name of the directory where the test will be made [required]
  -i, --in     	A path to where the test directory will be made 
  -c, --config 	The path to a different configuration file 
```

## Configuration
Configuration can be done in a TOML file. There is an example located in `./example/example_configuration.toml`. By default, this file is read from `~/.config/tempenv/config.toml`, but another path can be specified with the `--config` argument

<details>
<summary>Example configuration file</summary>
<br>

```toml
tests_location = "invalid/home/fuexfollets/tests/"

[forall_presets]
copy_with = ["/home/someuser/words.txt"]
execute_in_test_directory = [["touch", "note.txt"]]

[presets.example_preset]
copy_with = [
    "~/some-file-in-home-directory",
    "./some-file-in-current-working-directory",
]
execute_in_test_directory = [
    [
        "this",
        "is",
        "executed",
        "in",
        "the",
        "new",
        "test",
        "directory",
    ],
    [
        "and",
        "so",
        "is",
        "this",
    ],
]

[presets.cpp]
copy_with = [
    "./lib/some-library/",
    "./main.cpp",
    "/home/some-user/standard/Makefile",
]
execute_in_test_directory = [["make", "main"], ["wget", "github.com"]]
```

</details>
