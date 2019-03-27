@echo off

dir /B /ON  /AD > file.txt
REM /B 空格式（没有标题信息和摘要）
REM /ON /O分类顺序 N表示按名称
REM /AD /A显示具有特定属性的文件 D表示目录