# 🔗 Pipex  

**Pipex** is a 42 project that recreates the behavior of shell pipelines (`|`). It executes multiple commands with input/output redirection using Unix system calls like `pipe()`, `fork()`, `execve()`, and `dup2()`.  

---

## ❓ Why Use `pipe` in Pipex?  

The `pipe` system call allows **inter-process communication (IPC)** by creating a unidirectional data channel. One process writes to the pipe, while another reads from it.  

### 🔍 Example:  
```bash
ls -l | wc -l
