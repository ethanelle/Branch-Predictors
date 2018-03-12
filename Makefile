compile: predictors.cpp
	g++ predictors.cpp -o predictor

run: compile
	./predictor example_trace.txt

clean:
	rm -rf predictor
	rm -rf output.txt
