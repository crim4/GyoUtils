#define sin __sin
#define cos __cos
#define tan __tan
#define sqrt __sqrt
#include <chrono>
#undef sqrt
#undef sin
#undef cos
#undef tan

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../gyoutils.h"

#define PRINT_TESTS
#include "src/lib.cpp"

#include "src/math/simple.cpp"
#include "src/math/vec2.cpp"
#include "src/math/vec3.cpp"
#include "src/math/vec4.cpp"
#include "src/math/mat4.cpp"

#include "src/prints.cpp"

#include "../win64_files.h"
#include <Windows.h>

bool test(int a) {
    print("a %", a);
    defer({print("b %", a); print("another one"); });
    
    if(a < 3) return false;
    
    print("c %", a);
    defer(print("d %", a));
    
    return true;
}

int main() {

    print("%\\%, %", 10, 15);
    print("%\\%, %", 10, 15);
    print("%\\%, %", 10, 15);

    #if 0    
    Array<str> arr = array_new<str>(20);
    get_only_files_in_dir(".\\src", &arr);
    
    Array<str> arr2 = array_new<str>(20);
    get_only_files_in_dir(".\\src\\math", &arr2);
    
    print("CLASSIC FOR:");
    for(int i = 0; i < arr.size; i++) {
        print("file %=%", i, arr[i]);
    }
    
    print("\nCLASSIC FOR AGAIN:");
    for(int i = 0; i < arr.size; i++) {
        print("file %=%", i, arr[i]);
    }
    
    print("\nNEW FOR:");
    For(arr) {
        print("file %='%'", it_index, it);
    }
    
    print("\nNEW FOR AGAIN:");
    For(arr) {
        print("file %=%", it_index, it);
    }
    
    print("\nNEW FOR WITH PTR:");
    For_ptr(arr) {
        print("file %=%", it_index, *it);
    }
    
    print("\nNEW FOR REV:");
    For_rev(arr) {
        print("file %=%", it_index, it);
    }
    
    print("\nNEW FOR REV WITH PTR:");
    For_ptr_rev(arr) {
        print("file %=%", it_index, *it);
    }
    
    print("\nNEW FOR REV WITH PTR:");
    For_rev_ptr(arr) {
        print("file %=%", it_index, *it);
    }
    
    print("\nCLASSIC FOR 2:");
    for(int i = 0; i < arr.size; i++) {
        print("file %=%", i, arr[i]);
    }

    print("\nNEW FOR OF STR:");
    For(arr[0]) {
        print("file %=%", it_index, (char)it);
    }

    print("\nOLD FOR:");
    OLDFor(arr) {
        print("file %=%", it.index, it.value);
    }
    
    print("\nOLD FOR AGAIN:");
    OLDFor(arr) {
        print("file %=%", it.index, it.value);
    }
    #endif
    
    // test_simple_math();
    // test_vec2_math();
    // test_vec3_math();
    // test_vec4_math();
    // test_mat4_math();
    
    // print("\nAll % tests passed succesfully", _cnt);
    return 0;
}
