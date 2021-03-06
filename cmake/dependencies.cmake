include(FindPkgConfig)
include(ExternalProject)

set_directory_properties(PROPERTIES
	EP_PREFIX ${CMAKE_SOURCE_DIR}/external
)


pkg_check_modules(psocksxx REQUIRED psocksxx>=0.0.6)
pkg_check_modules(libconfig REQUIRED libconfig++>=1.4)
pkg_check_modules(python python>=2.7)
pkg_check_modules(pc_spdlog spdlog>=0.17.0)

if(NOT python_FOUND)
	# pkg-config couldn't find Python, try find_package()
	find_package(PythonLibs)
	if(PYTHONLIBS_FOUND)
		set(python_FOUND TRUE)
		set(python_INCLUDE_DIRS ${PYTHON_INCLUDE_DIRS})
		set(python_LDFLAGS ${PYTHON_LIBRARIES})
	endif()
endif()


find_package(Doxygen)


# spdlog
add_library(spdlog INTERFACE IMPORTED)
if(NOT pc_spdlog_FOUND)
	externalproject_add(gabime_spdlog
		GIT_REPOSITORY     https://github.com/gabime/spdlog.git
		GIT_TAG            v0.17.0
		CONFIGURE_COMMAND  ""
		BUILD_COMMAND      ""
		INSTALL_COMMAND    ""
		TEST_COMMAND       ""
		UPDATE_COMMAND     ""
	)

	externalproject_get_property(gabime_spdlog source_dir)
	file(MAKE_DIRECTORY ${source_dir}/include)
	set_target_properties(spdlog PROPERTIES
		INTERFACE_INCLUDE_DIRECTORIES ${source_dir}/include
	)

	add_dependencies(spdlog gabime_spdlog)
else()
	set_target_properties(spdlog PROPERTIES
		INTERFACE_INCLUDE_DIRECTORIES ${pc_spdlog_INCLUDE_DIRS}
	)
endif()

