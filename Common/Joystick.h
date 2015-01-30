//
//  Joystick.h
//  JoyStickEx
//
//  Created by Jaewhan Lee on 13. 6. 5..
//  Copyright www.cocos2d-x.kr 2013년. All rights reserved.
//

#ifndef __JoyStickEx__Joystick__
#define __JoyStickEx__Joystick__

#include "cocos2d.h"
USING_NS_CC;

class JoystickDelegate
{
public:
    virtual void updateJoyStickVelocity( Vec2 vecJoyStickVelocity ) {};
};

class Joystick : public Layer
{
public:
    Joystick();
    virtual ~Joystick();
    
    virtual bool init( JoystickDelegate* pDelegate );
    static Joystick* create( JoystickDelegate* pDelegate );

private:
    JoystickDelegate*   m_pDelegate;

    bool                m_bIsPressed;
    Vec2                m_vecVelocity;
    Vec2                m_vecCenter;

    Sprite*             m_pJoystickBg;
    Sprite*             m_pJoystickthumb;
    
    void                initTouchEvent();
    void                initJoystickSprite();
    
    void                updateVelocity(Vec2 point);
    void                resetJoystick();
    bool                handleLastTouch();

    bool                onTouchBegan(Touch* pTouch, Event* pEvent);
    void                onTouchMoved(Touch* pTouch, Event* pEvent);
    void                onTouchEnded(Touch* pTouch, Event* pEvent);
    void                onTouchCancelled(Touch* pTouch, Event* pEvent);
};

#endif
