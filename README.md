# comp26120_2020_base

This repository is arranged into different branches for each lab or group of labs.

You can use the refresh script to grab any new material from the base repository. See comments in the script for how to use it.

Otherwise, see Blackboard for information about labs.



对于每个实验室或一组实验室，此存储库被安排在不同的分支中。

您可以使用刷新脚本从基本存储库中获取所有新材料。 请参阅脚本中的注释以了解如何使用它。

否则，请参阅黑板以获取有关实验室的信息。


算法c语言
登陆到COMPjudge检测是否通过all tests
partA 用hash table:
到目前为止，我们的快速查找函数的解决方案是对输入进行排序，在b部分中，我们将研究如何以排序的顺序存储它。在本部分中，您将采用一种不同的方法，该方法依赖hash function将要存储的值分布到一个固定大小的数组中。将字符串插入到hash table 中所需的hash value应该从该字符串派生。作为第一步:使用linear probing。然后为了理解发生了什么,您应该添加代码来计算冲突的次数,这样您就可以在print stats中计算每次访问的平均次数。
开放寻址的一个问题是，当不能插入值时该怎么办。为了让事情变得简单，你可以在这种情况下失败。您的代码应该保持表的num entries字段是最新的。insert function应该检查全表,并在出现这种情况时干净地退出程序。当表被填满时，你应该增加哈希表的大小(翻倍?)，然后重新哈希到一个更大的表。在C语言中,要小心内存泄漏.(不是很懂)
Part B:使用binary search trees
1.通过将要插入的值与现有值进行比较，完成insert function。如果它们相等，你应该怎么做?提示:;
这表示一个集合。
2.完成查找函数。重要的是，它应该遵循与插入相同的逻辑。
3.扩展代码以记录统计信息，比如高度和每次插入或查找的平均比较次数。
global:h and global:c:定义一些全局变量和函数
speller:c: the driver for each spell-checking program:每个拼写检查程序的驱动程序
从字典文件中读取字符串并将它们插入数据结构中
从第二个文本文件中读取字符串,并在数据结构中找到它们

set args -d ../data/simple/2/dict -s 13 -m 1 -v ../data/simple/2/infile
./speller_hash -d ../data/simple/2/dict -s 13 -m 1 -v ../data/simple/2/infile
python3 ./test.py c simple hash 1