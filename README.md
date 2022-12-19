# Widen
A distributed system for deep learning model inference

> For detail information of this project, refer to [here](docs/)

## Usage
- Clone the project
    ```bash
    git clone --recursive https://github.com/KMint1819/Widen.git
    ```

- Build the project
    ```cmake
    cd Widen && mkdir build
    cd build
    cmake ..
    cmake --build . -j <number of threads to speed up compilation>
    ```
    - Output path of executables will be in build/bin
 
- Run unit test using the following command:
    ```cmake
    ctest -VV --test-dir test/
    ```

## Dependencies
- protobuf
- asio

## TODOs
- docker
- clang-tidy
- distributed unit tests
- precompiled headers

## Improvements