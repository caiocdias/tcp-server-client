cmake_minimum_required(VERSION 3.10)

# Nome do projeto
project(TCPProject)

# Definir o padrão C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Incluir diretórios de cabeçalhos
include_directories(${PROJECT_SOURCE_DIR}/src)

# Identificar o sistema operacional e definir as variáveis específicas
if (WIN32)
    add_definitions(-DPLATFORM_WINDOWS)
    set(SOURCES
        src/main.cpp
        src/tcp_client.cpp
        src/tcp_server.cpp
        src/platform/windows/socket_util.cpp
    )
elseif (UNIX)
    add_definitions(-DPLATFORM_LINUX)
    set(SOURCES
        src/main.cpp
        src/tcp_client.cpp
        src/tcp_server.cpp
        src/platform/linux/socket_util.cpp
    )
endif()

# Adicionar o executável principal
add_executable(tcp_project ${SOURCES})
