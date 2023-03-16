CC=g++ -std=c++17 -Wall -Werror -Wextra
CHECKFLAGS=-lgtest
CURRENTDIR = $(shell pwd)
BUILD_DIR=build
INSTALL_DIR=3DViewer_v2_0
APP=3DViewer_v2_0
REPORTDIR=gcov_report
GCOV=--coverage
OPEN=
FILTER=

OS = $(shell uname)

ifeq ($(OS), Linux)
	CC+=-D OS_LINUX -g -s
	CHECKFLAGS+=-lpthread
	CHECK_LEAKS=CK_FORK=no valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=log.txt
	OPEN=xdg-open
	DIR=
	QTFLAGS=-spec linux-g++
else
	CC+=-D OS_MAC
	CHECK_LEAKS=CK_FORK=no leaks --atExit --
	FILTER=--gtest_filter=-*.Exception
	OPEN=open
	DIR=/$(APP).app
	QTFLAGS=
endif

all: build

build: 
	qmake -o $(BUILD_DIR)/Makefile $(APP).pro $(QTFLAGS) CONFIG+=qtquickbuilder
	make -C $(BUILD_DIR)/ first

rebuild: clean all

install: build
	mkdir -p $(INSTALL_DIR)
	cp -r $(BUILD_DIR)$(DIR) $(INSTALL_DIR)

dist: install
	tar -czvf $(INSTALL_DIR).tgz $(INSTALL_DIR)
	mv $(INSTALL_DIR).tgz $(INSTALL_DIR)

uninstall:
	@rm -rf $(INSTALL_DIR)

dvi:
	$(OPEN) ./docs/dvi.html

tests: clean
	@$(CC) ./tests/viewer_tests.cc ./model/memento.cc ./model/obj_data.cc ./model/affine.cc $(CHECKFLAGS) -o Test
	@./Test
	@rm -rf *.o *.a Test

gcov_report: clean
	@$(CC) ./tests/viewer_tests.cc ./model/memento.cc ./model/obj_data.cc ./model/affine.cc -o Test $(GCOV) $(CHECKFLAGS)
	@./Test
	@lcov --no-external -c -d . -o SmartCalc_v2_0.info
	@genhtml -o $(REPORTDIR) SmartCalc_v2_0.info
	@$(OPEN) ./$(REPORTDIR)/index.html

check: style cppcheck leaks

style: 
	@cp ../linters/clang-format .
	clang-format -style=google -n */*.cc */*.h
	@rm clang-format

cppcheck:
	@cppcheck --language=c++ */*.cc */*.h

leaks: clean
	@$(CC) ./tests/viewer_tests.cc ./model/memento.cc ./model/obj_data.cc ./model/affine.cc $(CHECKFLAGS) -o Test
	@$(CHECK_LEAKS) ./Test $(FILTER)
	@rm -rf *.o *.a Test

clean:
	@rm -rf *.o *.a *.out *.txt *.gcno *.gch *.gcda *.info *.tgz $(REPORTDIR) Test $(BUILD_DIR) $(INSTALL_DIR) $(HOME)/settings_3dviewer.conf

open:
ifeq ($(OS), Linux)
	./$(INSTALL_DIR)/$(APP)
else
	open $(INSTALL_DIR)/$(APP).app
endif