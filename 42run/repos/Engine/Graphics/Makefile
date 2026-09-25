
NAME := Graphics.a
FANCY_NAME := Engine/Graphics

################################################################

DIR_SRC := src/Graphics/
DIR_OBJ := obj/Graphics/

################################################################

FILES := \

################################################################

FILES += \
	Shader/Code.cpp \
	Shader/Base.cpp \
	Shader/_Log.cpp \
	ShaderBlockBinding.cpp \

################################################################

FILES += \
	Uniform/General/Base.cpp \
	Uniform/General/FloatNBase.cpp \
	Uniform/General/FloatNType.cpp \
	Uniform/General/UIntNBase.cpp \
	Uniform/General/UIntNType.cpp \
\
	Uniform/General/Layout.cpp \
	Uniform/General/Buffer.cpp \
\
	Uniform/Trans2D.cpp \
	Uniform/Trans3D.cpp \
\
	Uniform/Depth.cpp \
	Uniform/RangeF.cpp \
	Uniform/LInter.cpp \
\
	Uniform/Light/Base.cpp \
	Uniform/Light/Point.cpp \
	Uniform/Light/Direction.cpp \
	Uniform/Light/Spot.cpp \
\
	Uniform/AspectRatio.cpp \
	Uniform/PixelSize.cpp \
	Uniform/DisplaySize.cpp \
\
	Uniform/_Log.cpp \

################################################################

FILES += \
	Multiform/General/Base.cpp \
	Multiform/General/Layout.cpp \
	Multiform/General/Buffer.cpp \

################################################################

FILES += \
	Buffer/Base.cpp \
	Buffer/Array.cpp \
	Buffer/Element.cpp \
	Buffer/Uniform.cpp \
	Buffer/_Log.cpp \
\
	VertexArray/Base.cpp \
	VertexArray/Main.cpp \
	VertexArray/MainInst.cpp \
	VertexArray/MainElemInst.cpp \
	VertexArray/Multi.cpp \

################################################################

FILES += \
	Attribute/General/Base.cpp \
	Attribute/General/FloatNBase.cpp \
	Attribute/General/UIntNBase.cpp \
	Attribute/General/IntNBase.cpp \
	\
	Attribute/General/Layout.cpp \
	Attribute/General/_Log.cpp \
\
	Attribute/BoxF2.cpp \

################################################################

FILES += \
	Texture/Base.cpp \
	Texture/Array2D.cpp \
	Texture/Generate.cpp \

################################################################

FILES += \
	PaddedBlock/LightBase.cpp \
	PaddedBlock/LightDirection.cpp \
	PaddedBlock/LightPoint.cpp \
	PaddedBlock/LightSpot.cpp \

################################################################

LIBRARYS  := $(NAME)
INCLUDES  := include/ ../include/ ../ValueType/include/ ../Generics/include/ ../FileManager/include/ ../OpenGL/include ../Display/include/
ARGUMENTS := 

################################################################

BASE_DIR := ../

include $(BASE_DIR)/MakefileArchiver.mk

################################################################
