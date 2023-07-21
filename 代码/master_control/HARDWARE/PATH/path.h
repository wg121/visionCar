#ifndef __PATH_H
#define __PATH_H
#include "sys.h"
#include "stdlib.h"
#include "string.h"
/*
·��ģ��

*/

#include "map.h"



/* ��    �ƣ�pathInit
 * ��   �ã���ʼ��
 * ��   ����start�����	end���յ㡣
 * ����ֵ���ַ��� up��down��left��right��over
 *	 	   �������Ҵ���������ƶ����ϱ��ķ�λ�����Գ�ͷΪ�ο�ϵ
 *		   over�������
 * ʹ�ó�����openmv��⵽·�ڣ�ִ��һ��getNextCmd�õ�һ��command
 *			ÿ���л�����յ㶼��Ҫִ�� init
 */
void pathInit(char *start,char *end);


/****************************************************
 * ��    �ƣ�getNextCmd
 * ��   �ã��õ���һ��·��Ӧ���ߵķ���
 * ����ֵ���ַ��� up��down��left��right��over
 *	 	   �������Ҵ���������ƶ����ϱ��ķ�λ�����Գ�ͷΪ�ο�ϵ
 *		   over�������
 * ʹ�ó�����openmv��⵽·�ڣ�ִ��һ��getNextCmd�õ�һ��command
 */
char *getNextCmd(void);

/****************************************************
 * ��    �ƣ�getNowRoad
 * ��   �ã�ÿִ��һ�Σ������ǰ�ص�����
 * ����ֵ���ַ��� �ص�����
 *	 	   cross1	A
 * ʹ�ó�����openmv��⵽·�ڣ�ִ��һ��getPassedRoad�õ���ǰ·��
 */
char *getNowSite(void);


/****************************************************
 * ��    �ƣ�getNextSite
 * ��   �ã�ÿִ��һ�Σ����Ҫ�����·��
 * ����ֵ���ַ��� �ص�����
 *	 	   cross1	A
 * ʹ�ó�����openmv��⵽·�ڣ�ִ��һ��getNextSite�õ�Ҫ�����·��
 */
char *getNextSite(void);

/****************************************************
 * ��    �ƣ�getNextDistance
 * ��   �ã�ÿִ��һ�Σ��������һ��·������
 * ����ֵ��int ����һ��·������
 *
 * ʹ�ó�����openmv��⵽·�ڣ�ִ��һ�εõ���ǰ����һ��·�ڵľ���
 */
int getNextDistance(void);







#endif
