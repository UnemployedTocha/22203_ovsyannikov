#include <stdio.h>

int* get_pointer_v1() { 
    int a = 10;
    return &a;
}

int* get_pointer_v2() { 
    int a = 10;
    int *pa = &a;
    return pa;
}

int main(int argc, char* argv[]) {
    int* ptr1 = get_pointer_v1();
    printf("ptr1: %d\n", ptr1);     //ptr1: (null)   
    printf("*ptr1 = %d\n", *ptr1);  //segmentation fault
  
    int* ptr2 = get_pointer_v2();   
    printf("ptr2: %p\n", ptr2);     //ptr2: some adress   
    printf("*ptr2 = %d\n", *ptr2);  //ub 
}
