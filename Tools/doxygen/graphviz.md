# graphviz DOT使用笔记
`2019.04.28 by jianfeng`

### notepad++工具直接预览
- cmd /C cd /d "$(CURRENT_DIRECTORY)" & dot -Tsvg "$(FULL_CURRENT_PATH)" -o dot.svg & cd "$(CURRENT_DIRECTORY)" & dot.svg

### 示例参考
- [对称算法：OFB流加密模式](./ofb.dot)
