cmake_minimum_required(VERSION 3.17)
project(Random_hashes)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenSSL REQUIRED)
    # This is a bug in CMake that causes it to prefer the system version over
    # the one in the specified ROOT folder.
    # set(OPENSSL_ROOT_DIR ${OPENSSL_ROOT_DIR} /usr/local/Cellar/openssl@1.1/1.1.1h/)
    #set(OPENSSL_CRYPTO_LIBRARY ${OPENSSL_ROOT_DIR}/lib/libcrypto.dylib CACHE FILEPATH "" FORCE)
    #set(OPENSSL_SSL_LIBRARY ${OPENSSL_ROOT_DIR}/lib/libssl.dylib CACHE FILEPATH "" FORCE)

add_executable(Random_hashes main.cpp)

target_link_libraries(Random_hashes OpenSSL::SSL)
