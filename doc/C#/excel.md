# excel操作

## 罫線
```C#
//罫線を引くための型を宣言
Excel.Borders borders;
Excel.Border border;

//セルの範囲設定
range1 = (Microsoft.Office.Interop.Excel.Range)xlSheet.Cells[10 1];
range2 = (Microsoft.Office.Interop.Excel.Range)xlSheet.Cells[10 14];
range = xlSheet.get_Range(range1, range2);

//罫線設定
borders = range.Borders;

//左に罫線を引く
border = borders[Excel.XlBordersIndex.xlEdgeLeft];
border.LineStyle = Excel.XlLineStyle.xlContinuous;

//右に罫線を引く
border = borders[Excel.XlBordersIndex.xlEdgeRight];
border.LineStyle = Excel.XlLineStyle.xlContinuous;

//上に罫線を引く
border = borders[Excel.XlBordersIndex.xlEdgeTop];
border.LineStyle = Excel.XlLineStyle.xlContinuous;

//下に罫線を引く
border = borders[Excel.XlBordersIndex.xlEdgeBottom];
border.LineStyle = Excel.XlLineStyle.xlContinuous;
```

REFERENCE  
http://1t1.info/2021/02/c%E3%81%A7excel%E6%93%8D%E4%BD%9C%E3%81%99%E3%82%8B%E3%80%80%E7%BD%AB%E7%B7%9A%E3%82%92%E5%BC%95%E3%81%8F%E3%81%AB%E3%81%AF/  
https://hironimo.com/prog/c-sharp/c-excel-line/


# NPOI
NPOIとは
Officeのドキュメントの操作を行う事が出来るApache POI(Javaライブラリ)の.NET用に移植されたライブラリです。C#やVB.netでOfficeのドキュメントを作成・編集する事が出来ます。また、LicenceはApache 2.0です。

Apache POIとは、JavaプログラムからMicrosoft Officeのファイル形式で文書の読み書きが行えるようにするライブラリ。  


JAVA Apache POI の使用例
```JAVA
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
 
import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.ss.usermodel.Sheet;
import org.apache.poi.ss.usermodel.Workbook;
import org.apache.poi.ss.usermodel.WorkbookFactory;
 
public class PoiSample {
 
  public static void main(String[] args) {
 
    InputStream is = null;
    Workbook wb = null;
    FileOutputStream out = null;
 
    try {
      //Excelファイル読込
      is = new FileInputStream("C:¥¥temp¥¥sample.xlsx");
      wb = WorkbookFactory.create(is);
 
      //コピー元セル(A1)を取得する
      Sheet sh = wb.getSheetAt(0);  //1番目のシートを読み込む
      Row row = sh.getRow(0);       //1行目を読み込む
      Cell cell = row.getCell(0);   //1セル目を読み込む
 
      //コピー先セル(C1)にセルをコピーする
      Cell cell2    = row.createCell(2);        //セルを作成する
      cell2.setCellStyle(cell.getCellStyle());  //コピー元セルのスタイルをセットする
      cell2.setCellValue(cell.getStringCellValue());  //コピー元セルの値をセットする（型を意識したgetメソッドを使用してください）
 
      //Excelファイル出力
      out = new FileOutputStream("C:¥¥temp¥¥sample.xlsx");
      wb.write(out);
 
    } catch (Exception ex) {
      ex.printStackTrace();
 
    } finally {
      try {
        wb.close();
        out.close();
      } catch (Exception ex2) {
        ex2.printStackTrace();
      }
    }
  }
}
```
備考  
セルのコピーは、スタイルと値を別々にセットする必要があります。  
.xlsx形式、.xls形式どちらのExcelにも対応します。

同じような感じでNPOIを使用できる

REFERENCE  
https://qiita.com/y012/items/3a2d0fc98bb40dccd457  
https://blog.java-reference.com/poi-copy-cell/  
【C#】NPOIを使ってExcelファイルを作成・編集する  
https://qiita.com/hukatama024e/items/37427f2578a8987645dd  
poiでCreateCellStyleを連発するのは辞めた方が良い話  
https://qiita.com/Ky01_dev/items/efeca05faaf08bd4fd41