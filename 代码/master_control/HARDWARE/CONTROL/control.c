#include "control.h"
//¿ØÖÆ
//¼ÙÉèÊÕµ½µÄÂ·¾¶Îª£º
/*
A:Ç°½ø
L:×ó×ª
R:ÓÒ×ª
S:Í£Ö¹
*/

//·½ÏòµÄ×ª»»
void change_direction(char* current,char* follow){
/*
1.ÏÈ»ñÈ¡µ±Ç°µÄÂ·¾¶·½Ïò
2.ÔÚ»ñÈ¡ÏÂÒ»´ÎµÄÂ·¾¶·½Ïò
3.ºÍÏÂÒ»´ÎµÄÂ·¾¶·½Ïò½øĞĞ±È¶Ô
*/
	//µ±Ç°µÄĞÅÏ¢Îª£ºover	Ê±£¬¹Ø±Õ×ÜÖĞ¶Ï£¬³µÍ£Ö¹
	if(strcmp(current,"over") == 0){
		__set_PRIMASK(1);//¹Ø×ÜÖĞ¶Ï
		moto_stop();
	}
	//µ±Ç°µÄĞÅÏ¢µÈÓÚÏÂÒ»´ÎĞÅÏ¢£¬
	else if(strcmp(current,follow) == 0){
		moto_advance();
	}
	else{
		//µ±Ç°³µÍ·³¯ÉÏ
		if(strcmp(current,"up") == 0){			//³µÍ·³¯ÉÏ
			//ÏÂÒ»¸ö
			if(strcmp(follow,"left") == 0){		//ÏÂÒ»¸ö³µÍ·³¯×ó
				moto_left();			//×ó×ª
			}
			else if(strcmp(follow,"right") == 0){		//ÏÂÒ»¸ö³µÍ·³¯ÓÒ
				moto_right();			//ÓÒ×ª
			}
			else{				//ÏÂÒ»¸ö³µÍ`·³¬ÉÏ »òÕßÏÂ
				moto_advance();
			}
		}
		//µ±Ç°³µÍ·³¯ÏÂ
		else if(strcmp(current,"down") == 0){
			//ÏÂÒ»´Î³µÍ·µÄ³¯Ïò
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
		//µ±Ç°µÄ³µÍ·³¯×ó
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
		//µ±Ç°³µÍ·³¬ÓÒ
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


//·´À¡µÄĞ§¹û
/*
Í£Ö¹£ºP
Ö±ĞĞ£ºA
×ó×ª£ºL
ÓÒ×ª: R
*/
char* direction(char* current,char* follow){
	char* ret;
/*
1.ÏÈ»ñÈ¡µ±Ç°µÄÂ·¾¶·½Ïò
2.ÔÚ»ñÈ¡ÏÂÒ»´ÎµÄÂ·¾¶·½Ïò
3.ºÍÏÂÒ»´ÎµÄÂ·¾¶·½Ïò½øĞĞ±È¶Ô
*/
	//µ±Ç°µÄĞÅÏ¢Îª£ºover	Ê±£¬¹Ø±Õ×ÜÖĞ¶Ï£¬³µÍ£Ö¹
	if(strcmp(follow,"over") == 0){
		__set_PRIMASK(1);//¹Ø×ÜÖĞ¶Ï
		moto_stop();
		ret = "P";
	}
	//µ±Ç°µÄĞÅÏ¢µÈÓÚÏÂÒ»´ÎĞÅÏ¢£¬
	else if(strcmp(current,follow) == 0){
		moto_advance();
		ret = "A";
	}
	else{
		//µ±Ç°³µÍ·³¯ÉÏ
		if(strcmp(current,"up") == 0){			//³µÍ·³¯ÉÏ
			//ÏÂÒ»¸ö
			if(strcmp(follow,"left") == 0){		//ÏÂÒ»¸ö³µÍ·³¯×ó
				moto_left();			//×ó×ª
				ret = "L";
			}
			else if(strcmp(follow,"right") == 0){		//ÏÂÒ»¸ö³µÍ·³¯ÓÒ
				moto_right();			//ÓÒ×ª
				ret = "R";
			}
			else{				//ÏÂÒ»¸ö³µÍ`·³¬É?»òÕßÏÂ
				moto_advance();
				ret = "A";
			}
		}
		//µ±Ç°³µÍ·³¯ÏÂ
		else if(strcmp(current,"down") == 0){
			//ÏÂÒ»´Î³µÍ·µÄ³¯Ïò
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
		//µ±Ç°µÄ³µÍ·³¯×ó
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
		//µ±Ç°³µÍ·³¬ÓÒ
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




