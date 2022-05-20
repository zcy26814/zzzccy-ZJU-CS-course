本文件夹包含四个执行程序和四个对应的bash脚本(实现输入或输出重定向)，实现四种功能：(Linux环境下)
1. pdadd 添加一条日志到pd中，若已有相同日期，则会选择最新添加的作为pd中的entity。
2. pdlist 列表显示所有或给定日期范围内的所有日志。
3. pdshow 显示给定日期的对应entity内容。
4. pdremove 删除给定日期的对应entity，成功返回0，失败返回1。
四个程序通过pd.txt进行交互，pdadd可以往pd.txt写内容，pdlist和pdshow可以读取pd.txt中内容，pdremove可以读写pd.txt内容。pd.txt存储pd的实例内容。pdlist，pdshow，pdremove的日期参数由命令行参数输入。
具体使用方式：
命令行中输入命令：
sh pdadd.sh
这时会等待用户输入日志(从标准输入)，格式为第一行日期：2021-5-15，第二行开始是entity内容，最后以单行“.”作为结束符(或者Ctrl+D)。
sh pdlist.sh或sh pdlist.sh 2021-5-15 2021-5-25
这个会打印全部pd中的日志或者打印给定日期范围的所有日志，输出为标准输出。
sh pdshow.sh 2021-5-15
这个会打印给定日期的entity内容，若没有则显示“This date has no entity.”输出到标准输出。
sh pdremove 2021-5-15
这个会删除pd中给定日期的entity，若成功则返回0，失败则返回-1。

