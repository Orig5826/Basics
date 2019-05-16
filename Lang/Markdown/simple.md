# Markdown相关描述
![Logo](../../apaki.jpg)
`2019.05.16 by jianfeng`

## VSCode 常用插件
- Markdown All in One [1]
    > 带有Latex某些语法特性，自动填充、显示等功能
    - 一开始可以使用该插件，对于不熟悉Latex语法的人很有帮助
- Markdown Preview Enhanced [2]
    > 可以显示Latex某些特性(不能自动填充)，也带有flow(流程图)等的绘制
    - [详细文档](https://shd101wyy.github.io/markdown-preview-enhanced/#/zh-cn/)

## Markdown 基本规范
> 部分规范已经熟悉，不再详述。本文档主要记录特殊点


## Markdown -> 对Latex的支持 [1]
- 常用基础语法
$$  
\begin{aligned}  
f(x) &= (m+n)^2 \\  
&= m^2+2mn+n^2 \\  
\end{aligned}  
$$


## Markdown -> 对Flow的支持 [2]
```flow
st=>start: 鉴权
e=>end: 结束退出
cond1=>condition: user==bgbiao
product=ddaotian
productcheck=>condition: ddaotian类型产品库存
(ecs,bss,vpc,eip,hids)

op1=>operation: 发起预订请求
拆单并库存检测
op2=>operation: info:生产指定类型产品
(DAOTIAN:ecs,natip,eip,hids)
op3=>operation: 鉴权失败
op4=>operation: 库存检测失败
io1=>inputoutput: 返回产品相关信息
ECS,NATIP,EIP,HIDS
io2=>inputoutput: info:无此类型产品

st->cond1
cond1(yes)->op1->productcheck(yes)->op2->io1->e
cond1(no)->op3->e
cond1(yes)->op1->productcheck(no)->op4->io2->e
```
