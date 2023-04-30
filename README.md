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

https://github.com/FuexFollets/tempenv/blob/a43b3b1fa47cbe2a4d56efb2f4f6d5c89ee056a8/example/example_configuration.toml

```toml
```
[abc](./example/example_configuration.toml)
