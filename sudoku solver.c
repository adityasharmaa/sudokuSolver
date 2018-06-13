#include<stdio.h>
#include"cursor.h"
/*void backup(int (*b)[9][9])
{
    int i,j,m,h,t=0,mat[10][10];
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            m=0;
            if(*(*(*(b+i)+j)+0)!=0)
            {
                mat[t][0]=i;
                mat[t][1]=j;
                h=0;
                while(*(*(*(b+i)+j)+h)!=0)
                {
                    if(*(*(*(b+i)+j)+h)!=10)
                    {
                        mat[t][m+2]=*(*(*(b+i)+j)+h);
                        m++;
                    }
                    h++;
                }
            }
            if(m==2)
            {
                t++;
            }
        }
    }
}*/
void draw(int a)//draws grid 3 by 3
{
    int i,j;
    for(i=1;i<3;i++)
    {
        gotoxy(1,4*i+1+a);
        for(j=1;j<27;j++)
        {
            printf("%c",196);
        }
    }
    for(i=1;i<3;i++)
    {
        for(j=2;j<13;j++)
        {
            gotoxy(9*i,j+a);
            printf("%c",179);
        }
    }
}
void frexe(int rc,int k,int *a,int (*b)[9][9],int m)//refresh row or column(m=1 for row,m=2 for column) after being sure that k can occupy only two places lying in same row or column in a 3*3 grid
{
    int i,h;
    if(m==1)
    {
        for(i=0;i<9;i++)
    {
        if(i==a[0] || i==a[1])//leave only two source cells with k
        continue;
        if(*(*(*(b+rc)+i)+0)!=0)
        {
            h=0;
            while(*(*(*(b+rc)+i)+h)!=0)
            {
                if(*(*(*(b+rc)+i)+h)==k)
                {
                    *(*(*(b+rc)+i)+h)=10;
                    break;
                }
                h++;
            }
        }
    }
    }
    if(m==2)
    {
    for(i=0;i<9;i++)
    {
        if(i==a[0] || i==a[1])
        continue;
        if(*(*(*(b+i)+rc)+0)!=0)
        {
            h=0;
            while(*(*(*(b+i)+rc)+h)!=0)
            {
                if(*(*(*(b+i)+rc)+h)==k)
                {
                    *(*(*(b+i)+rc)+h)=10;
                    break;
                }
                h++;
            }
        }
    }
    }
}
void fresher(int b[9][9][9])//determine possibility of applying frexe() function
{
    int i,j,k,l,s,h,m,rw[9],cl[9];
    for(i=0;i<=6;i+=3)
    {
        for(j=0;j<=6;j+=3)
        {
            for(k=1;k<=9;k++)
            {
                m=0;
                for(l=i;l<=i+2;l++)
                {
                    for(s=j;s<=j+2;s++)
                    {
                        if(b[l][s][0]!=0)
                        {
                            h=0;
                            while(b[l][s][h]!=0)
                            {
                                if(b[l][s][h]==k)
                                {
                                    rw[m]=l;
                                    cl[m]=s;
                                    m++;
                                }
                                h++;
                            }
                        }
                    }
                }
                if(m==2)
                {
                    if(rw[0]==rw[1])
                    {
                        frexe(rw[0],k,cl,b,1);
                    }
                    if(cl[0]==cl[1])
                    {
                        frexe(cl[0],k,rw,b,2);
                    }
                }
            }
        }
    }
}
void cell(int i,int j,int (*b)[9][9])//source cell freed after filling value in cell
{
    int h=0;
    while(*(*(*(b+i)+j)+h)!=0)
    {
        *(*(*(b+i)+j)+h)=0;
        h++;
    }
}
void printb(int b[][9][9])//print content of all source cells
{
    int i,j;
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            if(b[i][j][0]!=0)
            {
                int g=0;
                printf("|%d,%d| ",i,j);
                while(b[i][j][g]!=0)
                {
                    printf("%d,",b[i][j][g]);
                    g++;
                }
                printf("\n");
            }
        }
    }
    printf("\n");
}
void printa(int a[][9])//print solution
{
    int i,j;
    gotoxy(1,18);
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            printf("%d",a[i][j]);
            if(i>=0 && i<=2)
            gotoxy(3*(j+1)+1,i+18);
            if(i>=3 && i<=5)
            gotoxy(3*(j+1)+1,i+19);
            if(i>=6 && i<=8)
            gotoxy(3*(j+1)+1,i+20);
        }
        if((i+1)%3==0)
        printf("\n\n ");
        else
        printf("\n ");
    }
}
void refresh(int ij,int k,int (*a)[9][9],int m)//remove filled value from source cells of row or column m=1 for column , m=2 for row
{
    int c,d;
    if(m==1)
    {
    for(c=0;c<9;c++)
    {
        if(*(*(*(a+c)+ij)+0)!=0)
        {
            d=0;
            while(*(*(*(a+c)+ij)+d)!=0)
            {
                if(*(*(*(a+c)+ij)+d)==k)
                {
                    *(*(*(a+c)+ij)+d)=10;
                    break;
                }
                d++;
            }
        }
    }
    }
    if(m==2)
    {
        for(c=0;c<9;c++)
    {
        if(*(*(*(a+ij)+c)+0)!=0)
        {
            d=0;
            while(*(*(*(a+ij)+c)+d)!=0)
            {
                if(*(*(*(a+ij)+c)+d)==k)
                {
                    *(*(*(a+ij)+c)+d)=10;
                    break;
                }
                d++;
            }
        }
    }
    }
}
int grid(int i,int j,int k,int a[][9],int (*b)[9][9],int m)//function to check presence of a number in 3*3 boxes or remove a number from 3*3 boxes
{
    int q,r,o,s,t;
    if(i>=0 && i<=2)
    {
        if(j>=0 && j<=2)
        {q=0; r=0;}
        if(j>=3 && j<=5)
        {q=0; r=3;}
        if(j>=6 && j<=8)
        {q=0; r=6;}
    }
    if(i>=3 && i<=5)
    {
        if(j>=0 && j<=2)
        {q=3; r=0;}
        if(j>=3 && j<=5)
        {q=3; r=3;}
        if(j>=6 && j<=8)
        {q=3; r=6;}
    }
    if(i>=6 && i<=8)
    {
        if(j>=0 && j<=2)
        {q=6; r=0;}
        if(j>=3 && j<=5)
        {q=6; r=3;}
        if(j>=6 && j<=8)
        {q=6; r=6;}
    }
    if(m==1)
    {
        t=0;
    for(o=q;o<=q+2;o++)
    {
        for(s=r;s<=r+2;s++)
        {
            if(a[o][s]==k)
            t++;
        }
    }
    return t;
    }
    if(m==2)
    {
        for(o=q;o<=q+2;o++)
        {
            for(s=r;s<=r+2;s++)
            {
                if(*(*(*(b+o)+s)+0)!=0)
                {
                    t=0;
                    while(*(*(*(b+o)+s)+t)!=0)
                    {
                        if(*(*(*(b+o)+s)+t)==k)
                        {
                            *(*(*(b+o)+s)+t)=10;
                            break;
                        }
                        t++;
                    }
                }
            }
        }
    }
}
int fill(int i,int j,int k,int a[][9],int(*b)[9][9])//function to check possibility of filling a number in a vacancy
{
    int m=0,n=0,p,q;
    for(p=0;p<9;p++)
    {
        if(a[i][p]==k)
        m++;
    }
    for(p=0;p<9;p++)
    {
        if(a[p][j]==k)
        n++;
    }
    q=grid(i,j,k,a,b,1);
    if(m==0 && n==0 && q==0)
    return 1;
    else
    return 0;
}
void main()
{
    int i,j,k,l,m,s,o,c,y1,h,n=0,x=0,a[9][9]/*={
                                                {0,0,0,4,3,0,0,8,1},
                                                {0,0,5,0,0,0,0,0,0},
                                                {0,0,0,2,0,0,5,9,0},
                                                {0,4,0,0,0,2,0,0,0},
                                                {0,0,9,0,0,7,0,3,0},
                                                {3,5,0,9,0,0,0,0,7},
                                                {0,0,2,0,0,4,8,6,9},
                                                {6,0,0,0,9,8,0,0,0},
                                                {0,0,0,0,0,0,0,0,0}
                                             }*/;
    static int b[9][9][9];
    printf("Enter the sudoku to be solved with missing values as zero\n");
    draw(0);
    gotoxy(1,2);
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            scanf("%d",&a[i][j]);
            if(i>=0 && i<=2)
            gotoxy(3*(j+1)+1,i+2);
            if(i>=3 && i<=5)
            gotoxy(3*(j+1)+1,i+3);
            if(i>=6 && i<=8)
            gotoxy(3*(j+1)+1,i+4);
        }
        if((i+1)%3==0)
        printf("\n\n ");
        else
        printf("\n ");
    }
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            if(a[i][j]==0)
            {
                x++;
                h=0;
                for(k=1;k<10;k++)
                {
                    if(fill(i,j,k,a,b)==1)
                    {
                        b[i][j][h]=k;
                        h++;
                    }
                }
            }
        }
    }
    printf("\nThere are %d VACANCIES in all\n\n",x);
    draw(16);
    while(n<x)
    {
        y1=n;
        for(i=0;i<9;i++)
        {
        for(k=1;k<=9;k++)
        {
            m=0;
            for(j=0;j<9;j++)
            {
                if(b[i][j][0]!=0)
                {
                    h=0;
                    while(b[i][j][h]!=0)
                    {
                        if(b[i][j][h]==k)
                        {
                            m++;
                            c=j;
                            break;
                        }
                        h++;
                    }
                }
            }
            //printf("%d-%d\n",k,m);
            if(m==1)
            {
                a[i][c]=k;
                ++n;
                refresh(c,k,b,1);
                grid(i,c,k,a,b,2);
                cell(i,c,b);
                fresher(b);
            }
        }
        }
        for(j=0;j<9;j++)
        {
        for(k=1;k<=9;k++)
        {
            m=0;
            for(i=0;i<9;i++)
            {
                if(b[i][j][0]!=0)
                {
                    h=0;
                    while(b[i][j][h]!=0)
                    {
                        if(b[i][j][h]==k)
                        {
                            m++;
                            c=i;
                            break;
                        }
                        h++;
                    }
                }
            }
            if(m==1)
            {
                a[c][j]=k;
                ++n;
                refresh(c,k,b,2);
                grid(c,j,k,a,b,2);
                cell(c,j,b);
                fresher(b);
            }
        }
        }
        for(i=0;i<=6;i+=3)
        {
        for(j=0;j<=6;j+=3)
        {
            for(k=1;k<=9;k++)
            {
                m=0;
                for(l=i;l<=i+2;l++)
                {
                    for(s=j;s<=j+2;s++)
                    {
                        if(b[l][s][0]!=0)
                        {
                            h=0;
                            while(b[l][s][h]!=0)
                            {
                                if(b[l][s][h]==k)
                                {
                                    m++;
                                    c=l;
                                    o=s;
                                    break;
                                }
                                h++;
                            }
                        }
                    }
                }
                if(m==1)
                {
                    a[c][o]=k;
                    ++n;
                    refresh(o,k,b,1);
                    refresh(c,k,b,2);
                    cell(c,o,b);
                    fresher(b);
                }
            }
        }
        }
        if(n==y1)
        {
            printa(a);
            printf("\n\nCANNOT BE SOLVED FURTHER USING PRESENT LOGIC");
            printf("\n\n%d VACANCIES FILLED OUT OF %d\n\n",n,x);
            printb(b);
            exit(2);
        }
    }
    printa(a);
    printf("\nGIVEN SUDOKU HAS BEEN COMPLETELY SOLVED\n\n");
}
