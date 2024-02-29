#include <stdio.h>
#include <dlfcn.h>

void load_lib_and_run_func() {
    void* handle;
    void (*dyn_print_hello)(void);
    char* er;

    handle = dlopen("./my_shared_lib.so", RTLD_LAZY);
    if(!handle) {
        printf("dlopen() failed: %s\n", dlerror());
        return;
    }
    dlerror();
    dyn_print_hello = (void (*)(void))dlsym(handle, "print_from_shared_dyn_lib");
    er = dlerror();

    if(er != NULL) {
        printf("dlsym failed: %s\n", dlerror());
        return;
    }

    dyn_print_hello();
    if(dlclose(handle) != 0) {
        printf("dlclose() failed");
        return;
    }
}

int main() {
    load_lib_and_run_func();
    return 0;
}
