
/* This code is written by Anand Dhandhania(B10053),IIT Mandi. 
   Taking input a board with some tiles removed from it's edges, it finds the six congruent parts on the board using 
   Depth-First Search Algorithm.

   Input - 6*6 Board 

            0 0 0 0 0 0
	    0 0 0 0 0 0
	    0 0 0 0 0 0
	    0 1 1 1 1 0
	    0 0 0 0 1 0
	    0 1 0 0 0 0     */

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
int ***matrix;
int **board;
int ***orientations;
int size=1000000;
int count_meter=0;
int storage_orientation[6]={0,0,0,0,0,0};

/* This function returns back to the position on board with previous places block removed from it */
int backtrack(int size,int counter)
{

  int i,j,k=counter;
  // printf("%d",k);
  for(i=0;i<size;i++)
    {
      for(j=0;j<size;j++){
	if(*(*(board+i)+j)==k){
	  *(*(board+i)+j)=0;}}
    }

}

int check_adjacency(int first1, int first2, int sec1, int sec2)
{
  if(first1 >=0 && first2>=0 && sec1>=0 && sec2 >=0){
    if(first1== sec1){
       if(first2 - sec2 ==1 || first2 - sec2 == -1){
	 return 1;
       }
    }
    if(first2== sec2){
       if(first1 - sec1 ==1 || first1 - sec1 == -1){
	 return 1;
       }
    }
  }
  return 0;
}

/*removes the congruent parts from matrix*/
int congruent_remove(int number,int capacity){
  int outerloop=0,innerloop,flag=0;
  int row=capacity/2,col=capacity;
  if(capacity%2!=0)
    row++;
  while(outerloop<=number){
    innerloop=outerloop+1;
    while(innerloop<=number){
      flag=0;
      for(int a=0;a<row;a++){
	for(int b=0;b<col;b++){
	  if(matrix[outerloop][a][b]!=matrix[innerloop][a][b])
	    flag=1;
	}
      }
      if(flag==0){
	for(int a=0;a<row;a++){
	  for(int b=0;b<col;b++){
	    matrix[innerloop][a][b]=matrix[number][a][b];}}
	for(int a=0;a<row;a++){
	  for(int b=0;b<col;b++){
	    matrix[number][a][b]=-1;}}
	number--;
	innerloop--;
      }
      innerloop++;
    }
    outerloop++;
  }
  return number;
}
/* Function to find all the possible blocks that can be formed using the desired capacity.
   Capacity is equal to number of tiles/6 */
int get_parts(int numb){
  
  int i,j,k;
  int row=numb/2,col=numb;
  if(numb%2!=0)
    row=(numb+1)/2;

  matrix = (int***)malloc(size*sizeof(int**));
  for(i=0;i<size;i++)
    *(matrix+i)=(int**)malloc(row*sizeof(int*));
  for(i=0;i<size;i++){
    for(j=0;j<row;j++)
      *(*(matrix+i)+j)=(int*)malloc(col*sizeof(int));}
  for(i=0;i<size;i++){
    for(j=0;j<row;j++){
      for(k=0;k<col;k++)
	*(*(*(matrix+i)+j)+k)=-1;}}
  
  ***matrix=0;
  int blocks=numb-1;
  int flag=0,flag2=0;
  int part=0,ini_x,ini_y,oldparts=0,newparts=0,storex,storey,side;
  while(blocks>0){
    oldparts=newparts;
    while(oldparts>=0){
      flag=0;
      flag2=0;
      
      for(j=0;j<row;j++){
	for(k=0;k<col;k++){
	  if(matrix[oldparts][j][k]==0 && flag==0){
	    flag=1;
	    ini_x = j;
	    ini_y=k;
	    side=4;
	    if(j==0)
	      side--;
	    if(j== row-1)
	      side--;
	    if(k==col-1)
	      side--;
	    if(k==0 )
	      side--;
	   
	     j=0;
	     k=0;
	  }
	  if(flag==1){
	    if(check_adjacency(ini_x,ini_y,j,k)==1){
	      side--;
	      if(matrix[oldparts][j][k]!=0){
	      	flag2++;
		//store the first adjacent empty block
		if(flag2==1){
		  storex=j;
		  storey=k;
		}
		//store the matrix in new part if more than one adjacent empty block
		else{
		  if(newparts<size){
		    newparts++;
		    for(int a=0;a<row;a++){
		      for(int b=0;b<col;b++){
			matrix[newparts][a][b]=matrix[oldparts][a][b];
		      }
		    }
		    matrix[newparts][j][k]=0;
		  }
		}
	      }
	      //all the adjacent sides checked - find next 0
	      if(side==0){
		j=ini_x;
		k=ini_y;
		flag=0;
	      }
	    }
	  }
	}
      }
      matrix[oldparts][storex][storey]=0;
    oldparts--;
    }
    blocks--;

    newparts=congruent_remove(newparts,numb);
 
  }
  return newparts+1;
}
  

/* To find the initial positon for the part defined in a matrix of capacity*capacity/2.*/
int check_beginning(int **p,int n,int *subscript)  
{
  int i,j;
  int row=n/2,col=n;
  if(n%2!=0)
    row=(n+1)/2;
  for(i=0;i<row;i++)
    {
      for(j=0;j<col;j++){
	if(*(*(p+i)+j)==0)
	  {
	    subscript[0]=i;
	    subscript[1]=j;
	    return 0;
	  }
      }
    }
}

/* Function to make all possible orientations for a given block.
   A block will have total of eight orientations out of which some can be repetitive. */
 void make_all_orientations(int **matrix,int capacity)
{
 
  int row,col,temp; 
  int i,j;
  row=capacity/2;
  col=capacity;
  if(capacity%2!=0)
    row=(capacity+1)/2;
 
  for(int i=0;i<8;i=i+2){
    for(int j=0;j<row;j++){
      for(int k=0;k<col;k++)
	*(*(*(orientations+i)+j)+k)=-1;}}

 for(int i=1;i<8;i=i+2){
    for(int j=0;j<col;j++){
      for(int k=0;k<row;k++)
	*(*(*(orientations+i)+j)+k)=-1;}}

  for(int a=0;a<row;a++){
    for(int b=0;b<col;b++){
      orientations[0][a][b]=matrix[a][b];
    }
  }
 
  int flag=0,rowsize=row,colsize=col;
  for(int a=0;a<row;a++){
    flag=0;
    for(int b=0;b<col;b++){
      if(matrix[a][b]!=-1 )
	flag=1;
    }
    if(flag==0){
      rowsize=a;
      break;}
  }
  flag=0;
  for(int a=0;a<col;a++){
    flag=0;
    for(int b=0;b<row;b++){
      if(matrix[b][a]!=-1 && flag==0)
	flag=1;
    }
    if(flag==0){
      colsize=a;
      break;
    }
  }
  
  for(int a=0;a<rowsize;a++){
    for(int b=0;b<colsize;b++){
      orientations[4][a][colsize-b-1]=orientations[0][a][b];
    }
  }

  for(i=1;i<4;i++){
    for(int a=0;a<rowsize;a++){
      for(int b=0;b<colsize;b++){
	orientations[i][b][rowsize-a-1]=orientations[i-1][a][b];
	orientations[i+4][b][a]=orientations[i][b][rowsize-a-1];
	
      }
    }
    temp=rowsize;
    rowsize=colsize;
    colsize=temp;
  }
}

/*This function checks for the initial position on the board from where
  we need to put a block. */
int update_boardposition(int **matrix,int *p,int size)
{
  int i,j;
  for(i=0;i<size;i++){
    for(j=0;j<size;j++){
      if(matrix[i][j]==0){
	p[0]=i;
	p[1]=j;
	return 1;
      }
    }
  }
}

/*This function adds a block to the updated board position. */  
void add_shape(int **matrix1,int *matrix1_pos,int size1,int **matrix2,int *matrix2_pos,int row2,int col2,int signature)
{
  int i,j,k,l;
  k=matrix1_pos[0]-matrix2_pos[0];
  l=matrix1_pos[1]-matrix2_pos[1];
  for(i=0;i<row2;i++)
    {
      for(j=0;j<col2;j++)
	{
	  if(matrix2[i][j]==0 )
	    {
	      if(matrix1[k+i][l+j]==0)
		matrix1[k+i][l+j]=signature+1;
	    }
	}
    }
 
}

/*Function to check if it's possible to put the given block on the board */
int check_overlap(int **matrix1,int *matrix1_pos,int size1,int **matrix2,int *matrix2_pos,int row2,int col2)
{
  int i,j,k,l;
  k=matrix1_pos[0]-matrix2_pos[0];
  l=matrix1_pos[1]-matrix2_pos[1];
  if(l<0 || k<0)
    return 0;
  for(i=0;i<row2;i++)
    {
      for(j=0;j<col2;j++)
	{
	  if(matrix2[i][j]==0)
	    {
	      if((k+i)<size1 && (l+j)<size1)
		{
		  if(matrix1[k+i][l+j]==0  )
		    {}
		  else
		    return 0;
		}
	      else
		return 0;
	    }
	 
	}
    }
  return 1;
}
/* Goal Test Function */
int success(int **matrix,int size)
{
  int i,j,count=0;
  for(i=0;i<size;i++)
    for(j=0;j<size;j++)
      if(matrix[i][j]==0)
	return 0;
  return 1;

}

/*Recursively Implemented Depth-First Search Algorithm*/
int depth_first(int **board,int n,int capacity) 
{
  int row,col; 
  int orient=storage_orientation[count_meter];
  int buzzer=0;
  int part_position[2]={0,0};
  int board_position[2]={0,0};
  int i,j,k,alpha=0;
  
  while(buzzer==0 && orient < 8 && count_meter<6)
    { 
      if(orient%2 == 0)
	{
	  row=capacity/2;
	  col=capacity;
	  if(capacity%2!=0)
	    row=(capacity+1)/2;
	}
      else
	{
	  col=capacity/2;
	  row=capacity;
	  if(capacity%2!=0)
	    col=(capacity+1)/2;
	}

      /* for(i=0;i<row;i++){
	for(j=0;j<col;j++)
	  printf("%d ",*(*(*(orientations+orient)+i)+j));
	  printf("\n");}*/

      check_beginning(*(orientations+orient),capacity,part_position);
      // printf("%d,%d\n",part_position[0],part_position[1]);   
      update_boardposition(board,board_position,n);
      //printf("%d,%d\n",board_position[0],board_position[1]);
      
      buzzer=check_overlap(board,board_position,n,*(orientations+orient),part_position,row,col);
      //    printf("buzzer=%d\n",buzzer);
      if(buzzer==1)
	{ 
	  add_shape(board,board_position,n,*(orientations+orient),part_position,row,col,count_meter);
	  storage_orientation[count_meter]=orient+1;
	  count_meter++;
	  update_boardposition(board,board_position,n);	
	}
      else
	orient++;
    }
  alpha = success(board,n);
  if(alpha == 1)
    {
  //    printf("Success Attained\nHere is your board sir\n");
      for(i=0;i<n;i++){
	for(j=0;j<n;j++){
	  if(*(*(board+i)+j) < 0)
	    printf("X ");
	  else
	  printf("%d ",*(*(board+i)+j));
	}
	//printf("\n");
      }
      exit(1);
    }
 
  /*for(i=0;i<n;i++){
    for(j=0;j<n;j++)
      printf("%d ",*(*(board+i)+j));
      printf("\n");}*/
  

  if(buzzer==1)
    {
      depth_first(board,n,capacity);
    }
  else
    {
      if(count_meter == 0)
	return 0;
      
      backtrack(n,count_meter);
      storage_orientation[count_meter]=0;
      count_meter--;
      depth_first(board,n,capacity);
    }
}

/************** MAIN FUNCTION ***************/

int main(int argc,char *argv[]){
  
 
  int i,j,k;
  int a[6];
  int buzzer,orient,pos;
  int n,count=0,capacity;
  int check_bit=0;

  int part_count=0,row=0,col=0;

  /*initializing the storage orientation*/
  for(i=0;i<6;i++){
    storage_orientation[i]=0;
  }

  
 
  /* Board Initialization  */
  //printf("Enter the size of the board ");
 // scanf("%d",&n);
  n = atoi(argv[1]);	
  board = (int**)malloc(n*sizeof(int*));

  for(i=0;i<n;i++)
    *(board+i)=(int*)malloc(n*sizeof(int));
  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
      //scanf("%d",(*(board+i)+j));
	*(*(board+i)+j) =atoi(argv[2+n*i+j]); 
  
  /* End of initialization */

  for(i=0;i<n;i++)
    {
      for(j=0;j<n;j++)
	{
	  if( *(j + *(board+i)) == 0 )
	    {   
	      // printf("* ");
	      count++;
	    }
	  else
	    {
	      // printf("  ");
	      *(j + *(board+i)) = -1;
	    }
	}
    //  printf("\n");
    }
  
  
  /*error function */
  if (count%6 != 0 || count ==0)
    {
      printf("Error occured \n");
      exit(1);
    }
  else
    capacity=(int)count/6;
    
  //printf("%d\n",capacity);
  
  row=capacity/2;
  col=capacity;
  if(capacity%2!=0)
    row=(capacity+1)/2;

 /*initializing the orientations - array of matrices for storing all 8 orientation for a block.*/
  orientations= (int***)malloc(8*sizeof(int**));

  for(i=0;i<8;i++)
    {
      if(i%2==0)
	*(orientations+i)=(int**)malloc(row*sizeof(int*));
      else
	*(orientations+i)=(int**)malloc(col*sizeof(int*));
    }
  for(i=0;i<8;i++)
    {
      if(i%2==0)
	{
	  for(j=0;j<row;j++)
	    *(*(orientations+i)+j)=(int*)malloc(col*sizeof(int));
	}
      else
	{
	  for(j=0;j<col;j++)
	    *(*(orientations+i)+j)=(int*)malloc(row*sizeof(int));
	}
    }
  
  /*Function to get all possible combination of blocks*/
  part_count= get_parts(capacity);
  
   
  //  printf("number of parts%d\n",part_count);
  // printf("%d %d\n",row,col);

  for(i=0;i<part_count && check_bit==0;i++)  //loop for each part of one shape  MAIN LOOP !!! Era of destruction
    {
     // printf("i=%d\n",i);
      
      /*  for(j=0;j<row;j++){
	for(k=0;k<col;k++)
	  printf("%d ",*(*(*(matrix+i)+j)+k));
	  printf("\n");}*/

      make_all_orientations(*(matrix+i),capacity);
      count_meter=0;
      
      /*initializing the storage orientation whenever new block is taken*/
      for(j=0;j<6;j++){
	storage_orientation[j]=0;
      }
      
    
      /*  for(orient=0;orient<8;orient++)
	{
	  
	  if(orient%2 == 0)
	    {
	    row=capacity/2;
	      col=capacity;
	      if(capacity%2!=0)
		row=(capacity+1)/2;
	    }
	  else
	    {
	      col=capacity/2;
	      row=capacity;
	      if(capacity%2!=0)
		col=(capacity+1)/2;
	    }
	  for(i=0;i<row;i++)
	    {
	      for(j=0;j<col;j++)
		{
		  printf("%d ",*(*(*(orientations+orient)+i)+j));
		}
	      printf("\n");
	    }
	    }*/

     check_bit= depth_first(board,n,capacity);
     // printf("%d",check_bit);

    } 

  if(i==part_count)
    printf("no solution\n");
 return 0;
}




