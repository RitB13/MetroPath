# Kolkata Metro Route Finder - Requirements

## System Requirements

### Minimum Requirements
- **Operating System**: Windows 7+, macOS 10.12+, or Linux (Ubuntu 16.04+, Fedora 25+, etc.)
- **RAM**: 512 MB minimum, 1 GB recommended
- **Storage**: 50 MB free space for source code and compilation
- **Display**: Terminal/Console support

### Compiler Requirements
One of the following C++ compilers:
- **GCC/G++**: Version 4.8.1 or later (C++11 support)
- **Clang**: Version 3.3 or later
- **MSVC**: Visual Studio 2013 or later
- **MinGW**: Version supporting C++11 or later (Windows)

## Software Dependencies

### Required
- **C++ Standard Library (STL)** - Included with compiler
  - `<iostream>` - Input/output operations
  - `<vector>` - Dynamic arrays
  - `<unordered_map>` - Hash tables
  - `<list>` - Doubly linked lists
  - `<queue>` - Queue and priority queue
  - `<algorithm>` - Standard algorithms
  - `<climits>` - Numeric limits
  - `<cmath>` - Mathematical functions
  - `<sstream>` - String stream operations
  - `<cctype>` - Character handling
  - `<string>` - String class
  - `<functional>` - Function objects

### Optional
- **CMake**: Version 3.10+ (for build automation)
- **Make**: For Makefile-based builds
- **GDB/LLDB**: For debugging
- **Valgrind**: For memory leak detection (Linux/macOS)

## Build Tools

### Linux
```bash
# Debian/Ubuntu
sudo apt-get update
sudo apt-get install build-essential g++ cmake

# Fedora/RHEL
sudo dnf install gcc-c++ make cmake

# Arch Linux
sudo pacman -S gcc make cmake
```

### macOS
```bash
# Using Homebrew
brew install gcc cmake

# Or install Xcode Command Line Tools
xcode-select --install
```

### Windows
- **MinGW-w64**: Download from https://www.mingw-w64.org/
- **Visual Studio**: Download Community Edition from https://visualstudio.microsoft.com/
- **Cygwin**: Alternative Unix-like environment for Windows

## C++ Standard
- **C++11** or later required
- Features used:
  - `auto` keyword
  - Range-based for loops
  - Lambda expressions
  - `nullptr`
  - `unordered_map` and `unordered_set`
  - Move semantics
  - Template improvements

## Development Environment (Optional)

### IDEs
- **Visual Studio Code** + C++ Extension
- **CLion** by JetBrains
- **Visual Studio** (Windows)
- **Code::Blocks**
- **Eclipse CDT**
- **Qt Creator**

### Text Editors
- **Vim** with C++ plugins
- **Emacs** with C++ mode
- **Sublime Text** with C++ build system
- **Atom** with C++ packages

## Testing Requirements

### Unit Testing (Optional)
If you want to add unit tests:
- **Google Test (gtest)**: C++ testing framework
- **Catch2**: Modern C++ test framework
- **Boost.Test**: Part of Boost libraries

### Static Analysis (Optional)
- **cppcheck**: Static code analyzer
- **clang-tidy**: Clang-based linter
- **Coverity**: Commercial static analyzer

## Runtime Dependencies
**None** - The compiled executable is standalone and requires no external runtime libraries beyond the system's C++ runtime, which is typically pre-installed.

## Version Control
- **Git**: Version 2.0+ (optional, for source control)

## Documentation Tools (Optional)
- **Doxygen**: For generating code documentation
- **Markdown viewer**: For viewing README files

## Platform-Specific Notes

### Windows
- Ensure compiler is added to PATH environment variable
- Use PowerShell or Command Prompt for compilation
- Windows Defender may scan the executable after compilation

### Linux
- Most distributions come with g++ pre-installed or easily available
- Ensure you have write permissions in the compilation directory
- May need to install `build-essential` package

### macOS
- Xcode Command Line Tools provide clang compiler
- Homebrew is recommended for additional tools
- May need to accept Xcode license agreement

## No External Package Manager Required

Unlike Python or Node.js projects, this C++ project does not require:
- ❌ pip, npm, or similar package managers
- ❌ Virtual environments
- ❌ External library downloads
- ❌ Network connection for dependencies

All required libraries are part of the C++ Standard Library, which comes with your compiler.

## Compilation Verification

To verify your system meets the requirements:

```bash
# Check C++ compiler version
g++ --version        # For GCC
clang++ --version    # For Clang
cl                   # For MSVC (shows version in output)

# Check C++11 support
g++ -std=c++11 --version

# Verify make (optional)
make --version

# Verify cmake (optional)
cmake --version
```

## Quick Start Checklist

- [ ] C++ compiler installed (g++, clang++, or MSVC)
- [ ] Compiler supports C++11 or later
- [ ] Source files downloaded (Graph_M.cpp, Heap.h)
- [ ] Terminal/console access available
- [ ] Sufficient permissions to compile and execute programs

## Troubleshooting

### Common Issues

**Issue**: "command not found: g++"
- **Solution**: Install GCC/G++ compiler for your platform

**Issue**: Compilation errors about C++11 features
- **Solution**: Add `-std=c++11` flag when compiling

**Issue**: "unordered_map: No such file or directory"
- **Solution**: Ensure you're using C++11 or later standard

**Issue**: Linking errors on Windows
- **Solution**: Ensure you're using appropriate compiler flags for your platform

## Support

For compiler installation help, refer to:
- **GCC**: https://gcc.gnu.org/install/
- **Clang**: https://clang.llvm.org/get_started.html
- **MSVC**: https://docs.microsoft.com/en-us/cpp/

---

## Summary

**This project has ZERO external dependencies!**

You only need:
1. A C++11 (or later) compatible compiler
2. The C++ Standard Library (comes with compiler)
3. A text editor and terminal

That's it! No pip installs, no npm packages, no complex setup.
