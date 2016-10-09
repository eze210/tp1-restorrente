# tp1-restorrente
 
###Travis:
[![Build Status](https://travis-ci.org/eze210/tp1-restorrente.svg?branch=master)](https://travis-ci.org/eze210/tp1-restorrente) 

###To build the project using CMake:
    Run the file: `build.sh`

    The file contains the following lines:
	```bash 
		$ mkdir build
		$ cd build
		$ cmake ../src
		$ make
	```

###To run the executable after the build
    Run the file: `run.sh`

    The file contains the following lines:
    ```bash
        $ mkdir build/data
        $ cp src/data/conf build/data/
        $ cd build/
        $ ./restorrente
    ```
