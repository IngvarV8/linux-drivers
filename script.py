def func():
    driver_handle = open("/proc/ingvdr")
    msg = driver_handle.readline()
    print(msg)
    driver_handle.close()

func()