CMAKE_MINIMUM_REQUIRED(VERSION 3.13)

IF(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  SET(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake CACHE STRING "")
ENDIF()

PROJECT(Atrc)

INCLUDE_DIRECTORIES($ENV{AGZ_UTILS_HOME})
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/Source/)

SET(CMAKE_CXX_STANDARD 17)

IF(MSVC)
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
ENDIF()

FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(glfw3 CONFIG REQUIRED)
FIND_PACKAGE(GLEW REQUIRED)

FILE(GLOB_RECURSE LIB_SRC_CAMERA         "Source/Atrc/Lib/Camera/*.cpp"        "Source/Atrc/Lib/Camera/*.h")
FILE(GLOB_RECURSE LIB_SRC_CORE           "Source/Atrc/Lib/Core/*.cpp"          "Source/Atrc/Lib/Core/*.h")
FILE(GLOB_RECURSE LIB_SRC_ENTITY         "Source/Atrc/Lib/Entity/*.cpp"        "Source/Atrc/Lib/Entity/*.h")
FILE(GLOB_RECURSE LIB_SRC_FILM_FILTER    "Source/Atrc/Lib/FilmFilter/*.cpp"    "Source/Atrc/Lib/FilmFilter/*.h")
FILE(GLOB_RECURSE LIB_SRC_GEOMETRY       "Source/Atrc/Lib/Geometry/*.cpp"      "Source/Atrc/Lib/Geometry/*.h")
FILE(GLOB_RECURSE LIB_SRC_LIGHT          "Source/Atrc/Lib/Light/*.cpp"         "Source/Atrc/Lib/Light/*.h")
FILE(GLOB_RECURSE LIB_SRC_MATERIAL       "Source/Atrc/Lib/Material/*.cpp"      "Source/Atrc/Lib/Material/*.h")
FILE(GLOB_RECURSE LIB_SRC_MEDIUM         "Source/Atrc/Lib/Medium/*.cpp"        "Source/Atrc/Lib/Medium/*.h")
FILE(GLOB_RECURSE LIB_SRC_POST_PROCESSOR "Source/Atrc/Lib/PostProcessor/*.cpp" "Source/Atrc/Lib/PostProcessor/*.h")
FILE(GLOB_RECURSE LIB_SRC_RENDERER		 "Source/Atrc/Lib/Renderer/*.cpp"      "Source/Atrc/Lib/Renderer/*.h")
FILE(GLOB_RECURSE LIB_SRC_REPORTER		 "Source/Atrc/Lib/Reporter/*.cpp"      "Source/Atrc/Lib/Reporter/*.h")
FILE(GLOB_RECURSE LIB_SRC_SAMPLER		 "Source/Atrc/Lib/Sampler/*.cpp"       "Source/Atrc/Lib/Sampler/*.h")
FILE(GLOB_RECURSE LIB_SRC_TEXTURE		 "Source/Atrc/Lib/Texture/*.cpp"       "Source/Atrc/Lib/Texture/*.h")
FILE(GLOB_RECURSE LIB_SRC_UTILITY		 "Source/Atrc/Lib/Utility/*.cpp"       "Source/Atrc/Lib/Utility/*.h")
ADD_LIBRARY(
	Lib STATIC
	${LIB_SRC_CAMERA}
	${LIB_SRC_CORE}
	${LIB_SRC_ENTITY}
	${LIB_SRC_FILM_FILTER}
	${LIB_SRC_GEOMETRY}
	${LIB_SRC_LIGHT}
	${LIB_SRC_MATERIAL}
	${LIB_SRC_MEDIUM}
	${LIB_SRC_POST_PROCESSOR}
	${LIB_SRC_RENDERER}
	${LIB_SRC_REPORTER}
	${LIB_SRC_SAMPLER}
	${LIB_SRC_TEXTURE}
	${LIB_SRC_UTILITY})
SOURCE_GROUP("Camera"        FILES ${LIB_SRC_CAMERA})
SOURCE_GROUP("Core"          FILES ${LIB_SRC_CORE})
SOURCE_GROUP("Entity"        FILES ${LIB_SRC_ENTITY})
SOURCE_GROUP("FilmFilter"    FILES ${LIB_SRC_FILM_FILTER})
SOURCE_GROUP("Geometry"      FILES ${LIB_SRC_GEOMETRY})
SOURCE_GROUP("Light"         FILES ${LIB_SRC_LIGHT})
SOURCE_GROUP("Material"      FILES ${LIB_SRC_MATERIAL})
SOURCE_GROUP("Medium"        FILES ${LIB_SRC_MEDIUM})
SOURCE_GROUP("PostProcessor" FILES ${LIB_SRC_POST_PROCESSOR})
SOURCE_GROUP("Renderer"      FILES ${LIB_SRC_RENDERER})
SOURCE_GROUP("Reporter"      FILES ${LIB_SRC_REPORTER})
SOURCE_GROUP("Sampler"       FILES ${LIB_SRC_SAMPLER})
SOURCE_GROUP("Texture"       FILES ${LIB_SRC_TEXTURE})
SOURCE_GROUP("Utility"       FILES ${LIB_SRC_UTILITY})

FILE(GLOB MGR_SRC_OUTER			  "Source/Atrc/Mgr/*.cpp"				 "Source/Atrc/Mgr/*.h")
FILE(GLOB_RECURSE MGR_SRC_BUILTIN "Source/Atrc/Mgr/BuiltinCreator/*.cpp" "Source/Atrc/Mgr/BuiltinCreator/*.h")
ADD_LIBRARY(Mgr STATIC ${MGR_SRC_OUTER} ${MGR_SRC_BUILTIN})
SOURCE_GROUP("Builtin" FILES ${MGR_SRC_BUILTIN})
SOURCE_GROUP(""		   FILES ${MGR_SRC_OUTER})

FILE(GLOB_RECURSE IMGUI_SRC "Source/Lib/imgui/*.cpp" "Source/Lib/imgui/*.h")
ADD_LIBRARY(ImGui STATIC ${IMGUI_SRC})
TARGET_INCLUDE_DIRECTORIES(ImGui PRIVATE ${GLEW_INCLUDE_DIRS})
TARGET_INCLUDE_DIRECTORIES(ImGui PRIVATE ${glfw3_INCLUDE_DIRS})

FILE(GLOB_RECURSE LAUNCHER_SRC "Source/Atrc/Launcher/*.cpp" "Source/Atrc/Launcher/*.h")
ADD_EXECUTABLE(Launcher ${LAUNCHER_SRC})
TARGET_LINK_LIBRARIES(Launcher Lib Mgr)

FILE(GLOB_RECURSE MODELVIEWER_SRC "Source/Atrc/ModelViewer/*.cpp" "Source/Atrc/ModelViewer/*.h")
ADD_EXECUTABLE(ModelViewer ${MODELVIEWER_SRC})

TARGET_INCLUDE_DIRECTORIES(ModelViewer PRIVATE ${GLEW_INCLUDE_DIRS})
TARGET_INCLUDE_DIRECTORIES(ModelViewer PRIVATE ${glfw3_INCLUDE_DIRS})
TARGET_INCLUDE_DIRECTORIES(ModelViewer PRIVATE ${OPENGL_INCLUDE_DIRS})

TARGET_LINK_LIBRARIES(ModelViewer PRIVATE ImGui)
TARGET_LINK_LIBRARIES(ModelViewer PRIVATE GLEW::GLEW)
TARGET_LINK_LIBRARIES(ModelViewer PRIVATE glfw)
TARGET_LINK_LIBRARIES(ModelViewer PRIVATE ${OPENGL_LIBRARIES})