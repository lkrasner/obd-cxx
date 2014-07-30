SHELL := /bin/bash

INSTALL_DIR := /usr/local
PKGS := muparser
CXXFLAGS := -std=c++11 -Iinclude -Wall -Wextra $(shell pkg-config --cflags $(PKGS))
LDLIBS := $(shell pkg-config --libs $(PKGS))
OBJS := $(patsubst %.cpp, %.o, $(wildcard src/*.cpp)) 
LIBS := lib/libobd-cxx.so

LIB_DIR := lib

all : CXXFLAGS += -O2
all : $(LIBS)

debug : CXXFLAGS += -g
debug : $(LIBS)

$(LIBS) : CXXFLAGS += -fPIC
$(LIBS) : LDFLAGS += -shared
$(LIBS) : $(OBJS)

install : all
	install $(LIB_DIR)/* $(INSTALL_DIR)/lib
	mkdir -p $(INSTALL_DIR)/include/obd-cxx
	install -c -D include/* $(INSTALL_DIR)/include/obd-cxx/
	install -c -D obd-cxx.pc $(INSTALL_DIR)/lib/pkgconfig/

uninstall:
	rm -f $(INSTALL_DIR)/lib/libobd-cxx.so
	rm -rf $(INSTALL_DIR)/include/obd-cxx
	rm -f $(INSTALL_DIR)/lib/pkgconfig/obd-cxx.pc

clean :
	@rm -f src/*.o
	@rm -f lib/*

$(LIB_DIR)/%.so :
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

% : %.o
	$(CXX) $(LDFLAGS) -o $@ $< $(LDLIBS)
.PHONY : all clean debug install
