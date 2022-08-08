#include <REGX52.H>

unsigned char Key_Pushed;

/**
  * @brief 返回当前时刻按键值，0表示没按下，1-4表示独立按键
  * @param 无
  * @retval 按键值
  */
unsigned char Key_GetState()
{
	unsigned char KeyNum=0;
	if(P1_0==0) KeyNum=1;
	if(P1_1==0) KeyNum=2;
	if(P1_2==0) KeyNum=3;
	if(P1_3==0) KeyNum=4;
	return KeyNum;
}

/**
  * @brief 定时器监听程序，每隔20ms检测按键状态，边沿触发模式
  * @param 无
  * @retval 无
  */
void Key_Loop()
{
	static unsigned char LastState, CurrentState;	
	LastState=CurrentState;
	CurrentState=Key_GetState();
	if(LastState==1 && CurrentState==0) {Key_Pushed=1;}	// 如果20ms前为1，20ms后为0，表示按下1并松手的过程
	if(LastState==2 && CurrentState==0) {Key_Pushed=2;}
	if(LastState==3 && CurrentState==0) {Key_Pushed=3;}
	if(LastState==4 && CurrentState==0) {Key_Pushed=4;}
	// 如果条件改成 LastState==0 && CurrentState==4 就可以实现下降沿触发的效果了
}

/**
	* @brief 通过定时器方式判断独立键盘按键值，左，上，下，右分别返回1，2，3，4
  * @param 无
  * @retval 键位值
  */
unsigned char Key()
{
	unsigned char Temp=0;
	Temp=Key_Pushed;
	Key_Pushed=0;
	return Temp;
}


