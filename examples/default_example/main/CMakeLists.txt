# Be aware this file should not be takes as inspiration on how to set up compilation with the CMake build system when using ESP-IDF, because it directly includes the implementation files.
# This has to be done because the examples are build to test if they are still working and to automatically inform the library if a pull request would break examples.
# To actually include the library in your ESP-IDF project read the documentation especially the Installation section
set(srcs
    xgzf4000-poll-data.c
    ../../../xgzf4000.c
)

idf_component_register(
    SRCS ${srcs}
    INCLUDE_DIRS "../../../include"
    PRIV_INCLUDE_DIRS "../../../priv_include"
)