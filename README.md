University Management System in C++ using MySQL Database


To compile and run (replace with paths to your mysql files):

To compile
g++ main.cpp -o main -I/usr/local/mysql/include -L/usr/local/mysql/lib -lmysqlclient

To run
export DYLD_LIBRARY_PATH=/usr/local/mysql/lib:$DYLD_LIBRARY_PATH

./main

Tables in MYSQL are fold in the database folder