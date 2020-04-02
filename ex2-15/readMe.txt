自定要複製的來源與目的txt檔(不要留空白)
編譯完後 產生執行檔 filecopy後須接兩個argv （先來源後目的）
example
command line:./filecopy source.txt destination.txt


完整step:

1.先下command: （目的：使得該filecopy.exe之trace的結果輸出到txt檔）
sudo dtruss -n filecopy &> dtraceData.txt

2.之後另開啟新的terminal,再下 （目的 執行exe檔 並指定兩個txt）
./filecopy source.txt destination.txt

3.檢視dtraceData.txt即可觀看dtrace之output結果




