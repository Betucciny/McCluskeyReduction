#include <stdio.h>
#include <stdlib.h>
#define N 4

struct node{
    int data[N];
    struct node *next;
};

void copyarr(int from[][N],int to[][N],int elementos){
    for (int i=0;i<elementos;i++) for(int j=0;j<N;j++) to[i][j]=from[i][j];
}

struct node* push(struct node *top, int item[N]){
    struct node *nptr = malloc(sizeof(struct node));
    for(int i=0;i<N;i++)
        nptr->data[i] = item[i];
    nptr->next = top;
    top = nptr;
    return top;
}

void display(struct node *top){
    struct node *temp;
    temp = top;
    while (temp != NULL){
        for(int i=0;i<N;i++){
            if(temp->data[i]==2) printf("%c",45);
            if(temp->data[i]==1 || temp->data[i]==0) printf("%d", temp->data[i]);

        }
        temp = temp->next;
        printf("\n");
    }
}

void displayans(struct node *top){
    struct node *temp;
    int as,check=0;
    temp = top;
    while (temp != NULL){
        as=65;
        if(check) printf(" + ");
        for(int i=0;i<N;i++){
            if(temp->data[i]==1 || temp->data[i]==0) printf("%c", as);
            if(temp->data[i]==0) printf("%c",39);
            as++;
        }
        temp = temp->next;
        check++;
    }
}

struct node* reduce(struct node *group[],int nums[][N],struct node *ans,int r,int tot,int *totans){
    struct node* ngroup[r-1];
    struct node *temp1, *temp2,*temp3;
    int atemp[N], check=0,i,j,k,rep,repd,casig=0,checkf;
    for(i=0;i<r-1;i++) ngroup[i]=NULL;
    for(i=0;i<r-1;i++){
        temp1=group[i];
        while (temp1 != NULL){
            temp2=group[i+1];
            while (temp2 != NULL){
                for(j=0;j<N;j++){
                    if(temp1->data[j]!=temp2->data[j]){
                        atemp[j]=2;
                        check++;
                    }else if(temp1->data[j]==temp2->data[j])
                        atemp[j]=temp1->data[j];
                }
                if(check==1){
                    temp3 = ngroup[i];
                    repd=0;
                    while (temp3 != NULL){
                        rep=0;
                        for(j=0;j<N;j++){
                            if(temp3->data[j]==atemp[j]) rep++;
                        }
                        if(rep==N){
                            repd++;
                            break;
                        }
                        temp3 = temp3->next;
                    }
                    if(repd==0){
                        ngroup[i]= push(ngroup[i],atemp);
                        casig++;
                    }
                }
                check=0;
                temp2 = temp2->next;
            }
            temp1 = temp1->next;
        }
    }
    r--;
    if(casig>0) ans=reduce(ngroup,nums,ans,r,tot,totans);
    r++;
    for(i=0;i<r;i++){
        temp1=group[i];
        display(group[i]);
        while (temp1 != NULL){
            checkf=0;
            for(j=0;j<tot;j++){
                check=0;
                for(k=0;k<N;k++){
                    if(temp1->data[k]==nums[j][k] || temp1->data[k]==2) check++;
                    else break;
                }
                if(check==N){
                    checkf++;
                    for(k=0;k<N;k++) nums[j][k]=-1;
                }
            }
            if(checkf){
                ans= push(ans,temp1->data);
                (*totans)++;
            }
            temp1 = temp1->next;
        }
    }
    printf("\n");
    return ans;
}

void grouping(int nums[][N], int cant,struct node* group[N+1]){
    int i,j,count=0;
    for(i=0;i<cant;i++){
        for (j=0;j<N;j++) if(nums[i][j]==1) count++;
        group[count]= push(group[count],nums[i]);
        count=0;
    }
}

void decabin(int n,int*num) {
    if (n) {
        decabin(n / 2, num-1);
        *num =n%2;
    }
}

void bin(int nums[][N],int tot){
    int i,j;
    int temp[N];
    for (j=0;j<tot;j++){
        for(i=0;i<N;i++) temp[i]=0;
        decabin(j,&temp[N-1]);
        for(i=0;i<N;i++) {
            nums[j][i]=temp[i];
        }
    }
}

int entry(int nums[][N],int gnums[][N],int tot,int *gnumstot,int ggnums[][N]){
    int i,j,k=0,h,w,confirm=-1;
    bin(nums,tot);
    printf("Escriba 0 o 1 dependiendo de su tabla de verdad o 2 si es un comodin (no importa):\n");
    for(i=0;i<tot;i++){
        while(1) {
            printf("%2d ", i);
            for (j = 0; j < N; j++) printf("%d", nums[i][j]);
            printf(" :");
            scanf("%d",&confirm);
            fflush(stdin);
            if(confirm==0 || confirm==1 ||confirm==2) break;
        }
        if(confirm==1){
            for(w=0;w<N;w++)
                ggnums[*gnumstot][w]=nums[i][w];
            (*gnumstot)++;
        }
        if (confirm){
            for(h=0;h<N;h++){
                gnums[k][h]=nums[i][h];
            }
            k++;
        }
    }
    printf("\n");
    return k;
}

void stoarr(struct node *top, int ansarr[][N],int tot){
    struct node *temp1;
    temp1=top;
    while(temp1!=NULL){
        for(int j=0;j<N;j++) ansarr[tot-1][j]=temp1->data[j];
        tot--;
        temp1=temp1->next;
    }
}

struct node* select(struct node *fans,int ans[][N],int nums[][N],int anstot,int ntot){
    int i,j,k,check,checkf;
    for(i=0;i<anstot;i++){
        checkf=0;
        for(j=0;j<ntot;j++){
            check=0;
            for(k=0;k<N;k++){
                if(ans[i][k]==nums[j][k] || ans[i][k]==2) check++;
                else break;
            }
            if(check==N){
                checkf++;
                for(k=0;k<N;k++) nums[j][k]=-1;
            }
        }
        if(checkf){
            fans= push(fans,ans[i]);
        }
    }
    return fans;
}

struct node *simplify(struct node *fans,int ans[][N], int nums[][N],int totnums, int totans){
    int tempans[totans][N];
    int check,checkf,flag2,h=0,w;
    while(1){
        flag2=0;
        for(int i=0;i<totnums;i++) {
            checkf=0;
            for(int j=0;j<totans;j++){
                check=0;
                for(int k=0;k<N;k++) if(ans[j][k]==nums[i][k] || ans[j][k]==2) check++;
                if(check==N){
                    checkf++;
                    w=j;
                }
            }
            if(checkf==1){
                for(int k=0;k<N;k++) tempans[h][k]=ans[w][k];
                for(int k=0;k<N;k++) ans[w][k]=-1;
                flag2++;
                h++;
            }
        }
        if(flag2==0)break;
    }

    fans=select(fans,tempans,nums,totans,totnums);
    return fans;
}


int main() {
    int tot=1,i;
    for (i=0;i<N;i++) tot*=2;
    int nums[tot][N], gnums[tot][N],ggnums1[tot][N],gnumstot[1],totans[1], ggnums2[tot][N];
    (*gnumstot)=0;
    (*totans)=0;
    tot=entry(nums,gnums,tot,gnumstot,ggnums1);
    struct node *group[N+1];
    for(i=0;i<=N;i++) group[i]=NULL;
    struct node* ans;
    ans=NULL;
    grouping(gnums,tot,group);
    copyarr(ggnums1,ggnums2,(*gnumstot));
    ans=reduce(group,ggnums1,ans,N+1,*gnumstot,totans);
    int ansarr[*totans][N];
    stoarr(ans,ansarr,*totans);
    struct node *fans;
    fans=NULL;
    fans=simplify(fans,ansarr,ggnums2,(*gnumstot),(*totans));
    displayans(fans);
    return 0;
}

