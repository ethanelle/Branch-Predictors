compile: predictors.cpp compare.cpp
	g++ predictors.cpp -o predictor
	g++ compare.cpp -o compare

run: compile
	./predictor example_trace.txt

clean:
	rm -rf predictor
	rm -rf compare
	rm -rf output.txt
