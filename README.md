_This project has been created as part of the 42 curriculum by otahiri-._

## Description

Codexion is a concurrency simulation where multiple **coders** (threads) repeatedly go through stages (compile → debug → refactor) while competing for shared resources called **dongles** (two per coder, left/right).

The program prints timestamped logs and stops when either:
- all coders have completed the required number of compiles, or
- a coder **burns out** (does not compile within `time_to_burnout`).

Scheduling/fairness is configurable via `fifo` (first-in-first-out) or `edf` (earliest deadline first-style, based on the last compile time).

## Instructions

### Build

```sh
make
```

Useful targets:

```sh
make clean
make fclean
make re
```

### Run

```sh
./codexion <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>
```

- All times are in **milliseconds**.
- `<scheduler>` must be `fifo` or `edf`.

Example:

```sh
./codexion 5 800 200 200 200 3 50 fifo
```

Output format:

```text
<timestamp_ms_since_start> <coder_id> <event>
```

## Resources

### References

- `pthread_cond_wait`: https://www.ibm.com/docs/en/zos/3.2.0?topic=lf-pthread-cond-timedwait-pthread-cond-timedwait64-wait-condition-variable
- `pthread_cond_timedwait`: https://www.ibm.com/docs/en/zos/3.2.0?topic=lf-pthread-cond-timedwait-pthread-cond-timedwait64-wait-condition-variable
- `min-heap`: https://www.geeksforgeeks.org/dsa/introduction-to-min-heap-data-structure/

### AI usage (required)


- Used AI for: debugging deadlocks and helped in writing the readme file

## Blocking cases handled

This implementation explicitly addresses the common concurrency blocking scenarios:

1. **Deadlock while acquiring two resources**
   - Each coder requests both dongles and can only proceed when they are eligible to take *both* at once.
   - Eligibility is enforced by requiring the coder to be at the top of **both** dongles’ priority queues (min-heaps), preventing circular wait patterns.

2. **Starvation / unfair access to dongles**
   - Access is mediated by a per-dongle min-heap queue.
   - Policy depends on scheduler:
     - `fifo`: priority by request timestamp.
     - `edf`: priority by earliest last-compile time.

3. **Busy-wait avoidance while resources are unavailable**
   - If a dongle is in use (cooldown active), threads block on a condition variable (`pthread_cond_wait`) instead of spinning.
   - If dongles are free but not yet past their `next_available` timestamp (cooldown window), threads sleep using `pthread_cond_timedwait`.

4. **Clean shutdown while threads are blocked**
   - When the simulation ends (all done or burnout), a shared stop flag is activated and the monitor wakes sleepers and dongle-waiters via condition broadcasts.

5. **Log output interleaving**
   - Printing is serialized with a dedicated `write_lock` to avoid mixed/partial lines.

## Thread synchronization mechanisms

- **Threads**: `pthread_create`, `pthread_join`
  - One worker thread per coder (`run_stages`) + one monitor thread (`monitoring`).

- **Mutexes**: `pthread_mutex_t`
  - Per-coder mutex (`coder->lock`) protects shared fields like `last_compile` and `compiles_done`.
  - Per-dongle mutex (`dongle->lock`) protects dongle state (`cooldown`, `next_available`) and its heap.
  - Global output mutex (`input->write_lock`) serializes `printf`.

- **Condition variables**: `pthread_cond_t`
  - Per-dongle condition variable used to block waiting coders until a dongle becomes available.
  - Per-coder condition variable used by `ft_usleep()` via `pthread_cond_timedwait()` so sleeps can be interrupted during shutdown.

- **Priority queues (min-heaps)**
  - Each dongle maintains a heap of waiting coders; `peak()` selects the next eligible coder according to the chosen scheduler.

