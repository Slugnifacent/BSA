EXTERNAL_LIBS=/Users/bijan/joshScripts/CPP-Code/Test/Libs

CC=g++
CFLAGS=
OBJECTS=$(EXTERNAL_LIBS)/codecvt_error_category.o $(EXTERNAL_LIBS)/operations.o $(EXTERNAL_LIBS)/path.o $(EXTERNAL_LIBS)/path_traits.o $(EXTERNAL_LIBS)/portability.o $(EXTERNAL_LIBS)/unique_path.o $(EXTERNAL_LIBS)/utf8_codecvt_facet.o $(EXTERNAL_LIBS)/windows_file_codecvt.o
EXE_NAME=MetaData
LDFLAGS=-lboost_filesystem -lboost_system
CPPFLAGS=-DDEBUG_LOG


BOOST_INCLUDE=/Users/bijan/joshScripts/CPP-Code/boost_1_60_0/
INCLUDE=-I $(BOOST_INCLUDE)

CreateMeta : 
	$(CC) $(INCLUDE) test.cpp $(CPPFLAGS) -o $(EXE_NAME)  -L$(EXTERNAL_LIBS) $(LDFLAGS)
