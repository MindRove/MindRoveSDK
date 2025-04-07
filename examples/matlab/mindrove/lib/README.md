# MindRove SDK Library Files

This folder should contain the platform-specific libraries from the MindRove SDK.

## Setup Instructions

1. Download the appropriate SDK release for your OS from the [MindRoveSDK GitHub Releases](https://github.com/MindRove/MindRoveSDK/releases).
2. Extract the `lib/` folder from the archive.
3. Copy all library files into this `lib/` directory:

### File Types:
- **Windows**: `*.dll`, `*.lib`
- **macOS**: `*.dylib`, `*.a`
- **Linux**: `*.so`, `*.a`

These files are required for linking the MATLAB with the MindRove SDK.