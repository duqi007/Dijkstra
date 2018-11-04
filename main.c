#include <stdio.h>
#include <stdlib.h>


/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define INFINITY			65535
#define MAX_VERTEX_NUM		20
#define OK					1
#define ERROR				0


typedef	char		VertexType;
typedef	int			VRType; 
typedef	int			Status; 
typedef	enum {TRUE, FALSE} bool;
//定义辅助数组，记录顶点U到V-U大的代价最小的边 
struct {
	int			adjvex;
	VRType		lowcost;
}closeedge[MAX_VERTEX_NUM]; 

//------------图的数组（邻接矩阵）存储表示---------------// 
typedef struct{
	VertexType 	vexs[MAX_VERTEX_NUM];				//顶点向量 
	VRType		arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];	//邻接矩阵 
	int     	vernum,arcnum;							//顶点和弧数 
}MAGraph;

bool	visited[MAX_VERTEX_NUM];						/*已查找到最短路径的顶点的标志组，visited[v]=1表示已找到从V0到v的最短距离，visited[v]=0表示还未找到从V0到v的最短距离*/
int		Value[MAX_VERTEX_NUM];							/* 用于存储到各点最短路径的权值和 */
int		Path[MAX_VERTEX_NUM];							//用于存储最短路径下标的数组,,Path[j]表示j的前驱 

//构造无向网
Status CreateDN(MAGraph *g){
	
	int i,j;
	int start ,end ,num;
	printf("请输入图的顶点数和弧数！(要求顶点数小于二十)\n");
	scanf("%d %d", &g->vernum, &g->arcnum ); 	
	printf("图的顶点数：%d和弧数：%d\n", g->vernum, g->arcnum );
	printf("请输入图的顶点的值\n");
	
	for(i = 0; i < g->vernum ; i++){
		getchar();
		scanf("%c", &g->vexs[i]);
		printf("第%d个顶点的值是：%c\n", i , g->vexs[i]);
	} 
	
	//初始化邻接矩阵 
	for(i = 0; i < g->vernum ; i++){
		for(j = 0; j < g->vernum ; j++){
			g->arcs[i][j] = INFINITY ;
		}
	}
	printf("请输入弧关联的顶点和权值！\n");
	for( i = 0 ; i < g->arcnum ; i++ ){
		getchar();		
		scanf("%d %d %d", &start, &end ,&num );

		g->arcs[start][end] = num ;
		
		printf("顶点%c指向顶点%c的权值是%d\n", g->vexs[start] , g->vexs[end] , num);
	} 
	
	printf("有向网初始化成功！\n");
	return OK;
} 

//以邻接矩阵的形式输出无向图 
void MAGraphPrint(MAGraph *g){
	
	int i,j;
	for(i = 0; i < g->vernum ; i++){
		for(j = 0; j < g->vernum ; j++){
			printf("%7d  ", g->arcs[i][j]);
		}
		printf("\n");
	}
}



/*
函数名称：ShortestPath_Dijkstra(MAGraph G,int V0)
函数参数：G-----------由领接矩阵创建的图
		  V0------ ---起点
		  Path-----------指向整型数组的指针，最短路径前驱数组，用于表示VO到顶点V最短路径的前驱
		  Value-----------指向整型数组的指针，最短路径数组，用于表示VO到顶点V最短路径
函数说明：求最短路径的 Dijkstra算法 
*/

//迪杰斯特拉算法求最短路径
void ShortestPath(MAGraph *g, int v0){
	//用Dijkstra算法求有向网g的v向量的顶点到各个顶点的最短路径Path和权值Value
	//若Path[v] = J  ，记录v的前去为j； 
	//visited[v]当且仅当v在S集合里，即已经求的v0到v的最短路径
	int i, v,w, k;
	int min;
	for(v = 0 ; v < g->vernum ; v++){
		
		visited[v] = FALSE;					/*初始化查找标志组*/				
		Value[v] = g->arcs[v0][v] ;			/*初始化最短路径数组*/
		Path[v] = -1;
	} 
	/*初始化关于起点到起点最短路径数组和查找标志组*/
	Value[0] = 0;
	visited[0] = TRUE;
	
	for(i = 1 ; i < g->vernum ; i++){
		min = INFINITY;
		for(w = 0; w < g->vernum ; w++){	
			/*
			在与VO关联的顶点中查找还没被确定最短路径且离VO最近的结点Vw,
			在j=0时进行第1次循环由于min=INFINITY，如果Value[w]<min)成立
			则表示V0与Vw是相领接的，否则反之不是领接的 
			*/
			if(visited[w] == FALSE && Value[w] < min){
				v = w;											/* 记下当前找到离VO最近的结点 */
				min = Value[w];									/* 修改最短值 */	
			}
		}
		
		visited[v] = TRUE;
		for(w = 0 ; w < g->vernum ; w++){
			/*如果V0到Vw的距离要比经过顶点Vv大则修改最短路径值，并将前驱修改为v*/
			if(visited[w] == FALSE && (min + g->arcs[v][w] < Value[w])){
				Value[w] = min + g->arcs[v][w];	
				Path[w] = v;
			}
			
		}
	}
	printf("Dijkstra\n");
	
} 

void PrintPath(MAGraph *g){
	int i , j ;
	for( i = 0 ;i < g->vernum ; i++){
		
		printf("\n%c-->%c weight:%d,path:", g->vexs[0] , g->vexs[i] ,Value[i]);
		j = i;
		printf("%c ", g->vexs[j]);
		while(Path[j] != -1)
		{
			printf("%c ", g->vexs[Path[j]]);	
			j=Path[j];
		}
		printf("%c ", g->vexs[0]);
		printf("\n");
	}
}


int main(int argc, char *argv[]) {
	
	MAGraph *g = NULL; 
	g = (MAGraph *)malloc(sizeof(MAGraph));
	CreateDN(g);
	MAGraphPrint(g);
	ShortestPath(g, 0);
	PrintPath(g);
	return 0;
}
