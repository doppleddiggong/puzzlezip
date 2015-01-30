#ifndef __DEFINEDATA_H__
#define __DEFINEDATA_H__

// 기준 해상도
// 11시(0,0), 5시(800, 480)가 기준 좌표가 된다

#define DEFAULT_DISPLAY_WIDTH   800
#define DEFAULT_DISPLAY_HEIGHT  480

#define FONT_PATH "fonts/Marker Felt.ttf"

#define TOUCH_MOVED_OFFSET 15.0f
#define TOUCH_CANCEL_TAG   -1

#define CELL_SIZE 80

#define CELL_TYPE_WALL      0
#define CELL_TYPE_OPEN      1
#define CELL_TYPE_CHARACTER 2
#define CELL_TYPE_BALL      3
#define CELL_TYPE_MAX_NUM   4

#define NORMAL_IMAGE        0
#define PRESS_IMAGE         1
#define BUTTON_MAX_NUM      2

#define ERROR               -1

#endif // __DEFINEDATA_H__