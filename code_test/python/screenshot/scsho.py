import pyautogui as pag
 
# screen_shot = pyautogui.screenshot() 
#screen_shot = pyautogui.screenshot(region=(0, 0, 100, 200)) 
# screen_shot.save('test.png')

from time import sleep

# cd work_\code_test\python\screenshot 

i = 127
# savepath = 'C:/Users/my/Desktop/画像'
# savepath ='E:/Users/haori sayami\Videos/Captures/g'
# savepath ='E:/comic/X/X/'
# savepath ='E:/comic/OP/OP_'
# savepath ='E:/comic/H/Hunt'
# savepath ='E:/comic/REBORN'
# savepath ='E:/comic/HERO'
# savepath ='E:/comic/chain2/124/'
# savepath ='E:/comic/NARUTO/N/'
savepath ='E:/comic/DB/450/'
# savepath ='E:/comic/DEATH_NOTE/'
# savepath ='E:/comic/Oshi/O/'

try:
    while i<4000:
        sleep(2)
        pag.click(800, 30)
        # img = pag.screenshot(savepath + '/screenshot' + str(i) + '.png')
        # img = pag.screenshot(savepath + '/HUNTER_HUNTER_' + str(i) + '.png')
        # img = pag.screenshot(savepath + '/DEATH_NOTE' + str(i) + '.png')
        # img = pag.screenshot(savepath + '/ONE_PEACE' + str(i) + '.png')
        # img = pag.screenshot(savepath + '/Oshi_no_ko_' + str(i) + '.png')
        # img = pag.screenshot(savepath + '/NARUTO' + str(i) + '.png')
        # img = pag.screenshot(savepath + '/40_' + str(i) + '.png')
        img = pag.screenshot(savepath + '/468_' + str(i) + '.png')
        # img = pag.screenshot(savepath + '/136_' + str(i) + '.png')
        # img = pag.screenshot(savepath + '/123_' + str(i) + '.png')
        sleep(3)
        pag.click(30, 30)
        i = i + 1
except KeyboardInterrupt:
    print('\n')