# MindRove Unity Integration

This folder contains an example Unity project for integrating the MindRove SDK with Unity.


## Recommended Setup (via NuGet)
Use NuGet for Unity to automatically manage and update the SDK dependencies.
1. **Install NuGet for Unity**  
   If not already included, install the NuGet package manager for Unity: 
   [NuGetForUnity](https://github.com/GlitchEnzo/NuGetForUnity)


2. **Add the MindRove Package**  
   - Open Unity
   - Go to `NuGet -> Manage NuGet Packages`
   - Search for `MindRove`
   - Install the [latest available version](https://www.nuget.org/packages/mindrove)

3. **Restart Unity**  
   After installing the package, **restart the Unity Editor** to ensure the new DLLs are correctly loaded and referenced.

4. **Attach the Script to a GameObject**  
   Add a GameObject to your Scene (e.g., an empty GameObject) and attach the MindRove-related script (such as `NewBehaviourScript.cs`) to it. Unity will not execute scripts unless they are attached to active objects.

5. **Build and Run the Executable**  
   Due to networking and firewall constraints, **data streaming may not work in Play Mode inside the Unity Editor**.  
   Instead, build your project and run the resulting `.exe` file. This ensures the board connection and data transmission function as expected.
   
   If the board still doesn't stream data, ensure the .exe is allowed through your system's firewall.


## Alternative Manual Setup

> Use this method only if NuGet is not available.

1. Download the latest [MindRove SDK](https://github.com/MindRove/MindRoveSDK/releases/tag/5.1.4)
2. Copy the required `.dll` and `.lib` files (matching your system architecture, e.g., x64) from the `lib/` folder into `Assets/`.
3. Make sure any existing Unity script files in the  `Assets/` folder remain untouched.
4. Build and test as mentioned above.

## Notes

- Prefer the NuGet method for easier maintenance and versioning.
- If you update DLLs manually, always test the build after replacing them.
