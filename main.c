#define _CRT_SECURE_NO_WARNINGS
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"

#define M 20
#define Pwd_Max 10
#define Input_Max 3
#define INF 99999

typedef struct {
        int length;                     //带权图，用道路长度length表示是否相邻
        char name[20];                     //边含有信息的指针，道路名
}EdgeCell, AdjMatrix[M][M];      //边单元，邻接矩阵

typedef struct {
        int num;                        //顶点的编号
        char name[20];                  //顶点的名字
}VertexCell,Vertex[M];                            //顶点单元，储存了顶点的编号和名字

typedef struct {
        Vertex vertex;		         //顶点
        AdjMatrix edge;		//二维数组，用于记录顶点之间的关系
        int vexNum, edgNum;	//顶点数，边数
}MGraph;

//读取文件，建立无向网
void createMap(MGraph* g) {
        int i, j,k,e;
        char name[M];
        FILE* rf = fopen("data.txt", "r");
        if (rf)
        {
                fscanf(rf, "%d%d", &g->vexNum, &g->edgNum); // 读取顶点个数和边数
                for (i = 0; i < g->vexNum; i++) {             // 读取顶点(地标建筑)信息
                        fscanf(rf, "%d%s", &e, name);
                        g->vertex[i].num = e;
                        strcpy(g->vertex[i].name, name);
                }
                for (i = 0; i < g->vexNum; i++) // 创建邻接矩阵
                        for (j = 0; j < g->vexNum; j++)
                        {
                                if (i == j)
                                        g->edge[i][j].length = 0;
                                else
                                        g->edge[i][j].length = INF; // 表示不通
                        }
                for (k = 0; k < g->edgNum; k++) // 附上权重
                {
                        fscanf(rf, "%d%d%d%s", &i, &j, &e, name);
                        g->edge[i][j].length = e;
                        strcpy(g->edge[i][j].name, name);
                        g->edge[j][i].length = e;                       //矩阵对称
                        strcpy(g->edge[j][i].name, name);
                }
                
                fclose(rf);
        }
        else
                g->edgNum = 0;
}
//遍历道路信息,利用邻接矩阵遍历，由于矩阵对称，只需要遍历一半
void printGraph(MGraph* g) {
        int i, j;
        printf("\n道路信息列表\n\n");
        for (i = 0; i < g->vexNum; i++)
        {
                for (j = i; j <g->vexNum ; j++)
                {
                        if (g->edge[i][j].length != INF&& g->edge[i][j].length != 0) {//当道路长度不为0和-1的时候，就是这条路有
                                printf("%s 长度为%d\n", g->edge[i][j].name, g->edge[i][j].length); // 输出道路名称，长度
                        }
                }
        }
}
// 所有地标信息输出
void printVertex(MGraph* g)
{
        int i, j;
        printf("\n地标信息列表\n\n");
        for (i = 0; i < g->vexNum; i++)
        {
                printf("%d %s\n", g->vertex[i].num, g->vertex[i].name); // 输出编号、名称
                for (j = g->vexNum - i - 1; j >= 0; j--)
                {
                }
        }
        printf("\n");
}
//输出矩阵
void printMatrix(MGraph* g) {
        printf("顶点数：%d,边数：%d\n", g->vexNum, g->edgNum);
        for (int i = 0; i < g->vexNum; i++)
        {
                for (int j = 0; j < g->vexNum; j++)
                {
                        if (g->edge[i][j].length == INF)
                                printf("∞\t");
                        else
                                printf("%d\t ", g->edge[i][j].length);
                }
                printf("\n");
        }
}

// 查询离我最近的地标
void searchClosest(MGraph* g)
{
        int i, position, res[M];
        int dis[M];
        int closest = INF;
        printf("\n请输入您当前位置的编号：\n");
        scanf("%d", &position);
        position -= 1;
        for (int v = 0;v < g->vexNum;v++) {
                dis[v] = g->edge[position][v].length;              //将start点到各顶点的权值保存在dis数组中
                if (dis[v] < closest && dis[v] != 0) {
                        closest = dis[v];
                }
        }
        for (i = 0; i < M; i++) // 输出结果
        {
                if (closest == dis[i])
                {
                        printf("\n%s离您最近，距离是%d米\n", g->vertex[i].name, g->edge[position][i].length);
                }
        }
}



//Dijkstra算法，输出某点到所有点的最短路径
void Dijkstra(MGraph* g, int start, int path[M], int dis[M]) {       //g矩阵，start表示出发点,path[i]表示i上一个顶点，dis表示从start出发到顶点i的最短路径
        int final[M];                                              //为各个顶点配置一个标记值，用于确认该顶点是否已经找到最短路径
        //对各数组进行初始化
        for (int v = 0;v < g->vexNum;v++) {
                final[v] = 0;
                dis[v] = g->edge[start][v].length;              //将start点到各顶点的权值保存在dis数组中
                path[v] = 0;
        }
        //start为起始点，不用重复判断，直接标记
        dis[start] = 0;
        final[start] = 1;

        int temp = 0;                      //临时变量，用于保存找到的新的下标
        for (int i = 0;i < g->vexNum;i++) {
                int min = INF;
                //选择到顶点权值最小的顶点，即为本次能确定最短路径的顶点
                for (int w = 0;w < g->vexNum;w++) {             //遍历每个顶点
                        if (!final[w]) {                                              //如果该顶点没有被标记，说明还没被 加入 
                                if (dis[w] < min) {                               //循环，在剩下的几个顶点中找到最短的路径      
                                        temp = w;
                                        min = dis[w];
                                }
                        }
                }
                final[temp] = 1;                           //设置该顶点的标记为1
                //对新的顶点组到个顶点的权值进行更新
                for (int w = 0;w < g->vexNum;w++) {
                        if (!final[w] && (min + g->edge[temp][w].length < dis[w])) {
                                dis[w] = min + g->edge[temp][w].length;
                                path[w] = temp;
                        }
                }
        }
}



//最短路径
int AIMatch(MGraph* g) {
        int dist[500];                       //距离向量，dist[i]存储当前节点v到i的最小长度
        int path[500];                       //路径向量，path[i]=k;表示从k到i
        int position, destination ;
        printVertex(g);                         //打印顶点的编号和名称
        printf("请输入当前位置：\n");
        scanf("%d", &position);
        position -= 1;
        printf("请输入要去的目的地\n");
        scanf("%d",& destination);
        destination -= 1;
        Dijkstra(g, position, path, dist);
       

        printf("最短路径为：%d\n",dist[destination]);

}

//floyd算法
void showFloydPath(MGraph* g, int path[][M], int v0, int v)
{ //输出v0到v的所有中间结点
        int k = path[v0][v];
        if (k == -1)
                return;
        showFloydPath(g, path, v0, k);
        printf("%s->", g->vertex[k].name);
        showFloydPath(g, path, k, v);
}

void showFloydResult(MGraph* g, int dist[][M], int path[][M])
{ //输出floyd的结果
        int u, v;
        for (u = 0; u < g->vexNum; u++)
                for (v = 0; v < g->vexNum; v++)
                        if (dist[u][v] == INF)
                                printf("[%d->%d]:不可达.\n", u, v);
                        else if (g->vertex[u].num != g->vertex[v].num)
                        {
                                printf("[%d->%d]:%s->", g->vertex[u].num, g->vertex[v].num, g->vertex[u].name);
                                showFloydPath(g, path, u, v);
                                printf("%s", g->vertex[v].name);
                                printf("，总路程%d米\n", dist[u][v]);
                        }
}

void floyd(MGraph* g)
{
        int dist[M][M];
        int path[M][M];
        int u, v, k;
        for (u = 0; u < g->vexNum; u++) //初始化
                for (v = 0; v < g->vexNum; v++)
                {
                        dist[u][v] = g->edge[u][v].length;
                        path[u][v] = -1;
                }
        for (k = 0; k < g->vexNum; k++)//中间结点
                for (u = 0; u < g->vexNum; u++)//源结点
                        for (v = 0; v < g->vexNum; v++)
                                if (dist[u][k] != INF && dist[k][v] != INF && dist[u][k] + dist[k][v] < dist[u][v])
                                {
                                        dist[u][v] = dist[u][k] + dist[k][v];//当通过中间结点的最短路径小于原来的最短路径时，更新
                                        path[u][v] = k;//前驱指向中间结点
                                }
        printf("\n所有顶点的距离和路径如下：\n");
        showFloydResult(g, dist, path);
        system("pause");
}



int menu() {
        int choose;
        printf("====欢迎使用城市道路管理系统=====\n");
        printf("                                                                                          \n");
        printf("\t1.道路信息查询\n");      
        printf(" \n");    
        printf(" \t2.路线智能规划\n");
        printf(" \n");
        printf("\t3.查询离我最近的地点\n");
        printf("\n");
        printf("\t4.路线参考 \n");
        printf(" \n");
        printf("\t5.退出系统 \n");
        printf("\n");
        printf("================================\n\n");
        printf("请选择操作编号：");
        scanf("%d", &choose);
        printf("\n\n");
        return choose;
}

int main()
{
        MGraph* g= (MGraph*)malloc(sizeof(MGraph));
        createMap(g);
        int P[M] = { 0 };   // 记录顶点 0 到各个顶点的最短的路径
        int D[M] = { 0 };   // 记录顶点 0 到各个顶点的总权值
        while (1) {
                switch (menu())
                {
                       
                case 1:                 // 道路信息查询（遍历）
                         /**实验要求1，存储和显示道路信息
                        将数据存在文件中，直接从文件读取，然后写入邻接矩阵
                        然后从临界矩阵遍历边
                        */
                        printMatrix(g);
                        printGraph(g);
                        printVertex(g);
                        break;
                case 2:                 // Dijkstra算法,求该点到所有点的最短路径
                        AIMatch(g);
                        break;
                case 3:                 // 查找离我最近的地方
                        printVertex(g);
                        searchClosest(g);
                        break;
                case 4:                 // 路线参考,所有点之间的最短路径
                        floyd(g);
                        break;
                case 5:                 // 退出导航系统
                        printf("退出成功！");
                        exit(0);					//关闭程序
                        system("puase");
                        break;
                default:
                        printf("输入错误，请重新输入！\n\n");
                        break;
                }
                system("pause");
                system("cls");
        }
        system("pause");
        return 0;
}