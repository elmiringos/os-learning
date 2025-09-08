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

**Answer**
- With `SWITCH_ON_IO`, the scheduler immediately switches to a ready process whenever the current process issues I/O.
- Process 0 starts its I/O instruction and enters WAITING.
- Process 1 (CPU-bound) runs immediately while I/O completes.
- This leads to better CPU and I/O overlap.

**Simulation results:**
- Total time: 6 ticks
- CPU busy: 5 ticks
- I/O busy: 4 ticks


## 6

**Question**
One other important behavior is what to do when an I/O completes. With `-I IO RUN LATER`, when an I/O completes, the process that issued it is not necessarily run right away; rather, whatever was running at the time keeps running. What happens when you run this combination of processes? (`./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH ON IO -c -p -I IO_RUN_LATER`) Are system resources being effectively utilized?

**Answer**
- With `IO_RUN_LATER`, when PID 0's I/O completes, it does not immediately resume, the currently running CPU-bound process keeps using the CPU.
- The system resources are not being used as effectively as they could be (some I/O completion time is wasted waiting for CPU bursts to end).


## 7

**Question**
Now run the same processes, but with `-I IO_RUN_IMMEDIATE` set, which immediately runs the process that issued the I/O. How does this behavior differ? Why might running a process that just completed an I/O again be a good idea?

**Answer**
- With `IO_RUN_IMMEDIATE`, when PID 0’s I/O completes, it is scheduled to run immediately, instead of waiting for the currently running CPU-bound process to finish.
- This avoids unnecessary delays for I/O-bound processes and improves overall overlap of CPU and I/O activity.
- Running the I/O process right away is a good idea because I/O-bound processes often issue more I/O requests; letting them run quickly keeps both CPU and I/O devices busy, leading to more efficient system utilization.
- However, this approach may not be suitable when there are many I/O-bound processes, as frequent preemptions could increase context-switching overhead and reduce CPU throughput.


## 8

**Question**
Now run with some randomly generated processes using flags `-s 1 -l 3:50,3:50` or `-s 2 -l 3:50,3:50` or `-s 3 -l 3:50,3:50`. See if you can predict how the trace will turn out. What happens when you use the flag `-I IO_RUN_IMMEDIATE` versus that flag `-I IO_RUN_LATER`? What happens when you use the flag `-S SWITCH_ON_IO` versus `-S SWITCH_ON_END`?


**Using**
```./process-run.py -s 1 -l 3:50,3:50 -c -p -I IO_RUN_IMMEDIATE -S SWITCH_ON_IO```


**Answer:**

- With two mixed CPU/I/O processes, the `-I` flag controls whether a process that completes I/O runs immediately or has to wait.
  - With `IO_RUN_IMMEDIATE`, the process resumes right away, which improves overlap of CPU and I/O work.
  - With `IO_RUN_LATER`, the process waits until the current CPU task finishes, which can reduce efficiency.

- The `-S` flag controls when the scheduler switches on I/O:
  - With `SWITCH_ON_IO`, the CPU immediately switches to another process when one issues I/O, keeping the CPU busy.
  - With `SWITCH_ON_END`, the CPU continues running the current process until it completes, which may cause poorer CPU/I/O utilization overall.

- In short: using `IO_RUN_IMMEDIATE` together with `SWITCH_ON_IO` gives the best resource utilization, while `IO_RUN_LATER` combined with `SWITCH_ON_END` results in more idle time and less efficient overlapof CPU and I/O in this scenario.

