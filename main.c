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
        int length;                     //��Ȩͼ���õ�·����length��ʾ�Ƿ�����
        char name[20];                     //�ߺ�����Ϣ��ָ�룬��·��
}EdgeCell, AdjMatrix[M][M];      //�ߵ�Ԫ���ڽӾ���

typedef struct {
        int num;                        //����ı��
        char name[20];                  //���������
}VertexCell,Vertex[M];                            //���㵥Ԫ�������˶���ı�ź�����

typedef struct {
        Vertex vertex;		         //����
        AdjMatrix edge;		//��ά���飬���ڼ�¼����֮��Ĺ�ϵ
        int vexNum, edgNum;	//������������
}MGraph;

//��ȡ�ļ�������������
void createMap(MGraph* g) {
        int i, j,k,e;
        char name[M];
        FILE* rf = fopen("data.txt", "r");
        if (rf)
        {
                fscanf(rf, "%d%d", &g->vexNum, &g->edgNum); // ��ȡ��������ͱ���
                for (i = 0; i < g->vexNum; i++) {             // ��ȡ����(�ر꽨��)��Ϣ
                        fscanf(rf, "%d%s", &e, name);
                        g->vertex[i].num = e;
                        strcpy(g->vertex[i].name, name);
                }
                for (i = 0; i < g->vexNum; i++) // �����ڽӾ���
                        for (j = 0; j < g->vexNum; j++)
                        {
                                if (i == j)
                                        g->edge[i][j].length = 0;
                                else
                                        g->edge[i][j].length = INF; // ��ʾ��ͨ
                        }
                for (k = 0; k < g->edgNum; k++) // ����Ȩ��
                {
                        fscanf(rf, "%d%d%d%s", &i, &j, &e, name);
                        g->edge[i][j].length = e;
                        strcpy(g->edge[i][j].name, name);
                        g->edge[j][i].length = e;                       //����Գ�
                        strcpy(g->edge[j][i].name, name);
                }
                
                fclose(rf);
        }
        else
                g->edgNum = 0;
}
//������·��Ϣ,�����ڽӾ�����������ھ���Գƣ�ֻ��Ҫ����һ��
void printGraph(MGraph* g) {
        int i, j;
        printf("\n��·��Ϣ�б�\n\n");
        for (i = 0; i < g->vexNum; i++)
        {
                for (j = i; j <g->vexNum ; j++)
                {
                        if (g->edge[i][j].length != INF&& g->edge[i][j].length != 0) {//����·���Ȳ�Ϊ0��-1��ʱ�򣬾�������·��
                                printf("%s ����Ϊ%d\n", g->edge[i][j].name, g->edge[i][j].length); // �����·���ƣ�����
                        }
                }
        }
}
// ���еر���Ϣ���
void printVertex(MGraph* g)
{
        int i, j;
        printf("\n�ر���Ϣ�б�\n\n");
        for (i = 0; i < g->vexNum; i++)
        {
                printf("%d %s\n", g->vertex[i].num, g->vertex[i].name); // �����š�����
                for (j = g->vexNum - i - 1; j >= 0; j--)
                {
                }
        }
        printf("\n");
}
//�������
void printMatrix(MGraph* g) {
        printf("��������%d,������%d\n", g->vexNum, g->edgNum);
        for (int i = 0; i < g->vexNum; i++)
        {
                for (int j = 0; j < g->vexNum; j++)
                {
                        if (g->edge[i][j].length == INF)
                                printf("��\t");
                        else
                                printf("%d\t ", g->edge[i][j].length);
                }
                printf("\n");
        }
}

// ��ѯ��������ĵر�
void searchClosest(MGraph* g)
{
        int i, position, res[M];
        int dis[M];
        int closest = INF;
        printf("\n����������ǰλ�õı�ţ�\n");
        scanf("%d", &position);
        position -= 1;
        for (int v = 0;v < g->vexNum;v++) {
                dis[v] = g->edge[position][v].length;              //��start�㵽�������Ȩֵ������dis������
                if (dis[v] < closest && dis[v] != 0) {
                        closest = dis[v];
                }
        }
        for (i = 0; i < M; i++) // ������
        {
                if (closest == dis[i])
                {
                        printf("\n%s���������������%d��\n", g->vertex[i].name, g->edge[position][i].length);
                }
        }
}



//Dijkstra�㷨�����ĳ�㵽���е�����·��
void Dijkstra(MGraph* g, int start, int path[M], int dis[M]) {       //g����start��ʾ������,path[i]��ʾi��һ�����㣬dis��ʾ��start����������i�����·��
        int final[M];                                              //Ϊ������������һ�����ֵ������ȷ�ϸö����Ƿ��Ѿ��ҵ����·��
        //�Ը�������г�ʼ��
        for (int v = 0;v < g->vexNum;v++) {
                final[v] = 0;
                dis[v] = g->edge[start][v].length;              //��start�㵽�������Ȩֵ������dis������
                path[v] = 0;
        }
        //startΪ��ʼ�㣬�����ظ��жϣ�ֱ�ӱ��
        dis[start] = 0;
        final[start] = 1;

        int temp = 0;                      //��ʱ���������ڱ����ҵ����µ��±�
        for (int i = 0;i < g->vexNum;i++) {
                int min = INF;
                //ѡ�񵽶���Ȩֵ��С�Ķ��㣬��Ϊ������ȷ�����·���Ķ���
                for (int w = 0;w < g->vexNum;w++) {             //����ÿ������
                        if (!final[w]) {                                              //����ö���û�б���ǣ�˵����û�� ���� 
                                if (dis[w] < min) {                               //ѭ������ʣ�µļ����������ҵ���̵�·��      
                                        temp = w;
                                        min = dis[w];
                                }
                        }
                }
                final[temp] = 1;                           //���øö���ı��Ϊ1
                //���µĶ����鵽�������Ȩֵ���и���
                for (int w = 0;w < g->vexNum;w++) {
                        if (!final[w] && (min + g->edge[temp][w].length < dis[w])) {
                                dis[w] = min + g->edge[temp][w].length;
                                path[w] = temp;
                        }
                }
        }
}



//���·��
int AIMatch(MGraph* g) {
        int dist[500];                       //����������dist[i]�洢��ǰ�ڵ�v��i����С����
        int path[500];                       //·��������path[i]=k;��ʾ��k��i
        int position, destination ;
        printVertex(g);                         //��ӡ����ı�ź�����
        printf("�����뵱ǰλ�ã�\n");
        scanf("%d", &position);
        position -= 1;
        printf("������Ҫȥ��Ŀ�ĵ�\n");
        scanf("%d",& destination);
        destination -= 1;
        Dijkstra(g, position, path, dist);
       

        printf("���·��Ϊ��%d\n",dist[destination]);

}

//floyd�㷨
void showFloydPath(MGraph* g, int path[][M], int v0, int v)
{ //���v0��v�������м���
        int k = path[v0][v];
        if (k == -1)
                return;
        showFloydPath(g, path, v0, k);
        printf("%s->", g->vertex[k].name);
        showFloydPath(g, path, k, v);
}

void showFloydResult(MGraph* g, int dist[][M], int path[][M])
{ //���floyd�Ľ��
        int u, v;
        for (u = 0; u < g->vexNum; u++)
                for (v = 0; v < g->vexNum; v++)
                        if (dist[u][v] == INF)
                                printf("[%d->%d]:���ɴ�.\n", u, v);
                        else if (g->vertex[u].num != g->vertex[v].num)
                        {
                                printf("[%d->%d]:%s->", g->vertex[u].num, g->vertex[v].num, g->vertex[u].name);
                                showFloydPath(g, path, u, v);
                                printf("%s", g->vertex[v].name);
                                printf("����·��%d��\n", dist[u][v]);
                        }
}

void floyd(MGraph* g)
{
        int dist[M][M];
        int path[M][M];
        int u, v, k;
        for (u = 0; u < g->vexNum; u++) //��ʼ��
                for (v = 0; v < g->vexNum; v++)
                {
                        dist[u][v] = g->edge[u][v].length;
                        path[u][v] = -1;
                }
        for (k = 0; k < g->vexNum; k++)//�м���
                for (u = 0; u < g->vexNum; u++)//Դ���
                        for (v = 0; v < g->vexNum; v++)
                                if (dist[u][k] != INF && dist[k][v] != INF && dist[u][k] + dist[k][v] < dist[u][v])
                                {
                                        dist[u][v] = dist[u][k] + dist[k][v];//��ͨ���м�������·��С��ԭ�������·��ʱ������
                                        path[u][v] = k;//ǰ��ָ���м���
                                }
        printf("\n���ж���ľ����·�����£�\n");
        showFloydResult(g, dist, path);
        system("pause");
}



int menu() {
        int choose;
        printf("====��ӭʹ�ó��е�·����ϵͳ=====\n");
        printf("                                                                                          \n");
        printf("\t1.��·��Ϣ��ѯ\n");      
        printf(" \n");    
        printf(" \t2.·�����ܹ滮\n");
        printf(" \n");
        printf("\t3.��ѯ��������ĵص�\n");
        printf("\n");
        printf("\t4.·�߲ο� \n");
        printf(" \n");
        printf("\t5.�˳�ϵͳ \n");
        printf("\n");
        printf("================================\n\n");
        printf("��ѡ�������ţ�");
        scanf("%d", &choose);
        printf("\n\n");
        return choose;
}

int main()
{
        MGraph* g= (MGraph*)malloc(sizeof(MGraph));
        createMap(g);
        int P[M] = { 0 };   // ��¼���� 0 �������������̵�·��
        int D[M] = { 0 };   // ��¼���� 0 �������������Ȩֵ
        while (1) {
                switch (menu())
                {
                       
                case 1:                 // ��·��Ϣ��ѯ��������
                         /**ʵ��Ҫ��1���洢����ʾ��·��Ϣ
                        �����ݴ����ļ��У�ֱ�Ӵ��ļ���ȡ��Ȼ��д���ڽӾ���
                        Ȼ����ٽ���������
                        */
                        printMatrix(g);
                        printGraph(g);
                        printVertex(g);
                        break;
                case 2:                 // Dijkstra�㷨,��õ㵽���е�����·��
                        AIMatch(g);
                        break;
                case 3:                 // ������������ĵط�
                        printVertex(g);
                        searchClosest(g);
                        break;
                case 4:                 // ·�߲ο�,���е�֮������·��
                        floyd(g);
                        break;
                case 5:                 // �˳�����ϵͳ
                        printf("�˳��ɹ���");
                        exit(0);					//�رճ���
                        system("puase");
                        break;
                default:
                        printf("����������������룡\n\n");
                        break;
                }
                system("pause");
                system("cls");
        }
        system("pause");
        return 0;
}