import pyautogui as pag
 
# screen_shot = pyautogui.screenshot() 
#screen_shot = pyautogui.screenshot(region=(0, 0, 100, 200)) 
# screen_shot.save('test.png')

from time import sleep

i = 133
# savepath = 'C:/Users/my/Desktop/画像'
# savepath ='E:/Users/haori sayami\Videos/Captures/g'
# savepath ='E:/comic/X/test'
savepath ='E:/comic/OP/OP'
# savepath ='E:/comic/H/Hunt'
# savepath ='E:/comic/REBORN'
# savepath ='E:/comic/HERO'
# savepath ='E:/comic/NARUTO/'
# savepath ='E:/comic/DEATH_NOTE/'

try:
    while i<1300:
        sleep(2)
        pag.click(800, 30)
        # img = pag.screenshot(savepath + '/screenshot' + str(i) + '.png')
        # img = pag.screenshot(savepath + '/Choujin_X_' + str(i) + '.png')
        # img = pag.screenshot(savepath + '/HUNTER_HUNTER_' + str(i) + '.png')
        # img = pag.screenshot(savepath + '/DEATH_NOTE' + str(i) + '.png')
        img = pag.screenshot(savepath + '/ONE_PEACE' + str(i) + '.png')
        sleep(3)
        pag.click(30, 30)
        i = i + 1
except KeyboardInterrupt:
    print('\n')