#include "scheduler.h"
#include <stdlib.h>
#include <limits.h>

// Helper function to copy processes and reset remaining/start/completion times
void reset_processes(Process dest[], Process src[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
        dest[i].remainingTime = dest[i].burstTime;
        dest[i].startTime = -1;
        dest[i].completionTime = 0;
    }
}

Metrics fcfs_metrics(Process proc[], int n) {
    Process temp[n];
    reset_processes(temp, proc, n);

    int time = 0;
    float totalTurnaround = 0, totalWaiting = 0, totalResponse = 0;

    for (int i = 0; i < n; i++) {
        if (time < temp[i].arrivalTime)
            time = temp[i].arrivalTime;

        temp[i].startTime = time;
        temp[i].completionTime = time + temp[i].burstTime;
        time = temp[i].completionTime;

        int turnaround = temp[i].completionTime - temp[i].arrivalTime;
        int waiting = turnaround - temp[i].burstTime;
        int response = temp[i].startTime - temp[i].arrivalTime;

        totalTurnaround += turnaround;
        totalWaiting += waiting;
        totalResponse += response;
    }

    Metrics m;
    m.avgTurnaround = totalTurnaround / n;
    m.avgWaiting = totalWaiting / n;
    m.avgResponse = totalResponse / n;
    return m;
}

Metrics sjf_metrics(Process proc[], int n) {
    Process temp[n];
    reset_processes(temp, proc, n);

    int time = 0, completed = 0;
    float totalTurnaround = 0, totalWaiting = 0, totalResponse = 0;
    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;

    while (completed < n) {
        int idx = -1;
        int minBurst = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && temp[i].arrivalTime <= time && temp[i].burstTime < minBurst) {
                minBurst = temp[i].burstTime;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        temp[idx].startTime = time;
        temp[idx].completionTime = time + temp[idx].burstTime;
        time = temp[idx].completionTime;
        visited[idx] = 1;
        completed++;

        int turnaround = temp[idx].completionTime - temp[idx].arrivalTime;
        int waiting = turnaround - temp[idx].burstTime;
        int response = temp[idx].startTime - temp[idx].arrivalTime;

        totalTurnaround += turnaround;
        totalWaiting += waiting;
        totalResponse += response;
    }

    Metrics m;
    m.avgTurnaround = totalTurnaround / n;
    m.avgWaiting = totalWaiting / n;
    m.avgResponse = totalResponse / n;
    return m;
}

Metrics rr_metrics(Process proc[], int n, int timeQuantum) {
    Process temp[n];
    reset_processes(temp, proc, n);

    int time = 0, completed = 0;
    float totalTurnaround = 0, totalWaiting = 0, totalResponse = 0;
    int queue[n * 100], front = 0, rear = 0, inQueue[n];
    for (int i = 0; i < n; i++) inQueue[i] = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (!inQueue[i] && temp[i].arrivalTime <= time && temp[i].remainingTime > 0) {
                queue[rear++] = i;
                inQueue[i] = 1;
            }
        }

        if (front == rear) {
            time++;
            continue;
        }

        int idx = queue[front++];
        if (temp[idx].startTime == -1)
            temp[idx].startTime = time;

        int execTime = temp[idx].remainingTime < timeQuantum ? temp[idx].remainingTime : timeQuantum;
        time += execTime;
        temp[idx].remainingTime -= execTime;

        for (int i = 0; i < n; i++) {
            if (!inQueue[i] && temp[i].arrivalTime <= time && temp[i].remainingTime > 0) {
                queue[rear++] = i;
                inQueue[i] = 1;
            }
        }

        if (temp[idx].remainingTime > 0) {
            queue[rear++] = idx;
        } else {
            temp[idx].completionTime = time;
            completed++;

            int turnaround = temp[idx].completionTime - temp[idx].arrivalTime;
            int waiting = turnaround - temp[idx].burstTime;
            int response = temp[idx].startTime - temp[idx].arrivalTime;

            totalTurnaround += turnaround;
            totalWaiting += waiting;
            totalResponse += response;
        }
    }

    Metrics m;
    m.avgTurnaround = totalTurnaround / n;
    m.avgWaiting = totalWaiting / n;
    m.avgResponse = totalResponse / n;
    return m;
}
