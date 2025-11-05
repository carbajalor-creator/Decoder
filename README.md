# Decoder
Project 4 Decoding a Huffman Tree
Gabriela Carbajal Ortiz 
007715715
https://github.com/carbajalor-creator/Decoder.git


Collaboration & Sources
For this project I had to use a lot of outside sources to figure out how to set up the command line arguments and to read, write to, and create a file. I used AI to help figure out where my errors were coming from and what the errors I was encountering meant. The rest of the code and implementation was my own work.

Implementation Details
In this project I made a few extra helper functions to break things down a little. I have a headerVector function that read in the header file and made each word and code a pair and inserted that into hdrVector. I also made an treeInsert function that reads through the codes for each word and creates the tree branches and nodes to put the word to the leaf it belongs to. Then I had my buildFromHeader function iterate through hdrVector and call the treeInsert function to create the tree. I had another function called readCodes that just reads in the code file and stores the bits in a string called bits. This was then called in my decoding function that itertated through the string and once it reached a leaf it would insert the word into a vector called result. Then that vector would be iterated through in my writeToOutputFile function to output the words in correct order.

Testing & Status
I tested my functions individually and had multiple print statements throughout just to make sure my vectors and strings matched with what the input files had. I had a small issue with my decoding function because it would skip a few words but after a small adjustment I was able to get that to work and output correctly. I tested with the input files provided and my tokens decoded file matched with the tokens file provided. 
