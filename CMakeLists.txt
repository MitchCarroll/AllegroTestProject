cmake_minimum_required(VERSION 2.6)
#this is the minimum supported CMake version
project("AllegroTestProject")
#this is our project name, but also the name of the install dir
add_definitions(-DDATADIR="${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}/data/")
#this defines a constant that we can use in our code. see src/test.cpp for info
link_libraries(allegro allegro_main allegro_image)
#this is a list of libraries to link with (e.g.: -lallegro)
set(SOURCES
  src/test.cpp)
#here, we list all of our source files
add_executable(altest ${SOURCES})
#this command names the executable, and which files get compiled to make it
install(DIRECTORY data DESTINATION "share/${PROJECT_NAME}")
#this installs our data directory to the proper system folder
install(PROGRAMS altest DESTINATION bin)
#this installs the executable to the proper system directory
include(InstallRequiredSystemLibraries)
#this makes the makefile check for our libraries before trying to install
set(CPACK_PACKAGE_CONTACT "c.mitch.carroll@gmail.com")
#you need this to create a .deb package
include(CPack)
#this lets CPack create different distribution packages

