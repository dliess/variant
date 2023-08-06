find_package(GTest REQUIRED)

set(SOURCES 
    "UT_Variant.cpp"
)

set(TARGET_NAME VariantTest)
add_executable(${TARGET_NAME} ${SOURCES})
target_link_libraries(${TARGET_NAME}
    GTest::GTest
    GTest::Main
    Variant::Variant
)

add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})