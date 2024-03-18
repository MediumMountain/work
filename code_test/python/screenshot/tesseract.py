import tkinter as tk
from PIL import ImageTk # Tkinter用に画像変換
import pyautogui as gui # スクリーンショット
import pytesseract # 文字認識
import pyperclip # クリップボード


# ドラッグを開始した時の処理
def lbutton_down(event):
  global x1, y1
  x1, y1 = event.x, event.y
  # 前に描画した"rect"を削除
  canvas.delete("rect")
  # クリックした瞬間の小さい短形を描画
  canvas.create_rectangle(x1, y1, x1+1, y1+1, outline = "red", width = 2, tag="rect") 

# ドラッグしている時の処理
def drawing(event):
  global x2, y2
  x2 = event.x
  y2 = event.y
  # 座標の変更
  canvas.coords("rect", x1, y1, x2, y2)

# ドラッグを離した時の処理
def lbutton_up(event):
  global x1, y1, x2, y2
  # 始点、終点の反転に対応
  if x1 > x2:
    x1, x2 = x2, x1
  if y1 > y2:
    y1, y2 = y2, y1
  # オリジナルサイズの画像からトリミング
  screenshot_crop = screenshot.crop((x1*width_dif, y1*height_dif, x2*width_dif, y2*height_dif)) 


  pytesseract.pytesseract.tesseract_cmd = r'C:\Program Files\Tesseract-OCR\tesseract.exe'

  # 文字認識
  str = pytesseract.image_to_string(screenshot_crop, lang="jpn+jpn_vert")
  # クリップボードにコピー
  pyperclip.copy(str)
  # ウィンドウを閉じる
  root.destroy()


# 画面全体をスクリーンショット
screenshot = gui.screenshot()

# GUI
root = tk.Tk()
root.attributes('-fullscreen', True) # フルスクリーン
width = root.winfo_screenwidth()   # 画面の横幅
height = root.winfo_screenheight() # 画面の縦幅
# リサイズ
screenshot_resize = screenshot.resize((width, height))
# 元の画像が縮小サイズの何倍かを計算
width_dif = (screenshot_resize.width / width) + 1
height_dif = (screenshot_resize.height / height) + 1
# Tkinterで表示できるように変換
screenshot_tk = ImageTk.PhotoImage(screenshot_resize) 
# キャンバスの生成
canvas = tk.Canvas(root, width=screenshot_resize.width, height=screenshot_resize.height)
# キャンバスにイメージを表示
canvas.create_image(0, 0, image=screenshot_tk, anchor=tk.NW)
canvas.pack()

# イベントを設定
canvas.bind("<ButtonPress-1>", lbutton_down)
canvas.bind("<Button1-Motion>", drawing)
canvas.bind("<ButtonRelease-1>", lbutton_up)

root.mainloop()