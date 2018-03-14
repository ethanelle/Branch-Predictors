# CS 320 Project 1

This project is a branch prediction simulator. The predictor reads a text file as a command line argument and returns the results on the command line as well as in a text file "output.txt."

**Note:** This project is for reference only. Any code used must be adequately acknowleged.

### Files
* Makefile : Self-explanatory, how to use it is described below in "Running the program"
* example_trace.txt : An included example trace to test the program, also a formatting guide if you wish to test your own traces.
* predictors.cpp : The actual program.
* compare.cpp : A simple script to compare the output file to an answer key.

### Running the program
To run the program with the included Makefile:

To compile without running:
```
make
```
To run with the included test file:
```
make run
```
To run after compiling with any test file:
```
./predictor file.txt
```
To run the compare script after compiling and running:
```
./compare output.txt expected_output.txt
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

### Improvements Ahead
I had troubles with the tournament predictor giving me the wrong answer when using the gshare helper and bimodal saturating helper. However, I got it working by writing one (very large and very space-inefficient) function that does everything the tournament predictor needs. I think I will continue to look into this issue for a brief period of time before pushing this project to the back burner, so to speak.

### References
* [Combining Branch Predictors](http://www.hpl.hp.com/techreports/Compaq-DEC/WRL-TN-36.pdf), Scott McFarling

