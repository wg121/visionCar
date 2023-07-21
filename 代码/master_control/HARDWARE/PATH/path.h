#ifndef __PATH_H
#define __PATH_H
#include "sys.h"
#include "stdlib.h"
#include "string.h"
/*
路径模块

*/

#include "map.h"



/* 名    称：pathInit
 * 作   用：初始化
 * 参   数：start：起点	end：终点。
 * 返回值：字符串 up、down、left、right、over
 *	 	   上下左右代表的是类似东西南北的方位，不以车头为参考系
 *		   over代表结束
 * 使用场景：openmv检测到路口，执行一次getNextCmd得到一个command
 *			每次切换起点终点都需要执行 init
 */
void pathInit(char *start,char *end);


/****************************************************
 * 名    称：getNextCmd
 * 作   用：得到下一个路口应该走的方向
 * 返回值：字符串 up、down、left、right、over
 *	 	   上下左右代表的是类似东西南北的方位，不以车头为参考系
 *		   over代表结束
 * 使用场景：openmv检测到路口，执行一次getNextCmd得到一个command
 */
char *getNextCmd(void);

/****************************************************
 * 名    称：getNowRoad
 * 作   用：每执行一次，输出当前地点名称
 * 返回值：字符串 地点名称
 *	 	   cross1	A
 * 使用场景：openmv检测到路口，执行一次getPassedRoad得到当前路口
 */
char *getNowSite(void);


/****************************************************
 * 名    称：getNextSite
 * 作   用：每执行一次，输出要到达的路径
 * 返回值：字符串 地点名称
 *	 	   cross1	A
 * 使用场景：openmv检测到路口，执行一次getNextSite得到要到达的路口
 */
char *getNextSite(void);

/****************************************************
 * 名    称：getNextDistance
 * 作   用：每执行一次，输出到下一个路径距离
 * 返回值：int 到下一个路径距离
 *
 * 使用场景：openmv检测到路口，执行一次得到当前到下一个路口的距离
 */
int getNextDistance(void);







#endif
