# 算法第二次Project

##一、项目说明
    利用随机算法求解最近对的近似解问题，算法说明详见课件。

    传入60000个784维向量，在随机生成的（a1,a2,a3...a100）100个向量上投影。
    找到每一个向量上的最近对作为候选结果，对所有的候选结果计算欧式距离，找到最近对。

##二、项目结构
    参考TA给出的示例结构，高度模块化管理。头文件统一放置在headers.h文件中，processing.cpp中完成数据的投影处理，closest_pair.cpp中完成最近对的查找，main.cpp是整个程序的接口。
    直接在终端运行makefile文件进行结果校对。每一次运行都对投影向量使用了利用中位数划分查找最近对和随机数两种方式，以进行比较。

##三、需要做的事情：
####数据读写及处理：
    1、解析二进制文件，得到dataset。
    2、生成满足正态分布的随机投影向量。

####最近对算法：
    1、将每一个向量上的投影结果按照中位数／随机基准分成两部分。
    2、将两部分中的最近对和划分位置的相邻两点比较，得出该投影向量上的最近对。
    3、比较所有投影向量上的最近对结果，得出欧式距离最近的点集，即为最近对的近似解。

