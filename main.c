#include<stdio.h>
#include<math.h>
#define swap(a, b) {int tmp=a; a=b; b=tmp;}

int puck[5][3]={//실제 맵
    {1,2,3},
    {2,3,1},
    {3,1,2},
    {1,2,3},
    {0,0,0}
};
int map[5][3]={0};//시뮬 돌리는 맵
int O_Puck[4]={1,3,2,9};//우선 순위
int number[3]={8,2,4};//바코드 갯수(오른쪽에서 부터)
int f_puck[3]={0,0,0};//완성 판별용
int home=1;//출발&도착 지점
int count=0;
int need_puck[3][5]={0}, s_map[5][3]={0},s_map2[5][3]={0};//필요한 퍽 을 뽑아낸것,필요한 퍽의 갯수 s_map : 목표 or 완성 맵
int path[20][5]={0}, pt=0;//필요퍽의 시작 x,y,t,ex,ey

void sort(void);//퍽 정렬
void move(int x, int y, int t, int ex, int ey);// 무브
void findnum(void);// 숫자를 입력 받고 그에 해당 하는 퍽을 지정 해줌
void func(void);//sort 와 무브를 사용 하는 곳
//void swap(int * num11, int * num22){int temp=*num11; *num11=*num22; *num22=temp;}//스왑
int counttt=0;
int main(void){
    func();

    printf("\n\n ====MAP====\n");
    for(int i=4; i>=0; i--){
            for(int j=0; j<3; j++)
                printf("%3d ", map[i][j]);
            printf("\n\n");
        }
    printf(" ====PUCK====\n");
    for(int i=4; i>=0; i--){
            for(int j=0; j<3; j++)
                printf("%3d ", puck[i][j]);
            printf("\n\n");
        }
    // printf(" ====S_MAP====\n");
    // for(int i=4; i>=0; i--){
    //         for(int j=0; j<3; j++)
    //             printf("%3d ", s_map[i][j]);
    //         printf("\n\n");
    //     }
    // printf(" ====S_MAP2====\n");
    // for(int i=4; i>=0; i--){
    //         for(int j=0; j<3; j++)
    //             printf("%3d ", s_map2[i][j]);
    //         printf("\n\n");
    //     }
    //getchar();
}
//정렬
void sort(void)
{
    int fp=0,npc;
    int np[5]={0,};
    for(int i=0; i<3; i++) printf("%d", number[i]);
    for(int i=0; i<3; i++) for(int j=4; j>=0; j--) for(int ii=0; ii<3; ii++) if(map[j][i]==number[ii]){map[j][i]*=-1;number[ii]=0;break;}
    for(int i=0; i<3; i++){
        for(int j=4; j>=0; j--){
            if(map[j][i]>0){
                if(map[j+1][i]==0){
                    path[pt][0]=j;path[pt][1]=i;path[pt++][2]=1;
                    map[j][i]=0;
                }
                else{
                    int x=j+1,cnn=0;
                    // printf("\n\n ====MAP====\n");
                    // for(int i=4; i>=0; i--){
                    //         for(int j=0; j<3; j++)
                    //             printf("%3d ", map[i][j]);
                    //         printf("\n\n");
                    //     }
                    for(int ii=j+1; ii<5; ii++){if(map[ii][i]<0)cnn++;else if(map[ii][i]==0)break;}
                    while(cnn){
                        int ck=0;
                        for(int ii=0; ii<3&&ck==0; ii++){
                            if(ii!=i){
                                for(int jj=0; jj<5; jj++){
                                    if(map[jj][ii]==0){
                                        printf("\n%d %d : %d %d",j+cnn,i, jj, ii);getchar();
                                        path[pt][0]=j+cnn;path[pt][1]=i; path[pt][3]=jj;path[pt++][4]=ii;
                                        swap(map[j+cnn][i],map[jj][ii]);cnn--;ck=1;break;
                                    }
                                }
                            }
                        }
                    }
                    path[pt][0]=j;path[pt][1]=i;path[pt++][2]=1;
                    map[j][i]=0;
                }
            }
            else if(map[j][i]==-9)break;
        }
    }
    
}
//정렬 준비+move
void func(void){
    for(int i=0; i<3; i++) for(int j=0; j<5; j++) map[j][i]=puck[j][i];
    int fsum=0;
    for(int i=0; i<3; i++){
        for(int j=0; j<5; j++){
            if(fsum+map[j][i]<=number[i]&&map[j][i]!=0){
                fsum+=map[j][i];map[j][i]=-9;
            }
            else if(fsum+map[j][i]==number[i]){map[j][i]=-9;number[i]=0;break;}
            else break;
        }
        number[i]-=fsum;
        fsum=0;
    }

    sort();
    for(int i=0; i<pt; i++){
        for(int j=0; j<5; j++)printf("%d ", path[i][j]);printf("\n");
        move(path[i][0],path[i][1],path[i][2],path[i][3],path[i][4]);
        printf("======MOVE=======\n\n");
        for(int i=4; i>=0; i--){
            for(int j=0; j<3; j++)
                printf("%3d ", puck[i][j]);
            printf("\n\n");
        }
        getchar();
    }
    pt=0;
}

/*무빙을 위함 
x,y : 처리할 퍽 좌표
t : 버리는 퍽인지 판단 1=버림 0=움직임  
ex, ey : t==0 일때 퍽을 움직일 위치*/
void move(int x, int y, int t, int ex, int ey)
{
    if(!(x||y||ex||ey))return;
    if(t==1){
        puck[x][y]=0;

    }
    else{
        
        
        swap(puck[x][y],puck[ex][ey]);

    }
}

//퍽을 뽑아 내는 함수
void findnum(void){
    int arr[5]={4};
    int count11[4]={0};
    
    for(int i=0; i<3; i++)for(int j=0; j<5; j++)++count11[map[j][i]];
    for(int i=0; i<3; i++){
        int sum=0,pp=3,j=0;
        while(pp){
            if(count11[pp]&&sum+pp<=number[i]){arr[j++]=pp; --count11[pp]; sum+=pp;}
            else if(count11[pp]&&sum+pp==number[i]){arr[j++]=pp; --count11[pp]; sum+=pp; break;}
            else pp--;
        }
        for(int j=0; j<5; j++)arr[j]=arr[j]==0?4:arr[j];
        for(int j=0; j<5 ; j++){need_puck[i][j]=arr[j]==4?0:arr[j]; arr[j]=0;}
    }
}
