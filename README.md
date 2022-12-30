# Widen
A distributed system for deep learning model inference

> For detail information of this project, refer to [here](docs/)


## Usage
### What you'll need
> If you don't want to mess up with your own computer environment, consider using the provided dockerfile
- ubuntu >= 20.04
- cmake >= 3.17.0
- suitable compiler for your platform that supports C++17
- protobuf

### Steps 
- Clone the project
    ```bash
    git clone --recursive https://github.com/KMint1819/Widen.git
    ```

- Build the project
    ```cmake
    cd Widen && mkdir build

    ### IF YOU WANT TO USE DOCKER, RUN THE CONTAINER HERE
    ./scripts/env
    ###    

    cd build
    cmake ..
    cmake --build . -j <number of threads to speed up compilation>
    ```
    - Output path of executables will be in build/bin
 
- Run unit test using the following command:
    ```cmake
    cd build
    bin/mytests
    ```

## TODOs
- clang-tidy
- distributed unit tests
- precompiled headers

## Improvements
