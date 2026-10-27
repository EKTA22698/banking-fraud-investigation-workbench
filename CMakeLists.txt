cmake_minimum_required(VERSION 3.16)

project(BankingFraudWorkbench LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(fraud_workbench
    src/main.c
    src/core/transaction.c
    src/core/dataset.c
    src/core/fraud.c
    src/cli/cli.c
    src/algorithms/sorting/merge_sort.c
    src/algorithms/sorting/quick_sort.c
    src/algorithms/searching/binary_search.c
)

target_include_directories(fraud_workbench PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)