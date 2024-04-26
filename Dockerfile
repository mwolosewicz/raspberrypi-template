# Use an official Ubuntu base image
FROM ubuntu:22.04

# Set environment variables to non-interactive (this prevents some prompts)
ENV DEBIAN_FRONTEND=noninteractive

# Update and install dependencies
RUN apt update && apt install -y \
    build-essential \
    cmake \
    crossbuild-essential-armhf \
    python3 \
    python3-pip

# Install Python dependencies
RUN pip3 install conan

# Create conan profile
RUN conan profile detect --force