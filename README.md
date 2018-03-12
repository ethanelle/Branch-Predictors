# CS 320 Project 1

This project is a branch prediction simulator. The predictor reads a text file as a command line argument and returns the results on the command line as well as in a text file "output.txt."

**Note:** This project is for reference only. Any code used must be adequately acknowleged.

### Files
* Makefile : Self-explanatory, how to use it is described below in "Running the program"
* example_trace.txt : An included example trace to test the program, also a formatting guide if you wish to test your own traces.
* predictors.cpp : The actual program.

### Running the program
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
* Bimodal with table and 1-bit history
  * Table entries: 16, 32, 128, 256, 512, 1024, 2048
* Bimodal with table and saturating 2-bit history
  * Table entries: 16, 32, 128, 256, 512, 1024, 2048
* GShare with expanding global history register
  * Register size begins at 3 bits and expands by one each loop until 11 bits.
* Tournament (GShare and bimodal saturating)
  * GShare global history register set to 11 bits
  * Bimodal table set to 2048 entries

Each line in output represents the respective predictor results.

### References
* [Combining Branch Predictors](http://www.hpl.hp.com/techreports/Compaq-DEC/WRL-TN-36.pdf), Scott McFarling

