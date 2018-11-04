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
//���帨�����飬��¼����U��V-U��Ĵ�����С�ı� 
struct {
	int			adjvex;
	VRType		lowcost;
}closeedge[MAX_VERTEX_NUM]; 

//------------ͼ�����飨�ڽӾ��󣩴洢��ʾ---------------// 
typedef struct{
	VertexType 	vexs[MAX_VERTEX_NUM];				//�������� 
	VRType		arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];	//�ڽӾ��� 
	int     	vernum,arcnum;							//����ͻ��� 
}MAGraph;

bool	visited[MAX_VERTEX_NUM];						/*�Ѳ��ҵ����·���Ķ���ı�־�飬visited[v]=1��ʾ���ҵ���V0��v����̾��룬visited[v]=0��ʾ��δ�ҵ���V0��v����̾���*/
int		Value[MAX_VERTEX_NUM];							/* ���ڴ洢���������·����Ȩֵ�� */
int		Path[MAX_VERTEX_NUM];							//���ڴ洢���·���±������,,Path[j]��ʾj��ǰ�� 

//����������
Status CreateDN(MAGraph *g){
	
	int i,j;
	int start ,end ,num;
	printf("������ͼ�Ķ������ͻ�����(Ҫ�󶥵���С�ڶ�ʮ)\n");
	scanf("%d %d", &g->vernum, &g->arcnum ); 	
	printf("ͼ�Ķ�������%d�ͻ�����%d\n", g->vernum, g->arcnum );
	printf("������ͼ�Ķ����ֵ\n");
	
	for(i = 0; i < g->vernum ; i++){
		getchar();
		scanf("%c", &g->vexs[i]);
		printf("��%d�������ֵ�ǣ�%c\n", i , g->vexs[i]);
	} 
	
	//��ʼ���ڽӾ��� 
	for(i = 0; i < g->vernum ; i++){
		for(j = 0; j < g->vernum ; j++){
			g->arcs[i][j] = INFINITY ;
		}
	}
	printf("�����뻡�����Ķ����Ȩֵ��\n");
	for( i = 0 ; i < g->arcnum ; i++ ){
		getchar();		
		scanf("%d %d %d", &start, &end ,&num );

		g->arcs[start][end] = num ;
		
		printf("����%cָ�򶥵�%c��Ȩֵ��%d\n", g->vexs[start] , g->vexs[end] , num);
	} 
	
	printf("��������ʼ���ɹ���\n");
	return OK;
} 

//���ڽӾ������ʽ�������ͼ 
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
�������ƣ�ShortestPath_Dijkstra(MAGraph G,int V0)
����������G-----------����Ӿ��󴴽���ͼ
		  V0------ ---���
		  Path-----------ָ�����������ָ�룬���·��ǰ�����飬���ڱ�ʾVO������V���·����ǰ��
		  Value-----------ָ�����������ָ�룬���·�����飬���ڱ�ʾVO������V���·��
����˵���������·���� Dijkstra�㷨 
*/

//�Ͻ�˹�����㷨�����·��
void ShortestPath(MAGraph *g, int v0){
	//��Dijkstra�㷨��������g��v�����Ķ��㵽������������·��Path��ȨֵValue
	//��Path[v] = J  ����¼v��ǰȥΪj�� 
	//visited[v]���ҽ���v��S��������Ѿ����v0��v�����·��
	int i, v,w, k;
	int min;
	for(v = 0 ; v < g->vernum ; v++){
		
		visited[v] = FALSE;					/*��ʼ�����ұ�־��*/				
		Value[v] = g->arcs[v0][v] ;			/*��ʼ�����·������*/
		Path[v] = -1;
	} 
	/*��ʼ��������㵽������·������Ͳ��ұ�־��*/
	Value[0] = 0;
	visited[0] = TRUE;
	
	for(i = 1 ; i < g->vernum ; i++){
		min = INFINITY;
		for(w = 0; w < g->vernum ; w++){	
			/*
			����VO�����Ķ����в��һ�û��ȷ�����·������VO����Ľ��Vw,
			��j=0ʱ���е�1��ѭ������min=INFINITY�����Value[w]<min)����
			���ʾV0��Vw������ӵģ�����֮������ӵ� 
			*/
			if(visited[w] == FALSE && Value[w] < min){
				v = w;											/* ���µ�ǰ�ҵ���VO����Ľ�� */
				min = Value[w];									/* �޸����ֵ */	
			}
		}
		
		visited[v] = TRUE;
		for(w = 0 ; w < g->vernum ; w++){
			/*���V0��Vw�ľ���Ҫ�Ⱦ�������Vv�����޸����·��ֵ������ǰ���޸�Ϊv*/
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
