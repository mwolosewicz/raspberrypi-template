# RaspberryPi cross compilation template

This project serves as a versatile template for building applications on RaspberryPi and other ARMv8-compatible processors. It's designed to be flexible and easily adaptable to other platforms, making it an ideal starting point for developing robust applications across different environments.

**Static Linking of Libraries:** All libraries used in this project are statically linked. This means there is no need to install any libraries on the target system, effectively avoiding issues related to missing dynamic libraries or discrepancies in their versions. This approach ensures that the application runs smoothly across different environments without additional configuration.


## Simple build:
```
./build_podman.sh
```

Then use `scp` to copy binary `build/gpio_scanner` into the target device. 

## Key Features
* Cross-Platform Compatibility: Initially configured for RaspberryPi, this template can be easily extended to support additional platforms.
* Dependency Management: Uses Conan for efficient management of dependencies.
* Build System: Utilizes CMake, ensuring a streamlined build process.
* Cross-Compilation: Supports cross-compiling, allowing for development on various systems.
* Containerization: Leverages Podman to create a clean build environment within a container, preventing pollution of the local setup.
* Multi-OS Support: Thanks to Podman, the template can be used to build projects on non-Linux platforms such as MacOS and Windows.
* Direct Compilation on Linux: For Linux users, a build.sh script is provided for direct compilation.
* GPIO Operations: Integrates libgpiod for managing GPIO operations from userspace.
* Logging: Incorporates spdlog to enable efficient logging of application behavior.

## Prerequisites
* Podman Installation: Ensure that Podman is installed on your system. This is essential for creating the build environment.

## Setup for Native Compilation
For native compilation, particularly on Linux, you must install the packages defined in the Dockerfile. This ensures that all necessary dependencies are correctly set up in your local environment.

## Getting Started
To begin using this template, clone the repository to your local machine. If you are compiling on Linux and prefer a straightforward setup, you can use the provided build.sh script. For cross-platform development or if you prefer containerized environments, follow the steps to set up your Podman container as outlined in the documentation.

Feel free to customize this description further based on any additional details or specific requirements you might have for your project. This draft aims to provide a clear and concise introduction to your project, making it easy for users to understand its purpose and get started quickly. Good luck with your GitHub project!

## If you like it - you can buy me a coffee:
[!["Buy Me A Coffee"](https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png)](https://www.buymeacoffee.com/wolosewicz)