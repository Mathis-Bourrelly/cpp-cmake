# Configuration de CMake pour TP C++ Moderne esimed
cmake_minimum_required(VERSION 3.29)

# Nom du projet et de l'exécutable généré
project(template_cpp_cmake)

# Forcer l'utilisation de C++ 23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Tout doit être parfait
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
# Ne pas utiliser les extensions de CMake
set(CMAKE_CXX_EXTENSIONS OFF)

# Répertoire contenant les sources des exercices
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
# Répertoire contenant les sources des tests unitaires
set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

# Pour "import std"
include(cmake/std.cmake)

#######################################################
# Partie à mettre à jour manuellement
# Liste des fichiers sources des modules des exercices
set(PROJECT_FILES
        ${SRC_DIR}/exo1.cppm
)
# Liste des fichiers sources des tests unitaires
set(TEST_FILES
        ${TESTS_DIR}/exo1.cpp
)
# Exécutable principal
add_executable(${PROJECT_NAME}
        ${SRC_DIR}/main.cpp
)
#######################################################

# Pour les tests unitaires
include(cmake/catch2.cmake)

target_sources(${PROJECT_NAME}
        PUBLIC
        FILE_SET CXX_MODULES
        FILES
        ${PROJECT_FILES}
)

# Exécutable pour les tests unitaires
add_executable(tests ${TEST_FILES})
target_sources(tests
        PUBLIC
        FILE_SET CXX_MODULES
        FILES
        ${PROJECT_FILES}
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

# Configuration automatique pour CTest
include(CTest)
include(Catch)
catch_discover_tests(tests)
