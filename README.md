## ScreenHelper
### Library for OSX screen functions

ScreenHelper is a C++ library that allows you to easily manage your screen and windows, including capturing screenshots, obtaining screen resolutions, and getting the current active window name.

### Features

- Get screen resolution
- Capture full screenshots
- Capture partial screenshots
- Save captured images to files
- Get the current active window name

### Classes and structs
#### Structs
```c++
// Holds screen width and height.
struct ScreenWidthHeight

// Holds screenshot data including width, height, and image ref.
struct Screenshot

// Holds parameters for capturing a partial screenshot.
struct PartScreenshotParams
```

#### Functions

```c++
// Returns the screen resolution.
ScreenWidthHeight* GetScreenResolution()

// Captures a full screenshot and returns a Screenshot object.
Screenshot* GetScreenshot()

// Captures a partial screenshot based on the PartScreenshotParams object and returns a Screenshot object.
Screenshot* GetPartScreenshot(PartScreenshotParams* params)

// Saves the given image to a file specified by filePath. Returns true if successful, false otherwise.
bool SaveToFile(CGImageRef image, const std::string& filePath)

// Returns the name of the current active window as a string.
string* GetCurrentActiveWindowName()
```

#### Remember to `delete` unused pointers 

### Additional

The library provides extern "C" functions, allowing you to use this library in C# applications through P/Invoke.

All extern "C" functions are stored in separate `ScreenHelperExternal.h` header

For more info on using in C# - see my [CSharp project](https://github.com/pents/ScreenHelper.Sharp)

### Building

Repository contains CMakeLists files - build using CMake minimum version 3.23



```
cmake --buid /path/to/root/CMakeLists.txt/Folder --target all
```




### License

This project is licensed under the MIT License.