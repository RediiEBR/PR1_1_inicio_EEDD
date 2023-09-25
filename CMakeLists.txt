cmake_minimum_required(VERSION 3.21)
project(imagenes)

set(CMAKE_CXX_STANDARD 20)

add_executable(imagenes main.cpp fecha.cpp Imagen.cpp Imagen.h vEstatico.h forwardList.h
        vDinamico.h
        ListaDe.h)
