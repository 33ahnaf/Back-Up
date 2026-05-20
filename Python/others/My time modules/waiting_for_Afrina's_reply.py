import time

# 1 year = 31536000 seconds
# 1 month = 2592000 seconds
# 1 day = 86400 seconds
# 1 hour = 3600 seconds
# 1 minute = 60 seconds
# 1 second = 1 seconds

# epoch time when I was born -> 1275825600
epoch_time_when_Afrina_replyed = 1740560160

def show_time_in_YMDHMS_format(seconds):
    year = int(seconds/31536000)
    remaining_second = seconds%31536000

    month = int(remaining_second/2592000)
    remaining_second %= 2592000

    day = int(remaining_second/86400)
    remaining_second %= 86400

    hour = int(remaining_second/3600)
    remaining_second %= 3600

    minute = int(remaining_second/60)
    remaining_second %= 60

    second = int(remaining_second)

    print(f"{year} years - {month} months - {day} days - {hour} hours - {minute} minutes - {second} seconds")


def count_time(epoch_time):
    while True:
        show_time_in_YMDHMS_format((time.time())-epoch_time)
        time.sleep(0.01)


count_time(epoch_time_when_Afrina_replyed)