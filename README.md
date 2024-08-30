University Management System to include student and room registration, library, and password system in C++ using MySQL Database


To compile and run (replace with paths to your mysql files):

To compile and run main
g++ main.cpp -o main -I/usr/local/mysql/include -L/usr/local/mysql/lib -lmysqlclient
export DYLD_LIBRARY_PATH=/usr/local/mysql/lib:$DYLD_LIBRARY_PATH
./main


To compile and run library
g++ library.cpp -o library -I/usr/local/mysql/include -L/usr/local/mysql/lib -lmysqlclient
export DYLD_LIBRARY_PATH=/usr/local/mysql/lib:$DYLD_LIBRARY_PATH
./library

Tables in MYSQL are found in the database folder

