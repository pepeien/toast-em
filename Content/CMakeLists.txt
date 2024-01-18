##############  Set values  #######################
set(TARGET_NAME "${CONTENT_TARGET_NAME}")
set(SOURCES_DIR "${CONTENT_SOURCE_DIR}")

##############  Set source files  #######################
file(
    GLOB_RECURSE
    SOURCES

    "${SOURCES_DIR}/*.kerb"
)

##############  Copy files  #######################
foreach(ITEM ${SOURCES})
    get_filename_component(FILE_DIR  ${ITEM} DIRECTORY)
    get_filename_component(FILE_NAME ${ITEM} NAME)

    set(ITEM_DIR "${FILE_DIR}")
    string(REPLACE "${SOURCES_DIR}" "" ITEM_DIR ${ITEM_DIR})

    set(ITEM_DIR "${CONTENT_BUILD_DIR}/${ITEM_DIR}")
    string(REPLACE "//" "/" ITEM_DIR ${ITEM_DIR})

    file(MAKE_DIRECTORY "${ITEM_DIR}")

    set(ITEM_FILE "${ITEM_DIR}/${FILE_NAME}")
    string(REPLACE "//" "/" ITEM_FILE ${ITEM_FILE})

    configure_file(${ITEM} ${ITEM_FILE} COPYONLY)

    list(APPEND FILES ${ITEM_FILE})
endforeach(ITEM)

add_custom_target(
    ${TARGET_NAME}
    DEPENDS

    ${FILES}
)