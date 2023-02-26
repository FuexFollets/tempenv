# tempenv
A script for making temporary environments for testing

# Building
First recursively clone the tempenv repository. The tempenv binary can be built by running `make tempenv` in the project root. The binary will then be located at `./dist/tempenv`

```bash
git clone https://github.com/FuexFollets/tempenv.git --recursive-submodule
cd tempenv
make tempenv
mv ./dist/tempenv (another location in PATH)
```

# Reccomended Usage
If a test directory is successfully created, the path to the test directory will be printed to stdout. This allows you to create a test and move to it in one line.

Example:
```bash
cd $(tempenv --name some-test)
```

# Arguments
```
Usage: tempenv [--help] [--version] --name VAR [--in VAR] [--config VAR]

Optional arguments:
  -h, --help   	shows help message and exits 
  -v, --version	prints version information and exits 
  -n, --name   	The name of the test. Will be the name of the directory where the test will be made [required]
  -i, --in     	A path to where the test directory will be made 
  -c, --config 	The path to a different configuration file 
```

# Configuration
Configuration can be done in a `.toml` file. There is an example located in `./example/example_configuration.toml`. By deafult, this file is read from `~/.config/tempenv/config.toml`, but another path can be specified with the `--config` argument
