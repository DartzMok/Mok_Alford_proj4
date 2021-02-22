compile: proj4.out

proj4.out: proj4.c
	gcc -g -Wall -pedantic-errors proj4.c -o proj4.out

run: proj4.out
	./proj4.out input1.txt input2.txt; cat differencesFoundInFile1.txt differencesFoundInFile2.txt;

clean:
	rm proj4.out

