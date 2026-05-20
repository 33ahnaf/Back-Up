import time

initial_time = time.time()

for i in range(0, 1000000000):
    i+=1

terminal_time = time.time()

execution_time = terminal_time - initial_time

print(f"Time = {execution_time}")