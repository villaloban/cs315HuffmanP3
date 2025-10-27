Student Info: Name: Anthony Villalobos Student ID: 008394627 Repo Link: https://github.com/villaloban/cs315HuffmanP3.git

Collaboration & Sources: During this project I had trouble with the encode section and had trouble understanding exactly what needed to be done for it I asked Liam about it and he explained it to me in simple terms. During this project I also found that looking at string functions were really helpful since it made some thing easier by already having a function I could use. The ide also helped by having me emplace, size_t and auto for many things that were giving me warnings and errors. Also durring the testing phase I collaberated with liam on how to fix the issue and also asked ai why I was getting this error. Turns out the way it was reading the file wasn't correctt so I had to make a new path dirrection with the dirName and the inputfilename. I also asked ai how to fix the spacing issue I was having since I had forgotten about setw. 

Implementation & Details: In this phase of the project we worked on building the huffman tree, writting a header and code file and also finalizing our main. The buildFromCounts function is what builds the huffman tree and takes a word and its frequencey and makes tree nodes for them and takes the smallest of the two and then keeps that on until we get one final node. AssignCodeDFS takes a depth first search approach to assignning huffman codes. When going left it adds 0 and when going right it adds 1 and saves the code until it reaches a leaf node. The writeHeaderPreorder is similar to the function before but instead it is a pre order traversal and writes it to an ouput stream instead of using a vector. The encode function takes the tokens and convertes them to their huffman code and writes it to the ouput stream and wrap lines to wrap col usually 80 for readability sake. 

Testing & Status: Input; For the testing in this project we had to run it a little differently to where you dont have the path of the file and your main pre appends the path so all you have to do is add the file name. In this final phase of the project we are looking for any differences in our files against the reference files and should have a header, code, tokens, and freq file that will be created after running the program and giving it a txt file. When running the command _bash ./compile_and_test_project3_final_version.bash_ we see each txt file that we have get compared with their reference file and if tell us if they match and if they dont the unmatching lines will be printed on the terminal. An example would look like
**/
==> Running: p3_complete.x on TheBells.txt
BST height: 12
BST unique words: 49
Total tokens: 83
Min frequency: 1
Max frequency: 11
Comparing: input_output/TheBells.tokens  and  /home/faculty/kooshesh/cs315_fall2025/project3/final_version/tokens/TheBells.tokens
tokens matches
Comparing: input_output/TheBells.freq  and  /home/faculty/kooshesh/cs315_fall2025/project3/final_version/freq/TheBells.freq
freq matches
Comparing: input_output/TheBells.code  and  /home/faculty/kooshesh/cs315_fall2025/project3/final_version/code/TheBells.code
code matches
Comparing: input_output/TheBells.hdr  and  /home/faculty/kooshesh/cs315_fall2025/project3/final_version/hdr/TheBells.hdr
hdr matches

Summary: 44 match(es), 0 diff(s)
\**

Tokens File:
edgar
allan
poe
s
the
bells
hear
the
sledges
with
the
...


Header File:
seem 000000
s 000001
runic 000010
rhyme 000011
of 0001
poe 001000
oversprinkle 001001
night 001010
musically 001011
merriment 001100
melody 001101
keeping 001110
jingling 001111
in 01000
...


Freq File:
        11 bells
        11 the
         4 of
         3 a
         3 time
         3 tinkle
         2 from
         2 in
         2 that
         2 to
         2 with


Code File:
01100101110100100000000110010101010110011111101101101001011111111101111000011010
11011100001001100111101000110101100001001111101111100011000110000100010001001001
11110001001010110111110011110111111000010010111101000101000000001110011110100110
11011010011011011010001110110011100111001010001101011111000001000010000011111001
10011101011111001111101001011111000101011100101101101101101101101010111000011110
1110010011101100001100101

Error's I did recieve while testing had to do a good amount with the way I used for loops. For every for loop I had I would get a warning sign and had to change it to size_t or went with the compilers recomendation and used auto. I also had to implement the pre appending of the file in my main since before implementing that the files weren't being found. I also had an error with having my matches not found and had 33 matches and 11 differences but the reason being was spacing issues. I fixed this using setw which set the with so the file would match. 
