#ifndef ABSTRACTFILE_H
#define ABSTRACTFILE_H

#include "common.h"

typedef struct AbstractFile AbstractFile;

typedef size_t (*WriteFunc)(AbstractFile* file, const void* data, size_t len);
typedef size_t (*ReadFunc)(AbstractFile* file, void* data, size_t len);
typedef int (*SeekFunc)(AbstractFile* file, off_t offset);
typedef off_t (*TellFunc)(AbstractFile* file);
typedef void (*CloseFunc)(AbstractFile* file);
typedef off_t (*GetLengthFunc)(AbstractFile* file);

struct AbstractFile {
	void* data;
	WriteFunc write;
	ReadFunc read;
	SeekFunc seek;
	TellFunc tell;
	GetLengthFunc getLength;
	CloseFunc close;
};

typedef struct {
	size_t offset;
	void** buffer;
	size_t bufferSize;
} MemWrapperInfo;

typedef struct {
	size_t offset;
	void** buffer;
	size_t* bufferSize;
	size_t actualBufferSize;
} MemFileWrapperInfo;

#ifdef __cplusplus
extern "C" {
#endif
	AbstractFile* createAbstractFileFromFile(FILE* file);
	AbstractFile* createAbstractFileFromDummy();
	AbstractFile* createAbstractFileFromMemory(void** buffer, size_t size);
	AbstractFile* createAbstractFileFromMemoryFile(void** buffer, size_t* size);
	AbstractFile* createAbstractFileFromMemoryFileBuffer(void** buffer, size_t* size, size_t actualBufferSize);
	void abstractFilePrint(AbstractFile* file, const char* format, ...);
	io_func* IOFuncFromAbstractFile(AbstractFile* file);
#ifdef __cplusplus
}
#endif

#endif
