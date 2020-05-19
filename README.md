# unwrapper
![Build](https://github.com/oakdoor/unwrapper/workflows/build%20unwrapper/badge.svg)

![Build and create release](https://github.com/oakdoor/unwrapper/workflows/build%20and%20create%20release/badge.svg)

## Purpose
To retrieve data which has been wrapped after passing through an Oakdoor Data Diode™.

This repository contains source code and build scripts for the Unwrapper program. 
The unwrapper uses the CLOAK DAGGER™ header to unwrap data which has been wrapped by an Oakdoor Data Diode™.

## Dependencies
* Centos 7
* cmake
* devtoolset-9
* boost-devel

See the DockerFile in .github/actions/build/ for more details

## How to Use
* Pull/Download the repository
* Build the unwrapper using cmake
* Run the unwrapper on wrapped data

### Pull/Download the repository
    git clone git@github.com:oakdoor/unwrapper.git

### Building the Unwrapper
Run the following command from the root directory to build the unwrapper: 

    ./build_unwrapper.sh
This creates a "unwrapper_linux_x86" binary in the root directory.

Alternatively you can download the latest binary from the "release" tab. 
Remember to change the file permissions to allow execution, e.g.:

    chmod 700 unwrapper_linux_x86

### Running the Unwrapper
The Oakdoor Data Diode™ wraps data to **prevent the potential execution of malicious code**.

**Before unwrapping**, ensure you are confident that the original data contained no malicious code or 
that you are unwrapping in a controlled environment.  

The "unwrap" binary takes an input file and outputs unwrapped data to an output file:

    ./unwrapper_linux_x86 [file_in_name] [file_out_name] 
For instance once you have built the unwrapper, run:

    ./unwrapper_linux_x86 this_is_an_example_wrapped_file.txt my_unwrapped_file.txt
This should output a file named "my_unwrapped_file.txt" which should be identical to "example_unwrapped_file.txt"

