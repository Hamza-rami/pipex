📦 Pipex

Pipex is a 42 project that recreates the behavior of shell pipelines ( | ).
It executes multiple commands with input/output redirection using Unix system calls like pipe(), fork(), execve(), and dup2().

❓ Why Use pipe in Pipex?

The pipe system call allows inter-process communication (IPC) by creating a unidirectional data channel.
One process writes to the pipe, while another reads from it.

🔍 Example:
$ ls -l | wc -l

⚙️ Features
-----------
- Simulates Unix pipe behavior using pipe(), fork(), dup2(), and execve()
- Handles multiple commands
- Supports file redirection (infile, outfile)
- Built entirely in C
- Bonus: handles here_doc and additional pipes

📂 File Structure
------------------
mandatory/      -> Required part of the project  
bonus/          -> Bonus features (here_doc, more pipes)  
Makefile        -> Compile rules  

🛠️ How to Use
--------------
✅ Compile:
$ make

▶️ Run Pipex:
$ ./pipex infile "cmd1" "cmd2" outfile

📘 Example:
$ ./pipex input.txt "grep hello" "wc -l" output.txt

This is equivalent to:
$ < input.txt grep hello | wc -l > output.txt

🧪 Bonus Usage (if implemented)
-------------------------------
$ ./pipex here_doc LIMITER "cmd1" "cmd2" outfile

Behaves like:
$ << LIMITER cmd1 | cmd2 >> outfile

📚 Concepts Covered
--------------------
- pipe(), fork(), execve(), dup2()
- File descriptors and redirection
- Process creation and synchronization
- Argument parsing
- Error and memory management

👨‍💻 Author
------------
Hamza Rami  
Student at 1337 Khouribga
