@echo off
set src="demo.dot"
dot -Tsvg %src% -o dot.svg
