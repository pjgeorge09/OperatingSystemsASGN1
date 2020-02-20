So for Kirk, Spock, if you kill spock and run words with kirk, it places the words into a queue.
Starting spock again will empty the queue one at a time.

For K/S, if you kill kirk, spock just listens.


For 2 kirks, it simply puts them into the queue into the order written. So A B C from K1 K2 K1
in that order will print out from spock in A B C.

For 2 spocks, or more, it will pop the top of the queue in order, so the first spock will get
the first thing put into the list. If you do 1 2 3 4 5 6 7 8 9 10, spock 1 will get all odds 
and print them out. Spock 2 will get all evens and print them out.
This is because the spock that printed goes back to waiting position behind any current spocks.

