cmake_minimum_required(VERSION 3.23)
project(Managing_Financial_Data_Project2_C C)

set(CMAKE_C_STANDARD 99)

add_executable(Managing_Financial_Data_Project2_C main.c
        validation.c dynamic_customers.c customers_crud.c
        custom_objects.c dynamic_accounts.c accounts_crud.c
        transactions.c)
