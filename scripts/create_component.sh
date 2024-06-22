#!/bin/bash

# Verifica se foi passado um argumento
if [ "$#" -ne 1 ]; then
    echo "Uso: $0 <nome_do_projeto>"
    exit 1
fi

# Define o nome do projeto
NOME=$1
NOME_MAIUSCULO=$(echo "$NOME" | tr '[:lower:]' '[:upper:]')

# Cria o diretório src/nome
mkdir -p src/$NOME

# Cria o arquivo .cpp com o conteúdo especificado
cat <<EOL > src/$NOME/$NOME.cpp
#include "$NOME.hpp"

$NOME::$NOME()
{

}
EOL

# Cria o arquivo .hpp com o conteúdo especificado
cat <<EOL > src/$NOME/$NOME.hpp
#ifndef ${NOME_MAIUSCULO}_HPP
#define ${NOME_MAIUSCULO}_HPP

#include "BaseComponent.hpp"

class $NOME : public BaseComponent
{
public:
    $NOME();
private:
};

#endif // ${NOME_MAIUSCULO}_HPP
EOL

# Cria o arquivo CMakeLists.txt com o conteúdo especificado
cat <<EOL > src/$NOME/CMakeLists.txt
set(FILES_BASE_PATH \${CMAKE_BINARY_DIR})

add_library($NOME STATIC $NOME.cpp)

target_include_directories($NOME
    INTERFACE
    \$<BUILD_INTERFACE:\${CMAKE_CURRENT_SOURCE_DIR}>
    \$<INSTALL_INTERFACE:include>
)

target_link_libraries($NOME PUBLIC AssetManager)
target_link_libraries($NOME PUBLIC Animator)
target_link_libraries($NOME PUBLIC BaseComponent)

target_include_directories($NOME PUBLIC
                           "\${PROJECT_BINARY_DIR}/src/$NOME"
                           )

install(TARGETS $NOME
        EXPORT ${NOME}Targets
        DESTINATION lib)

install(FILES "\${PROJECT_BINARY_DIR}/src/$NOME/$NOME.hpp" DESTINATION include)
EOL

echo "Projeto $NOME criado com sucesso em src/$NOME"
