# C++ Web Server (No Frameworks)

A minimal yet functional HTTP web server written in C++ from scratch — **without using any frameworks** or external libraries. Built for learning, performance, and complete control.

---

## About This Project

This project is a barebones but powerful HTTP server built with raw **Winsock2** and standard C++20. It demonstrates how to create a fully working web server with:

- File serving (HTML, CSS, JS, images)
- Route handling (e.g. `/api/hello`, `/about`)
- Custom logging system
- No frameworks, no Boost, no external dependencies

Ideal for learning:

- Socket programming
- HTTP basics
- Multi-file C++ design
- Manual routing and request handling
- Building dev tools like logging

---

## Features

✅ Serve static files from a `/public` directory  
✅ Basic routing system using `std::unordered_map`  
✅ Custom `Logger` class with timestamps and log levels  
✅ MIME type detection for HTML, CSS, JS, PNG, JPEG  
✅ Custom 404 page fallback  
✅ Portable C++20 codebase (MSVC compatible)  
✅ Thread-safe logging  
✅ Designed for future extensibility: POST, threads, templates, etc.

---

## 📂 Folder Structure

cpp-webserver/
├── public/ # Static HTML/CSS/JS files
│ ├── index.html
│ └── styles.css
├── include/
│ ├── server.hpp
│ ├── router.hpp
│ └── logger.hpp
├── src/
│ ├── main.cpp
│ ├── server.cpp
│ ├── router.cpp
│ └── logger.cpp
├── CMakeLists.txt
└── README.md

---

## Getting Started

### Prerequisites

- Windows
- CMake ≥ 3.15
- Visual Studio (2022+) with C++ tools installed

---

### Build Instructions

```bash
git clone https://github.com/yourusername/cpp-webserver.git
cd cpp-webserver
mkdir build
cd build
cmake ..
cmake --build .
```

This will produce an executable in ./build/Debug/cpp_webserver.exe

---

### Run the Server

```bash
./build/Debug/cpp_webserver.exe
```

Then open

```arduino
http://127.0.0.1:8080
```

### Default Routes

Route Description

- / Serves public/index.html
- /styles.css Serves public/styles.css
- /about Returns a custom HTML route
- /api/hello Returns a JSON API response
- Unknown route Returns 404 Not Found

---

## How it Works

- The server uses Winsock2 to open a TCP socket and listen on port 8080
- incoming requests are parsed manually (GET only)
- The server supports static file serving from `./public`
- A router maps specific paths (like `/about`) to custom handler functions
- All activity is logged using a custom thread-safe `Logger`

## Design Principles

- **Zero Dependency**: build only with the C++ standard librabrary + Windows sockets
- **Learn-by=doing**: everything from HTTP parsing to routing is handwritten
- **Extensible**: easy to add POST,TLS, multithreading, templates
- **Readable and testable**: clean file structure and separation of concerns

## Logging System

Example output:

```css
[2025-07-20 15:14:05] [INFO] Starting the server...
[2025-07-20 15:14:05] [INFO] Listening on port 8080
[2025-07-20 15:14:20] [INFO] GET /index.html
[2025-07-20 15:14:22] [WARN] File not found: /favicon.ico
```

You can redirect logs to a file by modifying `Logger::init("server.log");`

## License

This project is licensed under the MIT License

## Acknowledgments

This project was built for educational purposes and personal growth in systems programming. Inspired by real-world web servers, but built from scratch in modern C++.
