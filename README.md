# Advent of Code

This is the start of a little project.
I want to solve every year of advent of code in a different programming language.
The plan:

| Year | Language   | Progress |
|------|------------|----------|
| 2015 | C++        | 34/50    |
| 2016 | Rust       | 12/50    |
| 2017 | JavaScript | -        |
| 2018 | Java       | -        |
| 2019 | Dart       | -        |
| 2020 | Swift      | -        |
| 2021 | Lua        | -        |
| 2022 | Zig        | -        |
| 2023 | OCaml      | -        |
| 2024 | Python     | -        |

# Advent of Code 2015 - C++

During this I developed a rather (at least for my standards) refined template for AoC-C++-projects.\
To start using it grab this repository, delete the src-folder, set the year in `generateDays.py` and\
run `py ./generateDays.py`\
(If I am bored I might make a template-repo)

## The Template

- `/templates` these files  are copied to each day when `generateDays.py` is executed (small str-replace to print year and day)\
- `/deps` libraries; only spdlog for now\
- `/src` contains all days
  - text files are generally input data; prefix "t" stands for "testdata"\
- `/utils` some utils which I'm quite proud of:
  - `extract_data<Ts...>(pattern, string)` makes a regex match and converts the matches to the given Ts. If you want to add more Ts just implement a template specialization of `generic_from_string<T>(string)` 
  - `Runner<Result, Args...>(solver_fn, year, day)` used for testing and running the given solver-function
    - add tests with `add_test_string(string, expected, args...)` or `add_test_file(filename, expected, args...)`
    - add read inputs with `add_input_string(string, args...)` or `add_input_file(filename, args...)`
    - optionally transform result of real inputs automatically with `set_result_transformation(result_transform_fn)`
 

### Examples
```cpp
std::regex pattern("(.+) would (.+) (\\d+) happiness units by sitting next to (.+).");
const auto [person_a, signum, strength, person_b] =
    extract_data<std::string, std::string, int, std::string>(pattern, line);
```

```cpp
auto runner = Runner<int, int>(solve, 2015, 17);

runner.add_test_file("t1.txt", 4, 25);
runner.add_test_input("some test data", 10, 43);

runner.add_input_file("i1.txt", 150);

runner.run();
```