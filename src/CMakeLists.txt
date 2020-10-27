project(SCalculator_src)

set(PROJECT_LIB
        ./config.hpp
        ./config.cpp
        frontend/window.cpp
        frontend/window.hpp
)

add_library(SCalculatorLib SHARED ${PROJECT_LIB})
set_target_properties(SCalculatorLib PROPERTIES OUTPUT_NAME libSCalculator.so)
target_link_libraries(SCalculatorLib PUBLIC ${GTKMM_LIBRARIES})
