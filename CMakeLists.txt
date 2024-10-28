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
    file(GLOB SOURCES
        src/*.cpp
        src/platform/windows/*.cpp
    )
elseif (UNIX)
    add_definitions(-DPLATFORM_LINUX)
    file(GLOB SOURCES
        src/*.cpp
        src/platform/linux/*.cpp
    )
endif()

# Adicionar o executável principal
add_executable(tcp_project ${SOURCES})

# Linkar a biblioteca ws2_32 no Windows para suportar sockets
if (WIN32)
    target_link_libraries(tcp_project ws2_32)
endif()
