#include "control.h"
//����
//�����յ���·��Ϊ��
/*
A:ǰ��
L:��ת
R:��ת
S:ֹͣ
*/

//�����ת��
void change_direction(char* current,char* follow){
/*
1.�Ȼ�ȡ��ǰ��·������
2.�ڻ�ȡ��һ�ε�·������
3.����һ�ε�·��������бȶ�
*/
	//��ǰ����ϢΪ��over	ʱ���ر����жϣ���ֹͣ
	if(strcmp(current,"over") == 0){
		__set_PRIMASK(1);//�����ж�
		moto_stop();
	}
	//��ǰ����Ϣ������һ����Ϣ��
	else if(strcmp(current,follow) == 0){
		moto_advance();
	}
	else{
		//��ǰ��ͷ����
		if(strcmp(current,"up") == 0){			//��ͷ����
			//��һ��
			if(strcmp(follow,"left") == 0){		//��һ����ͷ����
				moto_left();			//��ת
			}
			else if(strcmp(follow,"right") == 0){		//��һ����ͷ����
				moto_right();			//��ת
			}
			else{				//��һ�����`����� ������
				moto_advance();
			}
		}
		//��ǰ��ͷ����
		else if(strcmp(current,"down") == 0){
			//��һ�γ�ͷ�ĳ���
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
		//��ǰ�ĳ�ͷ����
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
		//��ǰ��ͷ����
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


//������Ч��
/*
ֹͣ��P
ֱ�У�A
��ת��L
��ת: R
*/
char* direction(char* current,char* follow){
	char* ret;
/*
1.�Ȼ�ȡ��ǰ��·������
2.�ڻ�ȡ��һ�ε�·������
3.����һ�ε�·��������бȶ�
*/
	//��ǰ����ϢΪ��over	ʱ���ر����жϣ���ֹͣ
	if(strcmp(follow,"over") == 0){
		__set_PRIMASK(1);//�����ж�
		moto_stop();
		ret = "P";
	}
	//��ǰ����Ϣ������һ����Ϣ��
	else if(strcmp(current,follow) == 0){
		moto_advance();
		ret = "A";
	}
	else{
		//��ǰ��ͷ����
		if(strcmp(current,"up") == 0){			//��ͷ����
			//��һ��
			if(strcmp(follow,"left") == 0){		//��һ����ͷ����
				moto_left();			//��ת
				ret = "L";
			}
			else if(strcmp(follow,"right") == 0){		//��һ����ͷ����
				moto_right();			//��ת
				ret = "R";
			}
			else{				//��һ�����`����?������
				moto_advance();
				ret = "A";
			}
		}
		//��ǰ��ͷ����
		else if(strcmp(current,"down") == 0){
			//��һ�γ�ͷ�ĳ���
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
		//��ǰ�ĳ�ͷ����
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
		//��ǰ��ͷ����
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




