
add_executable(aoc2015_03_1
        part1.cpp
        ../../utils/Logger.cpp
        ../../utils/utils.h
        ../../utils/matrix.h
)

target_link_dependency(aoc2015_03_1 HEADER spdlog-1.14.1)
target_include_directories(aoc2015_03_1 PUBLIC ../../utils)


add_executable(aoc2015_03_2
        part2.cpp
        ../../utils/Logger.cpp
        ../../utils/utils.h
        ../../utils/matrix.h
)


target_link_dependency(aoc2015_03_2 HEADER spdlog-1.14.1)
target_include_directories(aoc2015_03_2 PUBLIC ../../utils)
