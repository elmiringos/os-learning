# Homework: Process Scheduler Questions

## 1.

**Question:**
Run `process-run.py` with the following flags: `-l 5:100,5:100`. What should the CPU utilization be (percent of time the CPU is in use)? Why do you know this? Use the `-c` and `-p` flags to check your answer.

**Answer:**

- **Processes**
  - Each process has 5 instructions (`5:100`) and 100% of them are CPU instructions.  
  - There are **no I/O instructions**.  
  - Two such processes are running concurrently.

- **CPU usage**  
  - Since all instructions require the CPU, the CPU will always have a process to execute.  
  - There is no waiting for I/O, so the CPU never idles during the simulation.

- **Expected result**  
  - **CPU utilization = 100%**  
  - **I/O utilization = 0%** (no I/O issued)  

- **Verification**  
  Running:
  ```bash
  ./process-run.py -l 5:100,5:100 -c -p
  ```

## 2.

**Question**
Now run with these flags: `-l 4:100,1:0`. These flags specify one process with 4 instructions (all to use the
CPU), and one that simply issues an I/O and waits for it to be done. How long does it take to complete both processes? Use `-c` and `-p` to find out if you were right.

**Answer**

- **Processes:
  - First process have four CPU boud tasks.
  - Second process have only one IO task.

  **Expcted Resut:
  - Total: 10
  - CPU: 50 %
  - IO: 40 %

## 3.

**Question**
Switch the order of the processes: `-l 1:0,4:100`. What happens now? Does switching the order matter? Why? (As always, use `-c` and `-p` to see if you were right)

**Answer**

- No, the order does not matter because the scheduler only switches when a process finishes all its instructions (`SWITCH_ON_END`).
- As a result, the first process runs to completion before the second process starts, so CPU and I/O utilization are the same regardless of process order.

## 4

**Question**
We'll now explore some of the other flags. One important flag is `-S`, which determines how the system reacts when a process issues an I/O. With the flag set to SWITCH ON END, the system will NOT switch to another process while one is doing I/O, instead waiting until the process is completely finished. What happens when you run the following two processes (`-l 1:0,4:100 -c -S SWITCH_ON_END`), one doing I/O and the other doing CPU work?


**Answer**
- With `SWITCH_ON_END`, the scheduler only switches when a process finishes all instructions.
- Even if the first process is I/O-bound, the CPU-bound process waits until the first finishes.
- CPU and I/O utilization remain the same as in the previous runs.

## 5

**Question**
Now, run the same processes, but with the switching behavior set to switch to another process whenever one is WAITING for I/O (`-l 1:0,4:100 -c -S SWITCH_ON_IO`). What happens now? Use `-c` and `-p` to confirm that you are right.

** Answer**
- With `SWITCH_ON_IO`, the scheduler immediately switches to a ready process whenever the current process issues I/O.  
- Process 0 starts its I/O instruction and enters WAITING.  
- Process 1 (CPU-bound) runs immediately while I/O completes.  
- This leads to better CPU and I/O overlap.

**Simulation results:**
- Total time: 6 ticks
- CPU busy: 5 ticks
- I/O busy: 4 ticks
