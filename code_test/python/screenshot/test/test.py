import sys
import pytesseract
from PIL import Image

def image_to_text(image_path):
    # 画像を読み込む
    img = Image.open(image_path)

    pytesseract.pytesseract.tesseract_cmd = r'C:\Program Files\Tesseract-OCR\tesseract.exe'

    # TesseractでOCRを実行
    text = pytesseract.image_to_string(img, lang='jpn')

    return text

if __name__ == "__main__":
    if len(sys.argv) > 1:
        image_path = sys.argv[1]  # コマンドライン引数から画像ファイルのパスを取得
        text = image_to_text(image_path)
        print(text)
    else:
        print("Usage: python app.py <path_to_image>")