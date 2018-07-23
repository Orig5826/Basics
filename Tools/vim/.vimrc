" 添加vim的一些参数，以方便vim用来写c程序

"配置状态栏显示
set statusline=
set statusline+=%1*[%n]
set statusline+=%#fname#\ %<%F%m%r%h%w%=
set statusline+=%3*\ %{&ff}
set statusline+=%4*\ %{\"\".(&fenc==\"\"?&enc:&fenc).((exists(\"+bomb\")\ &&\ &bomb)?\"+\":\"\").\"\"}
set statusline+=%5*\ [%l,%v]
set statusline+=%6*\ %p%%

" 黑色背景下使用
" 目测应该时xterm的8色配置
"0      Black
"1      DarkBlue
"2      DarkGreen
"3      DarkCyan
"4      DarkRed
"5      DarkMagenta
"6      Brown, DarkYellow
"7      LightGray, LightGrey, Gray, Grey
"8      DarkGray, DarkGrey
"9      Blue, LightBlue
"10     Green, LightGreen
"11     Cyan, LightCyan
"12     Red, LightRed
"13     Magenta, LightMagenta
"14     Yellow, LightYellow
"15     White
hi fname cterm=bold ctermfg=Blue 	ctermbg=White
hi User1 cterm=bold ctermfg=Red 	"ctermbg=White
hi User3 cterm=bold ctermfg=Red 	"ctermbg=White
hi User4 cterm=bold ctermfg=Yellow 	"ctermbg=White
hi User5 cterm=bold ctermfg=White 	"ctermbg=White
hi User6 cterm=bold ctermfg=Magenta "ctermbg=White

" 白色背景下使用
" 
:colorscheme delek


set laststatus=2 "2.总是显示状态栏 1.多窗口时显示 0.不显示
set showcmd	"显示Normal模式下的当前命令
set autoindent	"自动缩进
set nu		"显示行号
"set ruler	"显示最后一行的状态 --- 据说设置了statusline之后，这个就没用了
"set showmode 	"左下角那行的状态
syntax on	"语法检查
:colorscheme delek
