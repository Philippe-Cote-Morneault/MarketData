<p align="center">
  <h3 align="center">MarketData</h3>
  <p align="center">
    A Market Data C++ API
  </p>
</p>

MarketData is a C++ API to fetch market data. This API allows you to download historic market data and some general information about companies that are on public finance websites and APIs. 

This library is currently under development and this README will be updated when new features are added. 

* [Getting Started](#getting-started)
  * [Requirements](#requirements)
  * [Installation](#installation)
* [License](#license)


<!-- GETTING STARTED -->
## Getting Started

Before attempting the build the library, make sure you meet all requirements.

### Requirements
* [cURL](https://github.com/curl/curl)
* [nlohmann/json](https://github.com/nlohmann/json)
* [CMake](https://cmake.org/download/)

### Installation

1. Clone the repo
```sh
git clone https://github.com/JigsawCorp/MarketData
```
2. Create build directory
```sh
cd MarketData
mkdir build
cd build
```
3. Run CMake with desired options.

The following command will create a static version of MarketData as well as tests.
```sh
cmake -DBUILD_STATIC=ON -DDBUILD_TESTS=ON ..
```

Available options are the following:

* DBUILD_TESTS: Generates an executable that will run tests on the project.
* DBUILD_STATIC: Generates a static library version of MarketData.
* DBUILD_SHARED: Generates a shared library version of MarketData.
* DBUILD_HEADER: Generates a header-only library version of MarketData.
* DBUILD_SRC: Generates an uncompiled target allowing you to compile the library with your project.

You can use as many options as you want and generate all 4 library types if desired.

4. (Optional) Install the library on your system
```sh
make install
```

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.


