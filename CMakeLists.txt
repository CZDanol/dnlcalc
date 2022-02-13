# Speedup tips:
# - use jom instead of make -> parallel builds

cmake_minimum_required(VERSION 3.20)

project(dnlcalc VERSION 0.0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(platform_config.cmake)

# ===========================================
# Qt
# ===========================================
find_package(Qt6 COMPONENTS Widgets Gui REQUIRED CONFIG)

# ===========================================
# Executable
# ===========================================
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

qt_add_executable(proj WIN32)

target_compile_definitions(proj PRIVATE QT_DISABLE_DEPRECATED_BEFORE=0x060200)
target_link_libraries(proj PRIVATE Qt6::Widgets Qt6::Gui)

# ===========================================
# Project config
# ===========================================
set(PROGRAM_NAME DNLCalc)

target_compile_definitions(proj PRIVATE
				"PROGRAM_VERSION=\"${CMAKE_PROJECT_VERSION}\""
				"PROGRAM_NAME_VERSION=\"${PROGRAM_NAME} ${CMAKE_PROJECT_VERSION}\""
				"PLATFORM_ID=\"${OS_STRING}_${PLATFORM_STRING}\""
				)

# ===========================================
# Sources & includes
# ===========================================
file(
				GLOB_RECURSE proj_src CONFIGURE_DEPENDS
				"src/*.cpp"
)

target_sources(proj PRIVATE ${proj_src})

target_include_directories(proj PRIVATE
	"src"
)
target_include_directories(proj SYSTEM PRIVATE
	"include"
)

# ===========================================
# Resources
# ===========================================
file(GLOB_RECURSE res_files CONFIGURE_DEPENDS "res/*")
qt_add_resources(proj "res"
				PREFIX "/res"
				BASE "res"
				FILES ${res_files}
				)

if (MSVC)
		# worldgenapi_cpu.cpp is not happy when this is not done, dunno why
		target_compile_options(proj PRIVATE /bigobj)

		# Enable parallel build
		target_compile_options(proj PRIVATE /MP)
endif ()

# ===========================================
# Deployment
# ===========================================
get_target_property(QMAKE_FILEPATH Qt6::qmake IMPORTED_LOCATION)

install(CODE "set(ac_client_target_file \"$<TARGET_FILE:proj>\")")
install(CODE "set(QMAKE_FILEPATH \"${QMAKE_FILEPATH}\")")
install(CODE "set(PROJECT_SOURCE_DIR \"${PROJECT_SOURCE_DIR}\")")
install(CODE "set(CMAKE_BINARY_DIR \"${CMAKE_BASE_DIR}\")")
install(SCRIPT "deploy.cmake")
