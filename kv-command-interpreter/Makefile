# run with 'make -i'
# Note: the large spaces are tabs, this is important
# Run GCOV, requires that we build the code
# All of these runs of ./prog are a test case
# We want to cover 100% of prog through these tests
run-tests-coverage: build
	./prog
	./prog test1.txt output1.txt
	./prog test2.txt output2.txt
	gcov prog-prog.gcno

# Run Valgrind to find memory leaks, requires that we build the code
run-tests-leak: build
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./prog test1.txt valgrind-output.txt
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./prog test2.txt valgrind-output2.txt

# Compile the code, requires that we clean up some files first.
# Add -lm if your code needs the math library.
build: clean
	g++ -fprofile-arcs -ftest-coverage -g prog.cpp -o prog

clean:
	rm -f *~
	rm -f prog
	rm -f *.gcda *.gcno *.gcov