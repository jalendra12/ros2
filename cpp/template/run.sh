find . -name "*.s" -exec rm -f {} \;
find . -name "*.exe" -exec rm -f {} \;
g++ -S metaProgrammingLib.cpp -o Assembly.s
g++ metaProgrammingLib.cpp -o executable.exe
./executable.exe