import pyautogui as pag

from time import sleep

i = 1

try:
    while i<4000:
        # sleep(30)
        pag.click(1900, 1000)
        sleep(30)
        # pag.click(30, 30)
        i = i + 1
except KeyboardInterrupt:
    print('\n')