//
//  Joystick.cpp
//  JoyStickEx
//
//  Created by Jaewhan Lee on 13. 6. 5..
//  Copyright www.cocos2d-x.kr 2013년. All rights reserved.
//

#include "Joystick.h"
#include "CustomMath.h"

#define JOYSTICK_OFFSET_X 5.0f
#define JOYSTICK_OFFSET_Y 5.0f

#define JOYSTICK_RADIUS 64.0f
#define THUMB_RADIUS 26.0f

Joystick* Joystick::create( JoystickDelegate* pDelegate )
{
    Joystick *pRet = new Joystick();
    if (pRet && pRet->init( pDelegate ) )
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

Joystick::Joystick()
{
    m_vecVelocity   = Vec2::ZERO;
    m_vecCenter     = Vec2(JOYSTICK_RADIUS + JOYSTICK_OFFSET_X, JOYSTICK_RADIUS + JOYSTICK_OFFSET_Y);
}

Joystick::~Joystick()
{
}

bool Joystick::init( JoystickDelegate* pDelegate )
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->initTouchEvent();
    this->initJoystickSprite();
    
    m_pDelegate = pDelegate;

    return true;
}

void Joystick::initTouchEvent()
{
    EventListenerTouchOneByOne* pEventListener = EventListenerTouchOneByOne::create();
    pEventListener->onTouchBegan = CC_CALLBACK_2(Joystick::onTouchBegan, this);
    pEventListener->onTouchMoved = CC_CALLBACK_2(Joystick::onTouchMoved, this);
    pEventListener->onTouchEnded = CC_CALLBACK_2(Joystick::onTouchEnded, this);
    pEventListener->onTouchCancelled = CC_CALLBACK_2(Joystick::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(pEventListener, this);
}

void Joystick::initJoystickSprite()
{
    m_pJoystickBg = Sprite::create("Game/joystick_background.png");
    m_pJoystickBg->setPosition(m_vecCenter);
    this->addChild( m_pJoystickBg );
    
    m_pJoystickthumb = Sprite::create("Game/joystick_thumb.png");
    m_pJoystickthumb->setPosition(m_vecCenter);
    this->addChild( m_pJoystickthumb, 1 );
}

void Joystick::updateVelocity(Vec2 point)
{
    // calculate Angle and length
    float fX = point.x - m_vecCenter.x;
    float fY = point.y - m_vecCenter.y;
    
    float distance = sqrt(fX*fX + fY*fY);
    float angle = atan2(fY,fX); // in radians
    
    if( distance > JOYSTICK_RADIUS )
    {
        fX = cos(angle) * JOYSTICK_RADIUS;
        fY = sin(angle) * JOYSTICK_RADIUS;
    }
    
    m_vecVelocity = Vec2(fX/JOYSTICK_RADIUS, fY/JOYSTICK_RADIUS);
    m_pDelegate->updateJoyStickVelocity(m_vecVelocity);
    
    if( distance > THUMB_RADIUS )
    {
        point.x = m_vecCenter.x + cos(angle) * THUMB_RADIUS;
        point.y = m_vecCenter.y + sin(angle) * THUMB_RADIUS;
    }
    
    m_pJoystickthumb->setPosition(point);
}

void Joystick::resetJoystick()
{
    this->updateVelocity(m_vecCenter);
}

bool Joystick::handleLastTouch()
{
    bool bWasPressed = m_bIsPressed;
    if (bWasPressed)
    {
        this->resetJoystick();
        m_bIsPressed = false;
    }
    return (bWasPressed ? true : false);
}

bool Joystick::onTouchBegan( Touch* pTouch, Event* pEvent )
{
    Vec2 touchPoint = pTouch->getLocation();
    
    if ( isPointInCircle(touchPoint, m_vecCenter, JOYSTICK_RADIUS))
    {
        m_bIsPressed = true;
        this->updateVelocity(touchPoint);
    }
    
    return true;
}

void Joystick::onTouchMoved( Touch* pTouch, Event* pEvent )
{
    if (m_bIsPressed)
    {
        Vec2 touchPoint = pTouch->getLocation();

        this->updateVelocity(touchPoint);
    }
}

void Joystick::onTouchEnded(Touch* pTouch, Event* pEvent)
{
    this->handleLastTouch();
}

void Joystick::onTouchCancelled(Touch* pTouch, Event* pEvent)
{
    this->handleLastTouch();
}


