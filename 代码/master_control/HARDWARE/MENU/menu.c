#include "menu.h"

void showtitle(void){
	//�Ӿ�����С��
	//��һ�б�����ʾ
	OLED_ShowChinese(16,0,0,16,1);
	OLED_ShowChinese(32,0,1,16,1);
	OLED_ShowChinese(48,0,2,16,1);
	OLED_ShowChinese(64,0,3,16,1);
	OLED_ShowChinese(80,0,4,16,1);
	OLED_ShowChinese(96,0,5,16,1);
	
	//ģʽ:     (--ǰ�������ˣ�ֹͣ����ת����ת)
	OLED_ShowChinese(0,16,6,16,1);
	OLED_ShowChinese(16,16,7,16,1);
	OLED_ShowString(24,16,":",16,1);

	//��ǰ(NOW)����һ��(NEXT)
	//OLED_ShowString(0,48,"NOW:",16,1);
	//OLED_ShowString(56,48,"NEXT:",16,1);
	
	OLED_Refresh();		//ˢ��oled
}
