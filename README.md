Descrizione di cosa fa il modulo...

Autore: deniscristian.pal@studenti.units.it

cmake -S . -B build/ -D CMAKE_BUILD_TYPE=Release
cmake --build build -j16
GTEST_COLOR=1 ctest --test-dir build --output-on-failure -j16
