#include "control.h"
//控制
//假设收到的路径为：
/*
A:前进
L:左转
R:右转
S:停止
*/

//方向的转换
void change_direction(char* current,char* follow){
/*
1.先获取当前的路径方向
2.在获取下一次的路径方向
3.和下一次的路径方向进行比对
*/
	//当前的信息为：over	时，关闭总中断，车停止
	if(strcmp(current,"over") == 0){
		__set_PRIMASK(1);//关总中断
		moto_stop();
	}
	//当前的信息等于下一次信息，
	else if(strcmp(current,follow) == 0){
		moto_advance();
	}
	else{
		//当前车头朝上
		if(strcmp(current,"up") == 0){			//车头朝上
			//下一个
			if(strcmp(follow,"left") == 0){		//下一个车头朝左
				moto_left();			//左转
			}
			else if(strcmp(follow,"right") == 0){		//下一个车头朝右
				moto_right();			//右转
			}
			else{				//下一个车蚡烦� 或者下
				moto_advance();
			}
		}
		//当前车头朝下
		else if(strcmp(current,"down") == 0){
			//下一次车头的朝向
			if(strcmp(follow,"left") == 0){
				moto_right();
			}
			else if(strcmp(follow,"right") == 0){
				moto_left();
			}
			else{
				moto_advance();
			}
		}
		//当前的车头朝左
		else if(strcmp(current,"left") == 0){
			if(strcmp(follow,"up") == 0){
				moto_right();
			}
			else if(strcmp(follow,"down")){
				moto_right();
			}
			else{
				moto_advance();
			}
		}
		//当前车头超右
		else if(strcmp(current,"right") == 0){
			if(strcmp(follow,"up") == 0){
				moto_left();
			}
			else if(strcmp(follow,"down") == 0){
				moto_right();
			}
			else{
				moto_advance();
			}
		}
	}
}


//反馈的效果
/*
停止：P
直行：A
左转：L
右转: R
*/
char* direction(char* current,char* follow){
	char* ret;
/*
1.先获取当前的路径方向
2.在获取下一次的路径方向
3.和下一次的路径方向进行比对
*/
	//当前的信息为：over	时，关闭总中断，车停止
	if(strcmp(follow,"over") == 0){
		__set_PRIMASK(1);//关总中断
		moto_stop();
		ret = "P";
	}
	//当前的信息等于下一次信息，
	else if(strcmp(current,follow) == 0){
		moto_advance();
		ret = "A";
	}
	else{
		//当前车头朝上
		if(strcmp(current,"up") == 0){			//车头朝上
			//下一个
			if(strcmp(follow,"left") == 0){		//下一个车头朝左
				moto_left();			//左转
				ret = "L";
			}
			else if(strcmp(follow,"right") == 0){		//下一个车头朝右
				moto_right();			//右转
				ret = "R";
			}
			else{				//下一个车蚡烦?或者下
				moto_advance();
				ret = "A";
			}
		}
		//当前车头朝下
		else if(strcmp(current,"down") == 0){
			//下一次车头的朝向
			if(strcmp(follow,"left") == 0){
				moto_right();
				ret  = "R";
			}
			else if(strcmp(follow,"right") == 0){
				moto_left();
				ret = "L";
			}
			else{
				moto_advance();
				ret = "A"; 
			}
		}
		//当前的车头朝左
		else if(strcmp(current,"left") == 0){
			if(strcmp(follow,"up") == 0){
				moto_right();
				ret = "R";
			}
			else if(strcmp(follow,"down")){
				moto_left();
				ret = "L";
			}
			else{
				moto_advance();
				ret = "A";
			}
		}
		//当前车头超右
		else if(strcmp(current,"right") == 0){
			if(strcmp(follow,"up") == 0){
				moto_left();
				ret = "L";
			}
			else if(strcmp(follow,"down") == 0){
				moto_right();
				ret = "R";
			}
			else{
				moto_advance();
				ret = "A";
			}
		}
	}
	return ret;
}




