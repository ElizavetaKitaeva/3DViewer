DEBUG=-g
CC=gcc 
WFLAGS=-Wall -Wextra -Werror
COV=--coverage
LFLAGS=-c
LCHECK= `pkg-config --libs check`
BD = ../build/

all: build

build: clean mk replication
	cd $(BD); qmake 3D_Viewer.pro
	make -C $(BD)

replication: 
	cp 3D_Viewer.pro $(BD)
	cp -R Icons $(BD)
	cp Icons.qrc $(BD)
	cp -R Inter $(BD)
	cp -R Models $(BD)
	cp -R QtGifImage $(BD)
	cp -R 3rdParty $(BD)
	cp *.c *.h *.cpp *.ui $(BD)

dist: build
	cd $(BD);cd ..; tar -cvf 3D_Viewer.tar build 

install: build
	mkdir $(HOME)/Desktop/3D_Viewer/
	cp -rf $(BD)3D_Viewer.app $(HOME)/Desktop/3D_Viewer/
	make clean

uninstall:
	rm -rf $(HOME)/Desktop/3D_Viewer/

dvi: 
	open -a "Google Chrome" dvi.html

test:
	checkmk clean_mode=1 s21_test.check > s21_test.c
	$(CC) $(WFLAGS) --coverage s21_test.c fileReader.c affine.c -o test $(LCHECK)
	./test

gcov_report: clean test
	./test
	lcov -t "test" -c -d . -o test.info
	genhtml test.info -o report
	open -a "Safari" report/index.html

clean:
	rm -f *.a *.gcda *.gcno *.o *.info *.out *.gcov *.cfg ../.DS_Store 
	rm -f -r report *.dSYM
	rm -rf s21_test.c savedSettings.txt 3D_Viewer.pro.user
	rm -rf ../build-*
	rm -rf ./test && rm -rf ./gcov_report
	rm -rf $(BD)*
	rm -rf $(BD)

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

leaks: test
	CK_FORK=no leaks --atExit -- ./test

lint: clean
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extensions=c *.c
	rm -f CPPLINT.cfg

mk:
	mkdir ../build


.PHONY: cpp leaks lint mk gcov_report test dvi uninstall install dist replication build