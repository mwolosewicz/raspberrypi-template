#!/bin/bash

# Definition of the image and container names
IMAGE_NAME="rpi_buildsystem"
CONTAINER_NAME="rpi_buildcontainer"

# Step 1: Check if the image has already been built, if not - build the image
if ! podman image exists $IMAGE_NAME; then
    echo "Building the image $IMAGE_NAME..."
    podman build -t $IMAGE_NAME .
fi

# Step 2: Check if the container has already been created, if not - create the container
if ! podman container exists $CONTAINER_NAME; then
    echo "Creating the container $CONTAINER_NAME..."
    podman run -dt --name $CONTAINER_NAME -v ${PWD}:/src:Z $IMAGE_NAME
else
    echo "Container $CONTAINER_NAME already exists."
fi

# Step 3: Run the build.sh script inside the container
echo "Running the build.sh script in the container $CONTAINER_NAME..."
podman exec -it $CONTAINER_NAME /bin/bash -c "cd src && ./build.sh"
