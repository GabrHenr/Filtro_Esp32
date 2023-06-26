# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.
set(app_sources
    "main.c"

    # EMBED_FILES "root.html"
)

idf_component_register(SRCS ${app_sources})
target_add_binary_data(${COMPONENT_TARGET} "root.html" TEXT)
target_add_binary_data(${COMPONENT_TARGET} "Background.webp" TEXT)