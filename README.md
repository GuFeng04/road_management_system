数据结构课程设计——小型城市道路管理系统

**功能需求**

本次实验设计的任务是实现一个简易的城市道路管理系统，设计要包含下列要求：

设计以学校周围地区为基础的道路管理系统，包含多个场所和多条道路，顶点和道路选择需有多样性，以体现程序的可行性。能够找出任意两点间的最短路径。

（1）输入的数据格式为：用地标建筑表示顶点，包含名称与编号，用道路表示边，包含名称和长度，即权值。构建邻接矩阵，包含顶点和边，以及顶点数和边数。

（2）输出的形式：输出则通过已有的信息数据，通过相关的操作输出相应信息。

（3）程序所能达成的功能：本程序可供任何人使用，主要功能：1、道路信息查询。2、路线智能规划。3查询离我最近的地点。4、路线参考。5、退出系统。

**总体方案设计**

系统通过main函数进入系统主菜单界面，根据用户的选择可分别进入：1、道路信息查询。2、路线智能规划。3查询离我最近的地点。4、路线参考。5、退出系统。

选择“道路信息查询”，遍历邻接矩阵，遍历顶点，遍历边。

选择“路线智能规划”，可以查询某两个点之间的最短路径。

选择“查询离我最近的地点”，利用邻接矩阵找到最近的地点。

选择“路线参考”，可以遍历所有的最短路径。

选择“退出程序”，则会退出程序。

![img](https://gitee.com/gufengspace/github_img/raw/master/img/道路管理1.png)

**详细设计**

（1）模拟地图：

![道路管理2](https://gitee.com/gufengspace/github_img/raw/master/img/%E9%81%93%E8%B7%AF%E7%AE%A1%E7%90%862.png)

（2）data.txt文件：

8 11

1 大仪工业园区

2 仪征奈山地质公园

3 瘦西湖风景区

4 月城科技广场

5 扬子津校区

6 扬力集团科技工业园

7 川奇光电工业园区

8 润扬湿地森林公园

0 1 15500 s125

0 2 21000 扬子津北路

1 2 24300 s353

2 3 6400 城南快速路

2 5 7300 扬子江中路

3 4 3200 扬子津校区

3 5 4700 邗江中路

4 5 2400 宁海线

4 6 2300 吴州西路

4 7 12400 润扬湿地森林公园

5 6 2500 维扬路