@echo off
REM 设置当前目录为仓库路径
cd /d "C:\Users\liyj\Desktop\Algorithm"

REM 获取当前日期
for /f "tokens=2 delims==" %%I in ('"wmic os get localdatetime /value | findstr LocalDateTime"') do set datetime=%%I
set date=%datetime:~0,4%-%datetime:~4,2%-%datetime:~6,2%

REM 添加文件到暂存区
git add .

REM 提交更改，附加日期信息
git commit -m "update %date%"

REM 推送到远程仓库
git push origin main

REM 提示完成
echo.
echo Push complete!
pause