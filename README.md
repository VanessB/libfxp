# libfxp
Cross-platform fixed point maths library with a support of macro templates written fully on C.

[Russian/Русский](./README_ru.md)

## Description
This library provides you with type-generic functions that perform fixed point calculations.
All operatable types are standard fixed size integers (see `inttypes.h`).
Due to macro templates implementation there is a possibility of using this library with platform- or compiler-dependent integers
(for example, with `__int128_t`, which is not supported by default).
The format of numbers (number of bits in fractional part) is specified in runtime by the user.

## Documentation
In development.

## Getting started
### Building
CMake of version not less then 3.7.2 is required in order to build the tests.
This list of console comands may be used to build the project from the directory that is two levels below the CMakeLists.txt file:
```
cmake -DCMAKE_BUILD_TYPE=Release ../..
make
```

## Planned features
### Documentation
- [ ] Documentation file.
- [ ] Wiki.

### Library features
- [x] Basic arithmetic operations (addition, subtracton, multiplication, division).
- [ ] Exponentiation and root.
- [ ] Logarithm and exponent.
- [ ] Trigonometric functions.
- [ ] Matrix operations.
