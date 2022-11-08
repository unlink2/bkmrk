
# bkmrk

![](https://github.com/unlink2/bkmrk/actions/workflows/build.yml/badge.svg)
![](https://github.com/unlink2/bkmrk/actions/workflows/test.yml/badge.svg)

## Table of content

- [Installation](#Installation)
- [Usage](#Usage)
- [License](#License)
- [Contributing](#Contributing)
- [TODO](#TODO)

## Installation


## Usage

To use scl, make sure to install it from the scl repository and add a file called 
`usr-local.conf` to `/etc/ld.so.conf.d` with the following content: 

```
/usr/local/lib
```

then run `sudo ldconfig`

## License

This program is distributed under the terms of the MIT License.

## Contributing

All contributions are welcome.
Both pull requests and issue reports are always appreciated.
Please make sure that all existing tests pass before submitting a pull request.

## Style

- Macros and constants: MAX_SIZE
- Enums: MyEnum
- Enum Values: MYENUM_VALUE1
- Structs and Typedefs: MyStruct
- Functions: my_function()
- Internal functions: my_internal_function_()

## TODO

- Replace bkmrk with project name in README.md and makefile
