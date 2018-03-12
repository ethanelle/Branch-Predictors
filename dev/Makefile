combine: clean_combine.cpp
	g++ clean_combine.cpp -o combine

run: combine
	./combine ../../traces/short_trace1.txt

run_long: combine
	./combine ../../traces/long_trace1.txt

clean:
	rm -rf combine
	rm -rf *.o
	rm -rf output.txt
