#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

void swap(char* a, char* b) {
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

int GetDirNamePos(char* path, int pathLength) {
	int dirNamePos = 0;
	for(size_t i = pathLength - 1; i >= 0; --i) {
		if(path[i] == '/') {
			dirNamePos = i + 1;
			break;
		}
	}
	return dirNamePos;
}

char* GetPathReverseDir(char* path) {
	int pathLength = strlen(path);
	char* reverseDirName = (char*)malloc(pathLength);
	strcpy(reverseDirName, path);

	int dirNamePos = GetDirNamePos(path, pathLength);
	for(size_t i = dirNamePos; i < (pathLength + dirNamePos) / 2; ++i) {
        swap(&(reverseDirName[i]), &(reverseDirName[pathLength - 1 - i + dirNamePos]));
	}

	return reverseDirName;
}

char* Concatenate(char* pathDir, int lenPathDir, char* fileName, int lenFileName) {
	int resultLength = lenPathDir + 1 + lenFileName;
	char* result = (char*)malloc(resultLength);
	memcpy(result, pathDir, lenPathDir);
	result[lenPathDir] = '/';
	memcpy(result + lenPathDir + 1, fileName, lenFileName);
	return result;
}

int GetSeporatorPossition(char* str, int length, char seporator) {
	size_t pos = 0;
	for(; pos < length; ++pos) {
		if(str[pos] == seporator) break;
	}

	return pos;
}

char* GetReverseFileName(char* fileName, int lenFileName) {
	char* reverseFileName = (char*)malloc(lenFileName);
	memcpy(reverseFileName, fileName, lenFileName);

	size_t seporPos = GetSeporatorPossition(fileName, lenFileName, '.');
	for(size_t i = 0; i < seporPos / 2; ++i) {
		swap(&reverseFileName[i], &reverseFileName[seporPos - i - 1]);
	}
	return reverseFileName;
}



void MakeReverseFile(char* pathOrigDir, char* pathReverseDir, char* fileName) {
	int lenFileName = 0;
	for(size_t i = 0; fileName[i] != '\0'; ++i) {
		lenFileName++;
	}
		
	FILE* origFile; 
    FILE* reverseFile;

	char* pathOrigFile = Concatenate(pathOrigDir, strlen(pathOrigDir), fileName, lenFileName);
	if((origFile = fopen(pathOrigFile, "rb")) == NULL) {
		printf("Unable to open file. Filepath:\n%s\n", pathOrigFile);
		free(pathOrigFile);
		return;
	}

	char* reverseFileName = GetReverseFileName(fileName, lenFileName);
	char* pathReverseFile = Concatenate(pathReverseDir, strlen(pathReverseDir), reverseFileName, lenFileName);
	if((reverseFile = fopen(pathReverseFile, "wb")) == NULL) {
		printf("Unable to open file. Filepath:\n%s\n", pathReverseFile);
		free(pathOrigFile);
		free(pathReverseFile);
    fclose(origFile);
    return;
	}

	  // Устанавливает внутренний указатель положения в файле, в новую позицию, которая определяются путем добавления
    // cмещения к исходному положению.
    fseek(origFile, -1, SEEK_END);
    // Возвращается значение соответствующее количеству байт от начала файла.
	  int sizeOrigFile = ftell(origFile);
    for(int filePos = sizeOrigFile; filePos >= 0; --filePos) {
		fseek(origFile, filePos, SEEK_SET);
		fputc(fgetc(origFile), reverseFile);
	}

	free(pathOrigFile);
	free(reverseFileName);
	free(pathReverseFile);
	fclose(origFile);
	fclose(reverseFile);
}

void ReverseRegularFiles(char* pathOrigDir, char* pathReverseDir) {
	DIR* dp;
	if((dp = opendir(pathOrigDir)) == NULL) {
		printf("Unable to open directory. Dirpath:\n%s\n", pathOrigDir);
		return;
	}
/*    
    struct dirent {
    ino_t          d_ino;        номер inode
    off_t          d_off;        не смещение;
    unsigned short d_reclen;     длина этой записи 
    unsigned char  d_type;       тип файла; поддерживается
                                   не всеми типами файловых систем
    char           d_name[256];  имя файла 
};

*/
    struct dirent* entry;
	while((entry = readdir(dp)) != NULL) {
		if(entry->d_type == DT_REG) {
			MakeReverseFile(pathOrigDir, pathReverseDir, entry->d_name);
		}
	}

	closedir(dp);
}

int MakeReverseDir(char* pathOrigDir) {
	struct stat dirstat;
	if (stat(pathOrigDir, &dirstat) == 0) {
		char* pathReverseDir = GetPathReverseDir(pathOrigDir);
		mkdir(pathReverseDir, dirstat.st_mode);
		ReverseRegularFiles(pathOrigDir, pathReverseDir);
		return 0;
	} 
    return -1;
}

int main(int argc, char* argv[]) {
	if(argc != 2) {
		printf("Error: incorrect number of arguments\n");
		exit(EXIT_FAILURE);
	}
	
	int ret = MakeReverseDir(argv[1]);

	if(ret == -1) {
		printf("Something went wrong \"%s\"\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	return 0;
}
