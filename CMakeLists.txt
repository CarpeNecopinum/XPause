CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

#############
# XIntercept library - Hook to observe XCreateWindow calls
#############
set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/")
set(LIBRARIES ${LIBRARIES} "-ldl")
add_library("xintercept" SHARED "XLibIntercept.c" "common.h")
TARGET_LINK_LIBRARIES("xintercept" ${LIBRARIES})

#############
# XPause program executable
#############

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin/")
set(LIBRARIES ${LIBRARIES} "-ldl -lX11")
add_executable("xpause" "XPause.c" "common.h")
TARGET_LINK_LIBRARIES("xpause" ${LIBRARIES})


install(TARGETS xpause xintercept
        RUNTIME DESTINATION /usr/local/bin/
        LIBRARY DESTINATION /usr/local/lib/
       )
