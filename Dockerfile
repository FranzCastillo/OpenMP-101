FROM ubuntu:latest

# Install dependencies
RUN apt-get update && \
    apt-get install -y gcc libomp-dev

# Set the working directory
WORKDIR /src

# Copy the source code
COPY ./src .