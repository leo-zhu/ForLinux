README

Applicant:  Leo Zhu
Date:       06/25/2019

(1) Source code 
    src/main.cpp
    lib/include/matrix.hh
    lib/src/matrix.cpp

(2) Static library after build
    lib/static/libmatrix.a

(3) Shared library after build
    lib/shared/libmatrix.so

(4) Program build
    $ ./make_lib              // to build library files
    $ ./make_main             // to build main executable files

(5) Program run
    $ bin/main_static         // run the test main program, with static library "matrix" built-in

    $ source setLibPath.sh    // set shared library path
    $ bin/main_dynamic        // run the test main program, with dynamically-linked shared library "matrix"

(6) All files and path structure after build

|-- bin
|   |-- main_dynamic
|   |-- main.o
|   `-- main_static
|-- lib
|   |-- include
|   |   `-- matrix.hh
|   |-- shared
|   |   |-- libmatrix.so
|   |   `-- matrix.o
|   |-- src
|   |   `-- matrix.cpp
|   `-- static
|       |-- libmatrix.a
|       `-- matrix.o
|-- make_lib
|-- make_main
|-- readme.txt
|-- setLibPath.sh
`-- src
    `-- main.cpp

(7) Test program build system information
CentOS Linux release 7.5.1804 (Core)


(end)
