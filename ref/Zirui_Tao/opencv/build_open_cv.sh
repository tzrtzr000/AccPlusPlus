cd ../opencv
mkdir build && cd build
cmake -D BUILD_TIFF=ON -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..
make -j7