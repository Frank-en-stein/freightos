Freightos Assignment By S. M. Faisal Rahman

Project Selected: 1
Why: Found it really intersting and just couldn't shake it off my head.

Why My Approach: I've analyzed the problem in as many ways as I can think of right now and couldn't theoritically think of anything better except some
				hardware upgrades.
	
Testinf scenarios: I've included the generator that I wrote to test my code. it's in python. Please check it out but DO NOT RUN unless you have 289GB disk
				space lying around in the same drive. tried to emulate a real scenario with it.

How to Run: It's pretty straight Forward. Use file_generator.py to generate 1 million docs. You can tune it down to 1000 or 5000 for reasonable tests.
			The rest of the .cpp files are part of the same code. The entry point is UniqueWord.cpp. Run it with GNU G++ with C++ 11 supported.
			
My Setup:
		Intel core i5 4772 4th gen, 8GB RAM,  7200RPM HDD, Windows 10, python3.5, Codeblocks(GNU GCC C++11)
		
Workflow:
	1. Assuming I only have to count valid english word, I wrote a file generator to generate 1 million files of 303kb summing up to 289GB.
	2. I've studied a few super efficient data structures to manage this massive data and found that Trie would be the bets option. This is 
		majorly because the whole dataset would be of range 10^20. So I cannot iterate over the dataset more than once.
	3. I've found that reading a file as a whole gives significant performance boost over buffered reads. That is what I've done making one file=one string.
	4. Tokenixing file appears to be too expensive. So, I wrote a custom Trie that takes a file as a string, iterrates over it only once and inserts new words
		into the trie while iterating that one time; basically an embodyment of trie insert and file tokenization. Gives noticable performance boost.
	5. Finally, i found that reading data from disk is going doubly faster than insertion into the trie. So, I implemented a Threaded Queue to use the producer
		consumer threading model. Also while I was at it, I made the trie thread safe to use threaded insertions.
	6. Estimated Test: for 10,000 files that is 28.896GB, the code ouputs in 36.533s. But this is the worst case I've found. It goes faster sometimes.
							So, estimated time for whole dataset = 3653.3s = 1 hrs

I Do know that it can be done faster than this. I'm gonna have to play around a little more and find out bottlenecks.
							
	
		