CC = g++
CPPFLAGS = -g -Wall

TARGET = RegisterFile.cpp MemoryUnit.cpp simulator.cpp

LIB = pkg-config --cflags --libs
BUILD_DIR = ./build
MAIN = sim
clean:
	@echo Removing old build files :
	$(RM) -r $(BUILD_DIR)
build:
	@echo Building project :
	mkdir $(BUILD_DIR)
	$(CC) $(CPPFLAGS) -o $(BUILD_DIR)/$(MAIN) $(TARGET)
	@echo Generated the executable without errors ...
run:
	@echo Running the executable ...
	cd $(BUILD_DIR); ./$(MAIN) 4 -1

all : clean build run

.PHONY: clean build run all
