@echo off
cd /d "C:\Users\liyj\Desktop\Algorithm"

for /f "tokens=2 delims==" %%I in ('"wmic os get localdatetime /value | findstr LocalDateTime"') do set datetime=%%I
set date=%datetime:~0,4%-%datetime:~4,2%-%datetime:~6,2%

git add .
git commit -m "update %date%"
git push origin main

echo.
echo Push complete!
pause