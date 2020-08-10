// Factoriel hesab覺 //
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
#define empty 0
using namespace std;
//ptr is board
void initial_goal(int goal_ptr[][9],int line,int coloun);
void  Taking_input(int ptr[9][9],string name , int * line, int * coloun);
void upload_input(int ptr[9][9], string name ,int line,int coloun);
int move_left(int ptr[][9],int line,int coloun);
int move_right(int ptr[][9],int line,int coloun);
int move_up(int ptr[][9],int line,int coloun);
int move_down(int ptr[][9],int line,int coloun);
int move_intelligent(int ptr[][9],int line,int coloun,int goal_ptr[][9],int last_move);
int copy_ptr(int ptr[9][9],int copy[9][9]);
int find_the_same_line(int ptr[9][9],int ptr_2[9][9],int goal_ptr[9][9],int size);
int find_blank_coordinat_x(int ptr[][9],int line,int coloun);
int find_blank_coordinat_y(int ptr[][9],int line,int coloun);
int find_the_y(int ptr[][9],int y,int line,int coloun);
int find_the_x(int ptr[][9],int x,int line,int coloun);
int find_the_difference_between_two_coordinates(int x_1,int x_2,int y_1,int y_2);
int find_the_difference_between_two_ptr(int ptr[][9],int goal_ptr[][9],int line,int coloun);
void shuffle(int ptr[][9],int line,int coloun,int number_of_move);
void initializion(int ptr[][9],int size);
void display(int ptr[][9],int line,int coloun);
int main(int argc, char* argv[]){
	char selection;
	string name;
	int size;
	int goal_ptr[9][9];
	int last_move=4;
	int ptr[9][9];
	int check;
	int count=0 ;
	int coloun ;
	int number_of_move;
	int line ;
	int random;
	char choise ;
	// initializions the charts
	srand(time(NULL));
	if(argc==1){
		cout << "please enter size : " ;
		cin >> size ;
		coloun=size-1;
		line =size-1;


		initializion(ptr,size);
		initializion(goal_ptr,size);

		do{
		//	cout<<"output\n";
			display(ptr,line,coloun);
			cout <<"\n";
			cout << "Your move : " ;
			// select the selection
			cin >> selection ;

			if(selection=='u' || selection=='U'){
				move_up(ptr,line,coloun);
			}
			else if(selection=='r' || selection=='R'){
				move_right(ptr,line,coloun);
			}
			else if(selection=='d' || selection=='D'){
				move_down(ptr,line,coloun);
			}
			else if(selection=='l' || selection=='L' ){
				move_left(ptr,line,coloun);
			}
			else if(selection=='i' || selection=='I'){
			//	cout << "Last move " << last_move ;
			//	cout << "\n" ;
				last_move=move_intelligent(ptr,line,coloun,goal_ptr,last_move);
			}
			else if(selection=='s' || selection=='S'){
				number_of_move=line*coloun;
				shuffle(ptr,line,coloun,number_of_move);
			}
			count ++;
		}while(selection!='q' && selection!='Q' && last_move!=-1 && find_the_difference_between_two_ptr(ptr,goal_ptr,line,coloun)!=0);
		display(ptr,line,coloun);
		cout << "\n";
		cout << "Problem solved !! \n";
		cout << "Total number of moves " << count ;

	}
	else{
		Taking_input(ptr,argv[1],&line,&coloun);
		copy_ptr(ptr,goal_ptr);
		initial_goal(goal_ptr,line,coloun);
		cout << "\n" ;
		display(ptr,line,coloun);
		cout << "\n" ;

	// No problema
	//	cout << "Thats true" ;
	do{
		cout << "Your move(q or Q for exit) : ";
		cin >> choise ;
		if(choise=='v' || choise=='V'){
			check=0;
			while(find_the_difference_between_two_ptr(ptr,goal_ptr,line,coloun)!=0 && check !=100000000 ){
				if(check%15==0 && check!=0){
					cout << "RAND \n" ;
					number_of_move=3;
					shuffle(ptr,line,coloun,number_of_move);
					display(ptr,line,coloun);

				}
				else{
					last_move=move_intelligent(ptr,line,coloun,goal_ptr,last_move);
				}
				check++;
				display(ptr,line,coloun);
			//cout << "\n line coloun : " << line << coloun <<"\n";
				cout << "\n";
			}

			display(ptr,line,coloun);
		}
		else if(choise == 't'||choise == 'T' ){
			if(check>=100000000){
				cout << "Puzzle can not solved yet \n" ;
			}
			else {
				cout << "Puzzle has been solvedd in " << check-1 << " move\n" ;
			}
		}

		else if(choise == 'e' || choise=='E'){
			cout << "Name : " ;
			cin >> name ;
			upload_input(ptr,name,line,coloun);
			display(ptr,line,coloun);
			cout << "\n";


		}
		else if(choise == 'l' || choise =='L'){
			cout << "Name : " ;
			cin >> name ;
			Taking_input(ptr,name,&line,&coloun);
			display(ptr,line,coloun);
			cout << "\n";
			copy_ptr(ptr,goal_ptr);
			initial_goal(goal_ptr,line,coloun);
		}
		else if(choise == 's' || choise == 'S'){
			shuffle(ptr,line,coloun,coloun*line);
			display(ptr,line,coloun);
			cout << "\n" ;
		}

	}while(choise!='q' && choise !='Q');










}
find_the_difference_between_two_ptr(ptr,goal_ptr,line,coloun);



}

void shuffle(int ptr[][9],int line,int coloun,int number_of_move){
	int blank_coordinat_x;
	int blank_coordinat_y;
	int random;
	int selection;

	int i;
	int last_move=-1;

//	cout << "Number of moves : " << number_of_move << "\n" ;
	for(i=0;i<number_of_move;i++){
	//	display(ptr,line,coloun);
  //	cout << "\n" ;
		blank_coordinat_x=find_blank_coordinat_x(ptr,line,coloun);
		blank_coordinat_y=find_blank_coordinat_y(ptr,line,coloun);
		random=rand()%4; // 0=up , 1=left , 2=down , size=right

		while((random==0 && (blank_coordinat_y==0  || ptr[blank_coordinat_y-1][blank_coordinat_x]==0 || ptr[blank_coordinat_y-1][blank_coordinat_x]==95 || ptr[blank_coordinat_y-1][blank_coordinat_x]==99 ))
			|| (random==1 && (blank_coordinat_x==0 || ptr[blank_coordinat_y][blank_coordinat_x-1]==0 || ptr[blank_coordinat_y][blank_coordinat_x-1]==95 || ptr[blank_coordinat_y][blank_coordinat_x-1]==99))
			|| (random==2 && (blank_coordinat_y>line-1|| ptr[blank_coordinat_y+1][blank_coordinat_x]==0 || ptr[blank_coordinat_y+1][blank_coordinat_x]==95 || ptr[blank_coordinat_y+1][blank_coordinat_x]==99))
			|| (random==3 && (blank_coordinat_x>coloun-1  || ptr[blank_coordinat_y][blank_coordinat_x+1]==0   || ptr[blank_coordinat_y][blank_coordinat_x+1]==95 || ptr[blank_coordinat_y][blank_coordinat_x+1]==99 ))){
			random=rand()%4;
		}
	//	cout << "random : " << random << " y : "<< blank_coordinat_x << " x : " << blank_coordinat_x << "i : " << i<< "\n";
		// moving the blank tile !
		if(random==0 ){
	//		cout << "Pick them up\n";
			move_up(ptr,line,coloun);
			last_move=0;
		}
		else if(random==1 ){
	//		cout << "Pick them left\n";
			move_left(ptr,line,coloun);
			last_move=1;
		}
		else if(random==2 ){
	//		cout << "Pick them down\n";
			move_down(ptr,line,coloun);
			last_move=2;
		}
		else if(random==3 ){
//			cout << "Pick them right\n";
			move_right(ptr,line,coloun);
			last_move=3;
		}
		//display(ptr,line,coloun);
		//cout << "\n";


	}


}
// copy ptr from another ptr
int copy_ptr(int ptr[9][9],int copy[9][9]){
	int i=0;
	int k=0;
	for(i=0;i<9;i++){
		for(k=0;k<9;k++){
			copy[i][k]=ptr[i][k];
		}
	}
}
int find_the_difference_between_two_coordinates(int x_1,int x_2,int y_1,int y_2){
	int result=0;
	if(x_2>x_1){
		result=x_2-x_1;
	}
	else{
		result=x_1-x_2;
	}
	if(y_2>y_1){
		result=result+y_2-y_1;
	}
	else{
		result=result+y_1-y_2;
	}
	return result;
}
int find_the_x(int ptr[][9],int x,int line,int coloun){
	int final=0;
	int i;
	int k;
	for(i=0;i<=line;i++){
		for(k=0;k<=coloun;k++){
			if(ptr[i][k]==x){
				final=k;
			}
		}
	}
	return final;

}
int find_the_y(int ptr[][9],int y,int line,int coloun){
	int final=0;
	int i;
	int k;
	for(i=0;i<=line;i++){
		for(k=0;k<=coloun;k++){
			if(ptr[i][k]==y){
				final=i;
			}
		}
	}
	return final;

}
int find_the_difference_between_two_ptr(int ptr[][9],int goal_ptr[][9],int line,int coloun){
	int result=0;
	int x_1;
	int y_1;
	int x_2;//goal
	int y_2;//goal
	int i=0;
	int k=0;
	for(i=0;i<=line;i++){
		for(k=0;k<=coloun;k++){
			if(ptr[i][k]!=goal_ptr[i][k] && ptr[i][k]!=97){
				x_1=find_the_x(ptr,ptr[i][k],line,coloun);
				y_1=find_the_y(ptr,ptr[i][k],line,coloun);
				x_2=find_the_x(goal_ptr,ptr[i][k],line,coloun);
				y_2=find_the_y(goal_ptr,ptr[i][k],line,coloun);

				result= result+find_the_difference_between_two_coordinates(x_1,x_2,y_1,y_2);
	//			cout << "PTR : " <<ptr[i][k] << "i : k : "<< i << k << " RESULT : " << result << "\n" ;
			}

		}
//		cout << "Lİne over \n" ;
	}

	return result;
}
int find_the_smallest(int x_1,int x_2,int x_size,int x_4){ // find the smallest number
	if(x_1<=x_2 && x_1<=x_size && x_1 <= x_4){
		return x_1 ;
	}
	else if(x_2<=x_size && x_2<=x_4 && x_2 <= x_1){
		return x_2 ;
	}
	else if(x_size<=x_4 && x_size<=x_2 && x_size <= x_1){
		return x_size ;
	}
	else if(x_4<=x_2 && x_4<=x_size && x_4<=x_1){
		return x_4 ;
	}
	}
int move_intelligent(int ptr[][9],int line,int coloun,int goal_ptr[][9],int last_move){
	int blank_coordinat_x;
	int blank_coordinat_y;
	// Beginning those are 99
	int check_up=99;
	int check_left=99;
	int check_down=99;
	int check_right=99;
	int ptr_up[9][9];
	int ptr_left[9][9];
	int ptr_down[9][9];
	int ptr_right[9][9];
	int smallest_one;
	int select=-1;
	// find the blank coordinates
	blank_coordinat_x=find_blank_coordinat_x(ptr,line,coloun);
	blank_coordinat_y=find_blank_coordinat_y(ptr,line,coloun);
	copy_ptr(ptr,ptr_up);
	copy_ptr(ptr,ptr_left);
	copy_ptr(ptr,ptr_down);
	copy_ptr(ptr,ptr_right);
	// check if its over

	// find the best possibility
		if(blank_coordinat_y>0 && last_move!=2 && ptr[blank_coordinat_y-1][blank_coordinat_x]!=0 && ptr[blank_coordinat_y-1][blank_coordinat_x]!=95 && ptr[blank_coordinat_y-1][blank_coordinat_x]!=99){
		//cout << "UP\n";
		move_up(ptr_up,line,coloun);
		check_up=find_the_difference_between_two_ptr(ptr_up,goal_ptr,line,coloun);

		}
		if(blank_coordinat_x>0 && last_move!=3 && ptr[blank_coordinat_y][blank_coordinat_x-1]!=0 && ptr[blank_coordinat_y][blank_coordinat_x-1]!=95 &&  ptr[blank_coordinat_y][blank_coordinat_x-1]!=99){
			//cout << "LEFT\n";
			move_left(ptr_left,line,coloun);
			check_left=find_the_difference_between_two_ptr(ptr_left,goal_ptr,line,coloun);

		}
		if(blank_coordinat_y<=line-1 && last_move!=0 && ptr[blank_coordinat_y+1][blank_coordinat_x]!=0 && ptr[blank_coordinat_y+1][blank_coordinat_x]!=95 && ptr[blank_coordinat_y+1][blank_coordinat_x]!=99){
			//cout << "DOWN\n";
			move_down(ptr_down,line,coloun);
			check_down=find_the_difference_between_two_ptr(ptr_down,goal_ptr,line,coloun);

		}
		if(blank_coordinat_x<=coloun-1 && last_move!=1 && ptr[blank_coordinat_y][blank_coordinat_x+1]!=0 && ptr[blank_coordinat_y][blank_coordinat_x+1]!=95 && ptr[blank_coordinat_y][blank_coordinat_x+1]!=99){
/*			cout << "RİGHT\n"; 	*/
			move_right(ptr_right,line,coloun);
			check_right=find_the_difference_between_two_ptr(ptr_right,goal_ptr,line,coloun);
		}
		smallest_one=find_the_smallest(check_up,check_left,check_down,check_right);
		if(smallest_one==check_up){
					copy_ptr(ptr_up,ptr);
					last_move=0;
					cout << "Intelligent choose move U up"/* = " << check_up << " left = " << check_left <<"down = " << check_down <<" right = " << check_right*/<< "\n";

		}
		else if(smallest_one == check_down){
				copy_ptr(ptr_down,ptr);
					last_move=2;
					cout << "Intelligent choose move D up "/*= " << check_up << " left = " << check_left <<"down = " << check_down <<" right = " << check_right*/<< "\n";

		}
		else if(smallest_one == check_right){
					copy_ptr(ptr_right,ptr);
					last_move=3;
					cout << "Intelligent choose move R up "/*= " << check_up << " left = " << check_left <<"down = " << check_down <<" right = " << check_right*/<< "\n";

		}
		else if(smallest_one==check_left){
					copy_ptr(ptr_left,ptr);
					last_move=1;
					cout << "Intelligent choose move L up "/*= " << check_up << " left = " << check_left <<"down = " << check_down <<" right = " << check_right*/<< "\n";
		}


	return last_move;
}
int find_blank_coordinat_x(int ptr[][9],int line,int coloun){
	int i=0;
	int k=0;
	for(i=0;i<=line;i++){
		for(k=0;k<=coloun;k++){
			if(ptr[i][k]==97){
				return k ;
			}
		}
	}
}
int find_blank_coordinat_y(int ptr[][9],int line,int coloun){
	int i=0;
	int k=0;
	for(i=0;i<=line;i++){
		for(k=0;k<=coloun;k++){
			if(ptr[i][k]==97){
				return i ;
			}
		}
	}
}
void display(int ptr[][9],int line,int coloun){
	int i;
	int k;
	for(i=0;i<=line;i++){
		for(k=0;k<=coloun;k++){
			if(ptr[i][k]!=99 && ptr[i][k]!=95){
				if(ptr[i][k]==97)
					cout << "\t" ;
				else{
					if(ptr[i][k]<10)
						cout << "0" ;
					cout << "" << ptr[i][k] << "\t";
				}

			}

		}

		cout << "\n" ;
	}
}
int move_left(int ptr[][9],int line,int coloun){
	int blank_coordinat_x=find_blank_coordinat_x(ptr,line,coloun);
	int blank_coordinat_y=find_blank_coordinat_y(ptr,line,coloun);
	if(blank_coordinat_x==0 || ptr[blank_coordinat_y][blank_coordinat_x-1]==0 ){
		cout << "Something wrong !! left" ;
		return 99 ;
	}
	else{
		ptr[blank_coordinat_y][blank_coordinat_x]=ptr[blank_coordinat_y][blank_coordinat_x-1];
		ptr[blank_coordinat_y][blank_coordinat_x-1]=97;
	}

}
int move_right(int ptr[][9],int line,int coloun){
	int blank_coordinat_x=find_blank_coordinat_x(ptr,line,coloun);
	int blank_coordinat_y=find_blank_coordinat_y(ptr,line,coloun);
	if(blank_coordinat_x==coloun || ptr[blank_coordinat_y][blank_coordinat_x+1]==0){
		cout << "Something wrong !! right" ;
		return 99 ;
	}
	else{
		ptr[blank_coordinat_y][blank_coordinat_x]=ptr[blank_coordinat_y][blank_coordinat_x+1];
		ptr[blank_coordinat_y][blank_coordinat_x+1]=97;
	}
}
int move_up(int ptr[][9],int line,int coloun){
	int blank_coordinat_x=find_blank_coordinat_x(ptr,line,coloun);
	int blank_coordinat_y=find_blank_coordinat_y(ptr,line,coloun);
	if(blank_coordinat_y==0 || ptr[blank_coordinat_y-1][blank_coordinat_x]==0){
		cout << "Something Wrong !! up " ;
		return 99 ;
	}
	else{
		ptr[blank_coordinat_y][blank_coordinat_x]=ptr[blank_coordinat_y-1][blank_coordinat_x];
		ptr[blank_coordinat_y-1][blank_coordinat_x]=97;
	}
}
int move_down(int ptr[][9],int line,int coloun){
	int blank_coordinat_x=find_blank_coordinat_x(ptr,line,coloun);
	int blank_coordinat_y=find_blank_coordinat_y(ptr,line,coloun);
	if(blank_coordinat_y==line || ptr[blank_coordinat_y+1][blank_coordinat_x]==0){
		cout << "Something wrong !!down ";
		return 99;
	}
	else{
		ptr[blank_coordinat_y][blank_coordinat_x]=ptr[blank_coordinat_y+1][blank_coordinat_x];
		ptr[blank_coordinat_y+1][blank_coordinat_x]=97;
	}
}
void initializion(int ptr[][9],int size){
	int i=0;
	int k=0;
	for(i=0;i<size;i++){
		for(k=0;k<size;k++){
			ptr[i][k]=(i*size)+k+1;
		}
		for(k=k;k<9;k++){
			ptr[i][k]=99;
		}
	}
	ptr[size-1][size-1]=97;
	for(i=i;i<9;i++){
		for(k=0;k<9;k++){
			ptr[i][k]=99;
		}
	}
}
int find_the_same_line(int ptr[9][9],int ptr_2[9][9],int goal_ptr[9][9],int size){
	int i=0;
	int j=0;
	int m=0;
	int k=0;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			if(ptr[i][j]<size*(i+1) && ptr[i][j]>size*i){
				m++; // m countu artar
			}
		}
	}
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			if(ptr_2[i][j]<size*(i+1) && ptr_2[i][j]>size*i){
				k++; // m countu artar
			}
		}
	}
	if(m>k){
		return 1;
	}
	else {
		return 2 ;
	}

}
void upload_input(int ptr[9][9],  string name     ,int line ,int coloun){
  int i=0;
  int j=0;

  ofstream dosyaYaz(name);
  while(i<=line){
    while(j<=coloun){
			if(ptr[i][j]==97){
				dosyaYaz << "bb ";
			}
			else if(ptr[i][j]!=99){

				if(ptr[i][j]<10){
            dosyaYaz << "0" ;
        }
        dosyaYaz << ptr[i][j] << " " ;
      }
      j++;
    }
      dosyaYaz  << "\n" ;
      i++;
      j=0;
  }
}
void  Taking_input(int ptr[9][9],string name , int * line ,int * coloun  ){
  int i=0;
  int k=0;
  int l=0;
  int m=0;
  int row=0;
	int max=0;
  char transformation[3];
  string satir[9] ;
  ifstream infile(name);
  while(getline(infile,satir[i])){
// try   cout << satir[i] <<"\n" ;
    i++;
  }
  satir[++i]="\0";

  i=0;
  k=0;
  l=0;
//  cout << "row " << row <<"\n" ;
  do{
    while(satir[i][k]!='\n'  && satir[i][k]!='\0'){
			if(satir[i][k]=='b' && satir[i][k+1]=='b'){
					transformation[l++]='9';
					transformation[l++]='7';
			}
			else if(satir[i][k]=='b' && satir[i][k-1]=='b'){
					transformation[l++]='9';
					transformation[l++]='7';
			}
			else if(satir[i][k]==' ')
      {
				k++;
				if(satir[i][k]=='b' && satir[i][k+1]=='b'){
						transformation[l++]='9';
						transformation[l++]='7';
				}
			}

		//  cout << "First if " << satir[i][k] << "\n" ;
      transformation[l]=satir[i][k];
      l++;
      k++;
    //  cout << "Second if " << satir[i][k] << "\n" ;
      if(satir[i][k]==' '){
        transformation[l]='\0';
        l=0;
        k++;
      }
      else{
        transformation[l]=satir[i][k];
        k++;
        transformation[++l]='\0';
        l=0;
      }
      ptr[i][m]=atoi(transformation);
		//  cout << transformation << "\n" ;
    //  cout << ptr[i][m] << "\n" ;
      m++;
			if(m>max && ptr[i][m]!=99){
				max=m;
			}
      transformation[0]='\0';
    }
		(*coloun)=max-1;
		if(m<9){
			ptr[i][m]=95;
			m++;
		}
 		while(m<9){
      ptr[i][m]=99;
      m++;
    }
    i++;
    k=0;
    m=0;
    l=0;
  }while(satir[i]!="\0") ;
	row=i;
	while(i<9){
		m=0;
		while(m<9){
			ptr[i][m]=99;
			m++;
		}
		i++;
	}
	(*line)=row-1;
}
void initial_goal(int goal_ptr[][9],int line,int coloun){
	int m=1;
	int i=0;
	int j;
	for(i=0;i<=line;i++){
		for(j=0;j<=coloun;j++){
			if(goal_ptr[i][j]!=99 && goal_ptr[i][j]!=95){
				if(goal_ptr[i][j]==0){
					goal_ptr[i][j]=0;
				}
				else{
					goal_ptr[i][j]=m++;
				}
			}
		}
	}
}
