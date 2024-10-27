# CMakeList.txt: projeto de CMake para tcp-server-client, incluir origem e definir
# lógica específica a um projeto aqui.
#

# Adicione a origem ao executável deste projeto.
add_executable (tcp-server-client "tcp-server-client.cpp" "tcp-server-client.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET tcp-server-client PROPERTY CXX_STANDARD 20)
endif()

# TODO: Adicione testes e instale destinos, se necessário.
