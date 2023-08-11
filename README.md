# CPractice + Snowplow Driver Code  
### Summary
This is when I first *really* taught myself to program in C using the book "C Primer Plus" by Stephan Prata, 6th Edition. I literally went over almost every example and end-of-chapter exercise within the book, except for Chapter 17 - Advanced Data Representation. You can see this organization under the directory CPrimerPlusBook. In addition, I also used this repo, for whatever reason, to hold code I was writing (at around the same time) for the Autonomous Snowplow project I was a part of as a freshman. This was a robotics project for which I was project lead. My particular contribution to the development was writing code to obtain data from our VectorNAV IMU board, and attempting to obtain a decent position estimate of the robot purely from this IMU data (*I was absolutely **unsuccessful** at this, as you might see if you look at the Snowplow/VectorNAV/VectorNAV Driver/vntest.c file*).

### Intent
I intend to use this repo for any practice C code I do for generic, non-embedded applications. For one thing, I intend to finally return to Chapter 17 - Advanced Data Representation of the textbook I had used, and cover the material in there. I am actually already familiar with general data structure forms used in programming through my Computer Science II class at NDSU (*we had used Java instead*), but C is a different ball game, and also more directly applicable to embedded systems, which is what I work with.

### How To Build
i686-w64-mingw32-gcc -o name_of_file.exe name_of_file.c