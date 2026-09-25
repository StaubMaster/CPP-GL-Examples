
NAME := FileManager.a
FANCY_NAME := Engine/FileManager

################################################################

DIR_SRC := src/
DIR_OBJ := obj/

################################################################

FILES := \
	FilePath.cpp \
	FilePathSegment.cpp \
	FilePathSegmentCollection.cpp \
	FileMode.cpp \
	FileSystemStat.cpp \
	FileSystemInfo.cpp \
	FileInfo.cpp \
	DirectoryInfo.cpp \
	TextExceptionBase.cpp \
	FileExceptions.cpp \
\
	FileParsing/ByteBlock.cpp \
\
	FileParsing/ByteStreamBase.cpp \
	FileParsing/ByteStreamGetter.cpp \
	FileParsing/ByteStreamSetter.cpp \
	FileParsing/ByteStreamQueue.cpp \
\
	FileParsing/BitStreamBase.cpp \
	FileParsing/BitStreamGetter.cpp \
\
	FileParsing/LineCommand.cpp \
	FileParsing/DebugManager.cpp \
	FileParsing/StringHelp.cpp \
	FileParsing/ExceptionBase.cpp \
	FileParsing/CountCheck.cpp \
	FileParsing/ParsingCommand.cpp \
\
	FileParsing/TextCommand/LineStream.cpp \
	FileParsing/TextCommand/Exceptions.cpp \
	FileParsing/TextCommand/Args.cpp \
	FileParsing/TextCommand/ArgsStream.cpp \
	FileParsing/TextCommand/Func.cpp \
	FileParsing/TextCommand/FuncNormal.cpp \
	FileParsing/TextCommand/Loop.cpp \
\
	FileParsing/Variables/Float.cpp \
\
	FileFormat/PNG/ErrorDetection.cpp \
	FileFormat/PNG/Chunk.cpp \
	FileFormat/PNG/ZLIB.cpp \
	FileFormat/PNG/Huffman.cpp \
	FileFormat/PNG/DEFLATE.cpp \
	FileFormat/PNG/Filter.cpp \
	FileFormat/PNG/IHDR.cpp \
	FileFormat/PNG/PNG.cpp \
\
	FileFormat/BitMap/Exceptions.cpp \
	FileFormat/BitMap/Headers/BITMAPINFOHEADER.cpp \
	FileFormat/BitMap/BitMap.cpp \
\
	uint.cpp \
	Image.cpp \

################################################################

LIBRARYS  := $(NAME)
INCLUDES  := include/ ../ValueType/include/ ../Generics/include/
ARGUMENTS := 

################################################################

BASE_DIR := ../

include $(BASE_DIR)/MakefileArchiver.mk

################################################################
