你是用 PowerShell 重定向运行的：
[终端命令] .\Agnes.exe > test.ppm
在 Windows PowerShell 5.1 下，> 常会把输出按 Unicode 文本（UTF-16）写文件，导致 PPM 被污染。
你现在可以直接打开：

试打开 test_ascii.ppm（我已在仓库里生成）
以后建议这样生成（避免 UTF-16）：

用 cmd 的重定向（最稳）
cmd /c ".\out\build\vs2022\bin\Release\Agnes.exe > test.ppm"

或在 WSL 里运行并重定向。

test.ppm 被写成了 UTF-16 LE（文件头是 FF FE，并且字符间有 00）。
PPM（P3）查看器通常期望的是 ASCII/UTF-8 文本字节流。
所以在 Windows 下即使 IrfanView 也可能无法识别这个“被 UTF-16 化”的 PPM。


也就是本应该是ASCII码的文件
因为在powershell重用重定向命令，被写成utf-16格式
