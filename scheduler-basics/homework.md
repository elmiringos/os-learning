## 1
1) For ./scheduler.py -p FIFO -j 3 -s 200 -c
ARG policy FIFO
ARG jobs 3
ARG maxlen 10
ARG seed 200

Here is the job list, with the run time of each job:
  Job 0 ( length = 1 )
  Job 1 ( length = 3 )
  Job 2 ( length = 8 )


Turnaround time = (1 + 4 + 12) / 3 = 5.67
Response time = (0 + 1 + 4) / 3 = 1.67


2) For SJF it would be the same cause jobs are generated in asc order always

## 2
1) For ./scheduler.py -p FIFO -j 3 -l 100,200,300 -c
ARG policy FIFO
ARG jlist 100,200,300

Here is the job list, with the run time of each job:
  Job 0 ( length = 100.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 300.0 )

Turaround time = (100 + 300 + 600) / 3 = 333.33
Response time  = (0 + 100 + 300) / 3 = 133.33

2) For SJF it would be the same as case jobs are generated in asc order always

## 3
For ./scheduler.py -p RR -j 3 -l 100,200,300 -q 1
ARG policy RR
ARG jlist 100,200,300

Here is the job list, with the run time of each job:
  Job 0 ( length = 100.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 300.0 )


Turaround time = (298 + 499 + 600) / 3 = 465.67
Response time  = (0 + 1 + 2) / 3 = 3

## 4
All jobs have equal lengths. Jobs arrive in asceding order of lenght.

## 5
All jobs arrive at the same time. The RR quantum is at least large as the lenght of each job.

## 6
In SJF with job length inceasing reponse would be also increase. To demonstrate this we can define 3 jobs in simulator with particular lengths (10, 20, 30) and just incease last value in other invocations.

## 7
As quantum lengths increase in RR the response will also increase. Cause quantum time is basically time that piece of one job will be processed.

`
\[
R_\text{max} = \sum_{i=1}^{N-1} \min(L_i, Q)
\]
`

Where Q - quantum, Li - lenght of i job
