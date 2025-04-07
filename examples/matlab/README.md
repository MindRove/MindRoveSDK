# MindRove MATLAB SDK Setup

To properly use the MindRove SDK with MATLAB, you must configure your environment by including the appropriate SDK files based on your operating system.

## Setup Instructions

1. **Download the MindRove SDK**  
    Visit the [MindRoveSDK GitHub](https://github.com/MindRove/MindRoveSDK/releases/) and download the [latest release](https://github.com/MindRove/MindRoveSDK/releases/latest) that matches your operating system (e.g. `mindrovesdk-5.1.4-win-x64.zip` for 64-bit Windows).

2. **Extract Files**  
    Unzip the downloaded archive and extract its contents and copy the folders into the `matlab/mindrove` directory of this project.

    The archive contains two folders:

    - `inc/` — contains all necessary header files

    - `lib/` — contains the compiled dynamic/shared libraries and static libraries for your platform


3. **Ensure the Folder Structure Matches**  
    After setup, your folder structure should look like this:

    ```
    matlab/
    └── mindrove/
        ├── inc/
        │   └── [SDK header files (*.h)]
        ├── lib/
        │   └── [SDK library files for your OS]
        └── *.m
            └── [MATLAB specification files]
    ```
    Note: The `.m` files are not included in the SDK archive, but come from the MATLAB example folder provided separately.


## File Types by OS

Ensure that the `lib/` folder contains the appropriate files for your operating system. These include a combination of dynamic/shared and static libraries such as:

- **Windows**: `*.dll`, `*.lib`

- **macOS**: `*.dylib`, `*.a`

- **Linux**: `*.so`, `*.a`

## Notes

Make sure that the SDK architecture (x64, x86, etc.) matches your MATLAB installation.
