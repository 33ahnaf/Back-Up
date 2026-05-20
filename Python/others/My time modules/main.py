import time

# 1 year = 31536000 seconds
# 1 month = 2592000 seconds
# 1 day = 86400 seconds
# 1 hour = 3600 seconds
# 1 minute = 60 seconds
# 1 second = 1 seconds

# epoch time when I was born -> 1275825600
epoch_time_of_my_birth_moment = 1275825600

def show_time_in_YMDHMS_format(epoch_time):
    years = int(epoch_time/31536000)
    remaining_seconds = epoch_time%31536000

    months = int(remaining_seconds/2592000)
    remaining_seconds %= 2592000

    days = int(remaining_seconds/86400)
    remaining_seconds %= 86400

    hours = int(remaining_seconds/3600)
    remaining_seconds %= 3600

    minutes = int(remaining_seconds/60)
    remaining_seconds %= 60

    seconds = int(remaining_seconds)

    print(f"{years} years - {months} months - {days} days - {hours} hours - {minutes} minutes - {seconds} seconds")


def count_time(epoch_time):
    while True:
        show_time_in_YMDHMS_format((time.time()) - epoch_time)
        time.sleep(0.01)


count_time(epoch_time_of_my_birth_moment)