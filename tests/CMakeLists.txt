add_subdirectory(hello_world)
add_subdirectory(region_test)
add_subdirectory(fib)
add_subdirectory(simple_collection)
add_subdirectory(simple_collection_fetch)
add_subdirectory(simple_collection_reduce)
add_subdirectory(simple_collection_data_reduce)
add_subdirectory(create_work_if_while)
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/scratch)
    add_subdirectory(scratch)
endif()
#add_subdirectory(simple_commutative)
#add_subdirectory(smart_ptr)
