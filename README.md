# CS 320 Project 1
## Ethan Elliott - Binghamton University

This project is a branch prediction simulator. The predictor reads a text file as a command line argument and returns the results on the command line as well as in a text file "output.txt."

### Prerequisites
To run the program with the included Makefile:

To run with the included test file:
```
make run
```
To compile without running:
```
make compile
```
To run after compiling with any test file:
```
./predictor file.txt
```

### Predictors
* Take all branches
* Not take all branches
* Bimodal with single history bit
* Bimodal with table and saturating 2-bit history
* GShare
* Tournament (GShare and bimodal saturating)

Each line in output represents the respective predictor results.
