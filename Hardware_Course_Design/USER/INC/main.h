#include <stdio.h>  
#include <stdlib.h>  
#include <math.h>
#include "stm32f10x.h"
#include "core_cm3.h"
#include "common.h"


#include "oledfont.h" 
#include "oled.h"
#include "usart.h"
#include "sys.h"

//自定义取最大或最小函数，oled.c中需要用到
#define MAX(a,b)   ((a>b)?a:b)
#define MIN(a,b)   ((a<b)?a:b)

