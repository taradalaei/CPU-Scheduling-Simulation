# CPU Scheduling Simulation

This project implements and evaluates three classic CPU scheduling algorithms as part of an Operating Systems course project.

## ✅ Algorithms Implemented

1. **FCFS (First Come First Serve)**
2. **SJF (Shortest Job First - Non-Preemptive)**
3. **Round Robin (RR)**

Each algorithm calculates the following metrics:
- Average **Turnaround Time**
- Average **Waiting Time**
- Average **Response Time**

---

## 🧠 Algorithm Descriptions & Implementation Notes

### 1. FCFS (First Come First Serve)

- **Concept**: Processes are executed in the order of their arrival time.
- **Behavior**: Non-preemptive; each process runs to completion.
- **Implementation**:
  - Sort/iterate processes by `arrivalTime`.
  - If CPU is idle (`time < arrivalTime`), fast-forward time.
  - Compute:
    - `startTime = current time`
    - `completionTime = startTime + burstTime`
  - Calculate metrics from these timestamps.

### 2. SJF (Shortest Job First - Non-Preemptive)

- **Concept**: Among the ready processes, choose the one with the shortest burst time.
- **Behavior**: Non-preemptive; once started, runs to completion.
- **Implementation**:
  - At each moment, scan all arrived processes (`arrivalTime <= time`) not yet executed.
  - Select the one with the minimum `burstTime`.
  - Mark it as visited and execute like FCFS.
  - Requires handling idle time if no process is ready.

### 3. Round Robin (RR)

- **Concept**: Each process gets a fixed time slice (`quantum`) in cyclic order.
- **Behavior**: Preemptive; context switching occurs when quantum expires.
- **Implementation**:
  - Use a queue to manage the ready processes.
  - At each step:
    - Execute the front process up to `quantum` or its `remainingTime`.
    - If not finished, enqueue it again.
    - Track `startTime` on first execution only.
    - Track `remainingTime` and `completionTime`.
  - Add newly arrived processes to the queue dynamically.

---

## 📁 File Structure

```

.
├── scheduler.h         # Struct definitions and function declarations

├── scheduler.c         # Implementation of scheduling algorithms

├── scheduler\_test.c    # Comprehensive test cases with assertions

├── Makefile            # Build script to compile and run tests

└── README.md           # This documentation file

````

---

## 🧪 How to Build and Run

### 🔧 Build:

In a Linux/WSL terminal, navigate to the project folder and run:

```bash
make        # Compiles the project
````

This generates an executable named `scheduler_test`.

### ▶️ Run Tests:

```bash
make run    # Executes all test cases
```

If implemented correctly, you will see output like:

```
==== Test Case 1 ====
FCFS: Calculated: Turnaround: 15.00, Waiting: 7.33, Response: 7.33
      Expected:   Turnaround: 15.00, Waiting: 7.33, Response: 7.33
>>> Test Case 1 PASSED.
...
ALL TESTS PASSED.
```

### 🧹 Clean Build Files:

```bash
make clean
```

---

## 📥 Input Format

All input processes are hardcoded inside `scheduler_test.c` for testing purposes.
Each process is defined using the `Process` struct:

```c
Process test1[3] = {
    {1, 0, 10, 0, 0, 0},  // pid, arrivalTime, burstTime, remainingTime, startTime, completionTime
    {2, 1,  5, 0, 0, 0},
    {3, 2,  8, 0, 0, 0}
};
```

### Fields in `Process`:

| Field            | Description                         |
| ---------------- | ----------------------------------- |
| `pid`            | Process ID                          |
| `arrivalTime`    | Time process enters ready queue     |
| `burstTime`      | CPU time required                   |
| `remainingTime`  | Used for Round Robin scheduling     |
| `startTime`      | Time process first starts execution |
| `completionTime` | Time when execution is completed    |

---

## 📤 Output Format

For each test case, results for FCFS, SJF, and RR (with given quantum) are printed and validated:

```
==== Test Case X ====
FCFS: Calculated: Turnaround: X.XX, Waiting: Y.YY, Response: Z.ZZ
      Expected:   Turnaround: X.XX, Waiting: Y.YY, Response: Z.ZZ
>>> Test Case X PASSED.
```

If all metrics match the expected values (within a tolerance), the test is passed.
At the end:

```
ALL TESTS PASSED.
```

will be shown if everything is correct.

---

## 📌 Notes

* All algorithms are implemented in standard **C99**
* The code is cross-platform but designed to run in Unix-like environments (Linux, macOS, WSL)
* Round Robin uses time slicing (`timeQuantum` parameter)
* Time metrics are calculated as:

  * **Turnaround** = `completionTime - arrivalTime`
  * **Waiting** = `turnaround - burstTime`
  * **Response** = `startTime - arrivalTime`

---

## 🔗 GitHub Repository

```
https://github.com/taradalaei/CPU_Scheduling_Simulation
```

---

## 📅 Course Info

* **Course**: Operating Systems – Spring 1404
