
add_executable(aoc2015_05_1 part1.cpp ../../utils/Logger.cpp)

target_link_dependency(aoc2015_05_1 HEADER spdlog-1.14.1)
target_include_directories(aoc2015_05_1 PUBLIC ../../utils)


add_executable(aoc2015_05_2 part2.cpp ../../utils/Logger.cpp)

target_link_dependency(aoc2015_05_2 HEADER spdlog-1.14.1)
target_include_directories(aoc2015_05_2 PUBLIC ../../utils)
