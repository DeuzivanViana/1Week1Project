# CPP-Template
This template implement by default the GTest

## Commands
- Base command for all
> `cmake . -B build -DBUILD_TESTS=ON -DSANITIZE=ON && cmake --build build`

Set flags to `OFF` or `ON` as you want.

## Flags info
- `BUILD_TESTS` generate all test in test/unit to build/src/test.elf, execute it and all will be tested.
- `SANITIZE` enable all sanitize flags to check if your code has a leak of memory and etc.
- `CMAKE_BUILD_TYPE=Release` optimize your code to release, removing `debugsinfo`

## Where binarys expect to stay
- `test.elf`in `build/test/test.elf`
- `app.elf`in `build/src/app.elf`

## Libs required
- `libgtest-dev` on debian install with `sudo apt install libgtest-dev`