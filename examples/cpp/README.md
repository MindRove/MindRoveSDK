# C++ Examples

This directory contains C++ examples for the Mindrove SDK. These examples demonstrate how to interact with the SDK using C++ and serve as a starting point for your own projects.

## Download the Latest Release

Before building the examples, download the latest release of the MindRove SDK from the following link:

[MindRove SDK Latest Release](https://github.com/MindRove/MindRoveSDK/releases/latest)

Unzip the downloaded release into the `examples/cpp` folder. This ensures that the SDK release directory is in the expected location.

## Building the Examples

To build the examples, follow these steps:

1. **Create a Build Directory**

    Open your terminal, navigate to the examples/cpp/ directory, and create a separate build directory:

    ```bash
    mkdir build && cd build

1. **Generate Build Files with CMake**

    Run CMake to configure the project. When running CMake, pass the SDK release directory using the `-D` flag. Replace `../path-to-the-release-folder-unzipped` with the relative path to your unzipped SDK release folder:

    ```bash
    cmake .. -DSDK_RELEASE_DIR="../path-to-the-release-folder-unzipped"
1. **Build the Project**

    Build the project in Release mode using the following command:

    ```bash
    cmake --build . --config Release

1. **Install the Binaries**

    Finally, install the generated binaries:

    ```bash
    cmake --install .

1. **Running the Examples**

    After building and installing, you can test the generated binaries. For instance, to run the get_data example on Windows:

    ```bash
    bin\get_data\get_data.exe --board-id -1

    ```
    This command runs the get_data executable with the --board-id -1 parameter, which is used to initiate a synthetic board that simulates incoming data.

## Additional Information

- Dependencies: Make sure CMake is installed on your system. You may also need a compatible compiler and any other dependencies required by the Mindrove SDK.
- Further Documentation: For more details on the SDK and advanced usage, please refer to the official Mindrove SDK documentation.
