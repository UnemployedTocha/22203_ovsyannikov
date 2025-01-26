#include <limits.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>


typedef struct {
    char src_path[PATH_MAX];
    char dest_path[PATH_MAX];
} args_t;

int safe_open(const char* path, int flags, mode_t mode) {
    int fd;
    while ((fd = open(path, flags, mode)) == -1 && errno == EMFILE) {
        perror("too many files open");
        sleep(1);
    }
    return fd;
}

DIR* safe_opendir(const char* path) {
    DIR* dir;
    while ((dir = opendir(path)) == NULL && errno == EMFILE) {
        perror("too many dirs open");
        sleep(1);
    }
    return dir;
}

void* copy_file(void* args) {
    args_t* args_  = (args_t*)args;
    int src_fd;
    int dest_fd;
    int buff_len = 8192;
    char buffer[buff_len];
    ssize_t bytes_read;

    src_fd = safe_open(args_->src_path, O_RDONLY, 0);   
    dest_fd = safe_open(args_->dest_path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
 
    while ((bytes_read = read(src_fd, buffer, buff_len)) > 0) {
        write(dest_fd, buffer, bytes_read);
    }
    close(src_fd);
    close(dest_fd);
    free(args_);
    pthread_exit(NULL);
}

void* copy_directory(void* args) {
    pthread_attr_t attr;
    char src_entry_path[PATH_MAX]; 
    args_t* args_ = (args_t*)args;
    DIR* src_dir;
    struct dirent* entry;
    struct stat st;
    char dest_entry_path[PATH_MAX];

    int res = pthread_attr_init(&attr);
    if(res != 0) {
  perror("Attr init failed\n");
  return 0;
    }
    res = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if(res != 0) {
  perror("Attr setdetach failed :( \n");
  return 0;
    }      

    src_dir = safe_opendir(args_->src_path);

    mkdir(args_->dest_path, 0755);

    while ((entry = readdir(src_dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
       continue;
  }
        snprintf(src_entry_path, PATH_MAX, "%s/%s", args_->src_path, entry->d_name);
        snprintf(dest_entry_path, PATH_MAX, "%s/%s", args_->dest_path, entry->d_name);
        if (stat(src_entry_path, &st) == -1) {
            perror("status err\n");
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            args_t* subdir_args = malloc(sizeof(args_t));
            strcpy(subdir_args->src_path, src_entry_path);
            strcpy(subdir_args->dest_path, dest_entry_path);
            pthread_t thread;

            pthread_create(&thread, &attr, copy_directory, subdir_args);
            //pthread_detach(thread);
        } else if (S_ISREG(st.st_mode)) {
            args_t* file_args = malloc(sizeof(args_t));
            strcpy(file_args->src_path, src_entry_path);
            strcpy(file_args->dest_path, dest_entry_path);
            pthread_t thread;
            pthread_create(&thread, &attr, copy_file, file_args);
            //pthread_detach(thread);
        }
    }

    res = pthread_attr_destroy(&attr);
    if (res != 0) {
  perror("pthread_attr_dedtroy failed :((((((( \n");
    }
    closedir(src_dir);
    free(args_);
    pthread_exit(NULL);
}

int main(int argc, char** argv) {
    pthread_t thread;  
    if (argc != 3) {
        printf("incorrect args num\n");
        return EXIT_FAILURE;
    }

    args_t* args = malloc(sizeof(args_t));
    strcpy(args->src_path, argv[1]);
    strcpy(args->dest_path, argv[2]);

    pthread_create(&thread, NULL, copy_directory, args);
    pthread_join(thread, NULL);
    pthread_exit(NULL);
}
