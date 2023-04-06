## ScreenHelper
### Library for OSX screen functions

ScreenHelper is a C++ library that allows you to easily manage your screen and windows, including capturing screenshots, obtaining screen resolutions, and getting the current active window name.

Most functions are using `CoreGraphics` or `CoreFoundation` framework

Note that some functions require `OpenCV`

### Features

- Get screen resolution
- Capture full screenshots
- Capture partial screenshots
- Save captured images to files
- Get the current active window name
- Get similarity value between two images
- Get coordinates of similar image on screen (with similarity percentage)

### Classes and structs
#### Structs
```c++
// Holds screen width and height.
struct ScreenWidthHeight

// Holds screenshot data including width, height, and image ref.
struct Screenshot

// Holds parameters for capturing a partial screenshot.
struct PartScreenshotParams
        
// Holds coordinates (top-left) for found object and similarity value
struct FoundPoint
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

// Returns similarity between two images (for CoreGraphics image object)
double Similarity(CGImageRef image1, CGImageRef image2);

// Returns similarity between two images (for OpenCV image object)
double Similarity(Mat image1, Mat image2);

// Returns coordinates for similar to given object 
FoundPoint* FindImageInScreen(CGImageRef pattern);

// Returns coordinates for similar to given object 
FoundPoint* FindImageInScreen(const cv::Mat &pattern);
```

#### Remember to `delete` unused pointers 

### Additional

The library provides extern "C" functions, allowing you to use this library in C# applications through P/Invoke.

All extern "C" functions are stored in separate `ScreenHelperExternal.h` header

It also have `Release*` functions for every struct

For more info on using in C# - see my [CSharp project](https://github.com/pents/ScreenHelper.Sharp)

### Building

Repository contains CMakeLists files - build using CMake minimum version 3.23



```
cmake --buid /path/to/root/CMakeLists.txt/Folder --target all
```




### License

This project is licensed under the MIT License.