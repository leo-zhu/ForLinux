README

Applicant:  Leo Zhu
Date:       06/25/2019

(1) Test source code 
    src/main.cpp

(2) Matrix library source code
    lib/include/matrix.hh
    lib/src/matrix.cpp

(3) Static library after build
    lib/static/libmatrix.a

(4) Shared library after build
    lib/shared/libmatrix.so

(5) Program build
    $ ./make_lib              // to build library files
    $ ./make_main             // to build main executable files

(6) Program run
    $ bin/main_static         // run the test main program, with static library "matrix" built-in

    $ source setLibPath.sh    // set shared library path
    $ bin/main_dynamic        // run the test main program, with dynamically-linked shared library "matrix"

(7) All files and path structure after build

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

(8) Test program build platform 
CentOS Linux release 7.5.1804 (Core)


(end)
