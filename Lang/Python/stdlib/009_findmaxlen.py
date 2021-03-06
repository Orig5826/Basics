aa = '''先生可知四月雨水居多，窗上也结了迷蒙的雾气，我整日端坐在桌前，只盼着先生能再一次路过我的窗子，解了我这不可言说的少女心事。我曾经拥有一切。果一定要让我说失去的话，我会说一个我记忆中最深刻的失去……
这世间青山灼灼星光杳杳 秋雨淅淅晚风慢慢 也抵不过公子眉目间的星辰呀
刚在身后 又到前头
不是所有的鱼都会生活在同一片海里
在你的人生中只要尽你所能地 真挚的去演奏就好了
非我族类，其心必异，楚虽大，非我族也”
答案不是唯一的，我要找感觉对的答案真实的我
“胖爷我就待在这里，只有两个人可以让我从这里出去，一个是你天真，一个就是小哥。你们一定要好好地活着，不要再发生任何要劳烦胖爷我的事情了，你知道胖爷年纪大了。当然，咱
们一起死在斗里，也算是一件美事。如果你们真的有一天，觉得有一个地方非去不可并且凶多吉少的话，一定要叫上我，别让胖爷这辈子再有什么遗憾。”
易涨易退山居水，易反易复小人心
时光磨去了青涩，让亲密蜕变成疏远，让纵情变成了沉默。
有一个夜晚我烧毁了所有的记忆，从此我的梦就透明了；有一个早晨我扔掉了所有的昨天，从此我的脚步就轻盈了。如果你感到委屈，证明你还有底线 。如果你感到迷茫，证明你还有追
求 。如果你感到痛苦，证明你还有力气 。如果你感到绝望，证明你还有希望 。
你不愿意种花，你说，我不愿看见它一点点凋落。是的，为了避免结束，你避免了一切开始。
我若不喜欢你，怎会和你做朋友？我若喜欢你，怎会仅仅与你做朋友？
终是庄周梦了蝶，你是恩赐也是劫 终是玉环停了曲，无人在懂琵琶语 终是木兰弃了剑，你是相思也是念 终是韩信放下枪，你是宿命也是光 终是弈星断了旗，一步生死一迷离 终是后羿
断了剑，此生注定难相恋 终是荆轲刺了秦，一代君王一世民 终是百里失了约，没你注定是残缺 终是世界太拥挤，梦醒时分再无你 终是悟空成了佛，你是堕落也是佛 终是李白醉了酒，
你是孤独也是愁 终是荆轲刺了秦，一代帝王一代臣 终是帝王忘了伤，也是难过也是痛 终是孟婆流下泪，才知悲伤也是情  终是项羽斩了缘，你是依偎也是缘 终是妲己迷了王，你是爱情也是劫 终是关羽失荆州，你是仁义也是忠 终是后羿断了剑，此生注定难相恋 终是韩信放下枪，你是宿命也是光
你觉得孤独就对了，那是让你认识自己的机会。你觉得不被理解就对了，那是让你认清朋友的机会。你觉得黑暗就对了，那样你才分辨得出什么是你的光芒。你觉得无助就对了，那样你才能明白谁是你的贵人。你觉得迷茫就对了，谁的青春不迷茫。
一个懂你泪水的人，胜过一群懂你笑容的人
有的恋人不知道怎么就走散了
易涨易退山居水，易反易复小人心
纵然生得好皮囊，腹内原来草莽
要变得坚强。如果很软弱的话，终有一日会连悲鸣都无法发出，活得像行尸走肉一般。
所谓同伴就是你看着他倒下来不及救援来不及悲伤但你会代替他笔直地站在战场上
明人不说暗话，你就是我想要的人。
群体只会干两种事——锦上添花或落井下石。
所有人都看到，塔上那个坚毅华贵，杀伐予夺，说一不二，似乎永远都坚不可摧的男子，在那一刻，犹如一个孩童般……失声痛哭
群体只会干两种事——锦上添花或落井下石。
如果你不了解自己的过去，怎么知道未来要往哪个方向走？－－楚子航
如果不是因为所遇并非良人，谁会再次踏上金玉台无奈起舞；如果不是因为受过伤，谁会漠然拒绝近在咫尺的温暖；如果不是因为那个人是你，谁会抛下一切跋涉千里去找那传说中的天涯海角？
'''

def find_maxlen_instr(ss):
    ll = ss.split("\n")
    length = 0
    # 寻找最长行长度
    for d in range(0,len(ll)):
        length = len(ll[0])
        if length < len(ll[d]):
            length = len(ll[d])
    # 返回长度最长行的内容
    for d in range(0,len(ll)):
        if length == len(ll[d]):
            return ll[d]

ret = find_maxlen_instr(aa)
print(ret)
