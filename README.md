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
