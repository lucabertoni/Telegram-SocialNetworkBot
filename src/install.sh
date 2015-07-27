clear

echo "Sto compilando il main..."
g++ main.cpp class/*.cpp -o main.o -std=c++0x -lcurl -lmysqlcppconn
echo "Compilato!"

echo "Sto compilando il demone..."
g++ daemon.cpp class/*.cpp -o daemon.o -std=c++0x -lcurl -lmysqlcppconn
echo "Compilato!"