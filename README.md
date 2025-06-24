# LogViewerTwo

A modern, Qt-based C++ desktop application for smart log file viewing and filtering. Designed for real-world use cases like embedded diagnostics and system monitoring.

![Qt](https://img.shields.io/badge/Qt-5%2F6-green.svg)
![C++](https://img.shields.io/badge/C%2B%2B-11-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)

## Features

### 🔍 **Smart File Management**
- Automatic loading of log files from configurable directories
- Support for CSV and INI file formats
- Real-time file list updates
- Intuitive file navigation

### 📊 **Advanced Filtering**
- **Log Files**: Filter and view `.csv` files
- **Milling Files**: Filter and view `.ini` files  
- **All Files**: View all supported file types
- Mutually exclusive filter options with smart state management

### 📅 **Date-based Search**
- Flexible date range picker with calendar popup
- Multi-format date recognition:
  - `yyMMdd` (e.g., 231225)
  - `yyyy-MM-dd` (e.g., 2023-12-25)
  - `yy/MM/dd` (e.g., 23/12/25)
  - `yyyy/MM/dd` (e.g., 2023/12/25)
- Intelligent filename date matching

### 🎨 **Modern UI Design**
- Professional dark blue theme
- Custom styled components
- Responsive layout design
- High-quality custom icons
- Smooth scrolling and hover effects

## Screenshots

![LogViewerTwo Interface](screenshot.png)
*Main interface showing file filtering and content viewing*

## Installation

### Prerequisites
- Qt 5.12+ or Qt 6.x
- C++11 compatible compiler
- CMake 3.16+ (optional)

### Building from Source

1. **Clone the repository:**
   ```bash
   git clone https://github.com/i-c4r4c4l/LogViewerTwo.git
   cd LogViewerTwo
   ```

2. **Build with Qt Creator:**
   - Open `LogViewerTwo.pro` in Qt Creator
   - Configure your kit (Desktop Qt version)
   - Build and run

3. **Build with qmake (command line):**
   ```bash
   qmake LogViewerTwo.pro
   make
   ```

## Configuration

### Settings File
The application uses `settings.ini` to configure the log directory:

```ini
LOGS_PATH = C:/path/to/your/logs
```

**Supported File Types:**
- `.csv` - Log files
- `.ini` - Configuration/Milling files

## Usage

1. **Launch Application**: Start LogViewerTwo
2. **Auto-Load**: Files are automatically loaded from the configured directory
3. **Filter Files**: Use checkboxes to filter by file type:
   - ☑️ **Log** - Show only CSV files
   - ☑️ **Milling** - Show only INI files  
   - ☑️ **All** - Show all supported files
4. **Date Search**: Select date range and click Search to filter by filename dates
5. **View Content**: Click any file in the list to view its contents

## Project Structure

```
LogViewerTwo/
├── icons/              # Application icons
│   ├── exit.png
│   └── log.png
├── main.cpp            # Application entry point
├── logviewertwo.h      # Main window header
├── logviewertwo.cpp    # Main window implementation
├── logviewertwo.ui     # Qt Designer UI file
├── LogViewerTwo.pro    # Qt project file
├── settings.ini        # Configuration file
└── README.md          # This file
```

## Technical Details

- **Framework**: Qt Widgets
- **Language**: C++11
- **UI Design**: Qt Designer + Programmatic styling
- **Configuration**: INI file based settings
- **File Handling**: Qt File I/O with text stream support
- **Date Processing**: QDate with multiple format parsing

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Qt Framework for the excellent GUI toolkit
- Modern UI design inspired by contemporary desktop applications
- Icon resources for professional appearance

## Support

If you encounter any issues or have feature requests, please [open an issue](https://github.com/yourusername/LogViewerTwo/issues) on GitHub.

---

**Author**: Ravshan M.  
**Version**: 1.0.0  
**Last Updated**: June 2025 