import time

init = 0.0
end = 0.0
used_time = 0.0

for i in range(0, 3):
    init = time.perf_counter()
    for j in range(0, 3000000000):
        pass
    end = time.perf_counter()
    print(f"#{i+1} run: {end - init}")
    used_time += end - init

used_time /= 3
print(f"Execution time (~average): {used_time}")

# Average execution time on 3 runs: 158.03950410466678 seconds.