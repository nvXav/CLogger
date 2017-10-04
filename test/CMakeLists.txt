include_directories(
    ${CMAKE_SOURCE_DIR}/src
)

set(HEADER
    ${CMAKE_SOURCE_DIR}/src/CLogger.h
)

set(SOURCE
    ${CMAKE_SOURCE_DIR}/src/CLogger.c
    TestMain.c
)

add_executable(CLogger ${SOURCE})
