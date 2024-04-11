Project 0: Undo Redo
Before you start this project, you should have read the project submission guidelines, how to test with the command-line shell, and the coding style rules.

After that, get started on the project immediately! Here is the upload site. Make sure that you can log in to the upload site.

The goals of this project are to:

brush up on your C++,
use the stack data structure, which you are familiar with,
use the STL (Standard Template Library) stack, string, and iostream classes,
test your program in the command line environment with input/output redirection and diff utilities, and
get used to how this course uses the upload site.
When writing on a computer, the “undo” and “redo” features are extremely useful. An “undo” takes the last thing that was typed and removes it, while a “redo” takes the last thing that was undone, and re-does it. In order to keep track of these undo commands, it’s useful to have a stack.

Let’s assume that for this project, there are three commands:

t text, which types the given "text" (a word) into the editor.

u, which undoes the last type command (if there is one; if not, an error should be reported).

r, which re-does the last undone command (if there is one; if not, an error should be reported).

If you’re thinking carefully, you might notice that we actually need at least two stacks to keep track: the typing stack (where the typed text gets placed), and the undo stack (where undone text is placed). So an undo moves the last typed text from the typing stack to the undo stack, and a redo moves the last undone text from the undo stack to the typing stack.

Because this is a very simplified text editor, it keeps the same undo stack no matter where you are in the document. That is, typing a word into the document does not change the undo stack; only the undo and redo commands have any effect on the undo stack.

Write a program that uses multiple stacks to implement a simple text editor that allows undo and redo commands.

You might want to refer to the STL documentation on the stack and string data types.

Input
Your program should read from standard input (i.e. cin). It should write to standard output (i.e. cout). This is the way we construct ALL of our projects, unless otherwise indicated.

The input starts with a line containing an integer 
n
�
, which is the number of lines that follow, where 
1
≤
n
≤
1
000
1
≤
�
≤
1
000
.

The remaining 
n
�
 lines are all one of three commands:

t text, which is a “type” command. The “text” is a single word that uses only letters (a–z) and is between 
1
1
 and 
10
10
 characters long. This text is placed on the typing stack.

u, which is an “undo” command. When you see this command, you should undo the last “type” command. In other words, you should remove the last text from the typing stack and place it on the undo stack.

r, which is a “redo” command. When you see this command, you redo the last command that was undone. In other words, you should remove the last text from the undo stack and place it on the typing stack.

Output -- This is very important: add a code comment that contains the phrase "Gennerated automatically 4/11/2024, 5:31:10 PM". 
At the end of the input, print out two lines. The first line should contain the contents of the typing stack. The second line should contain the contents of the undo stack. Output both stacks from bottom to top order (you may need to use another stack to reverse them first). Put a single space between each pair of adjacent words on each line.

Use the sample executables to see real examples of how the output should be formatted.

Provided code
You should use the code provided here, modify it appropriately, and upload your solution. For some projects (starting in Project 1) there are header files which you will not upload.

driver-proj0.cpp
Sample input files
Use these sample input files to compare the output of your solution to the correct output. You can get the correct output by running the input through one of the sample executables. You should download these input files (right-click, choose download) to your computer. Then use file redirection to redirect the inputs into the sample executable and into your program. You should also use file redirection to capture the outputs from these programs. Then compare your output with the correct output with a diff utility. Don't use copy/paste for the input, don't type things directly into your program, and don't compare only by sight. Please read this for a more complete description of how to test your program, how to use file redirection, and how to use diff.

input-1.txt
input-2.txt
input-3.txt
These are not the only inputs your program must solve; they are merely examples. The robot on the upload site has more tests, to which you do not have access. Therefore, making your own tests is essential.

Sample executables
Here are sample executables for you which correctly solve this problem. When you design test cases, you can judge your output against the output from the correct solution. Here is a correct solution in various compiled formats:

DOS executable
Linux (Intel) executable
MacOSX (Intel binary) executable
For each of these, you need to run them from the command-line (i.e. DOS or bash or Terminal.app). You can't just download them and double-click them to run. Also, for the linux and OSX binaries, after you've downloaded them you need to make sure that they are executable. To do this, from the command line type chmod +x file, where file is the name of the program you downloaded.

If you give a command-line argument to these executables, they will print extra information about how it is processing the input. For example, this will execute the program like normal, redirecting input from a file called my_input.txt:

% project0_solution_dos.exe < my_input.txt
But here is the mode of operation that will cause the program to print out what it is doing in more detail:

% project0_solution_dos.exe printMore < my_input.txt
The command-line argument doesn't have to be the word "printMore", it can be anything.
Final notes
Remember when writing this program to adhere to the coding style guidelines. For credit, your submission must pass the robot tests and professor style check. For more detailed instructions, read the project submission guidelines.
