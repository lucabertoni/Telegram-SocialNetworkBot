clear

echo "Sto compilando..."

g++ main.cpp class/*.cpp -o main.o -std=c++0x -lcurl -lmysqlcppconn

echo "Compilato!"