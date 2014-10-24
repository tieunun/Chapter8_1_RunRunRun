#ifndef _ANIMATION_UTIL_
#define _ANIMATION_UTIL_

#include "cocos2d.h"
USING_NS_CC;

class AnimationUtil
{
public:

	//�����ļ�����ǰ׺������������
	static Animation* createWithSingleFrameName(const char* name,float delay,int iLoops);

	//�����ļ�����ǰ׺������������ָ������ͼƬ����
	static Animation* createWithFrameNameAndNum(const char* name,int iNum,float delay,int iLoops);

private:

};



#endif