# 温湿度检测多功能开发模块

## 元器件清单

1. STM32F103C8T6单片机    
<img src="./imgs/STM32F103C8T6单片机.png" width="60%">  
2. LED灯   
<img src="./imgs/LED灯.png" width="40%">         
3. 按键   
<img src="./imgs/按键.png" width="40%">
4. 温湿度模块（AHT20）            
<img src="./imgs/AHT20.png" width="40%">
5. OLED屏幕（4pin+ssd1305）      
<img src="./imgs/OLED屏幕.png" width="40%">
6. BLE低功耗蓝牙（BT24）    
<img src="./imgs/蓝牙.png" width="50%">
7. 串口模块（USB to TTL）       
<img src="./imgs/串口.png" width="50%">
8. ST-LINK V2下载器        
<img src="./imgs/STLINK.png" width="50%">
9. 若干杜邦线（公对母）+ 一块面包板 

## 演示视频
<video width="320*2" height="240*2" controls>
  <source src="./video.mp4" type="video/mp4">
</video>


## 功能

1. 温湿度检测
2. 时钟
3. 计时器
4. 作者信息
* LED灯+按键
> LED: 呼吸灯   

> 按键1(PA4)：功能的切换/退出   

> 按键2(PA7): 功能的确定/使用   

## 代码逻辑

<img src="./imgs/运行逻辑.png" width="80%">

<img src="./imgs/中断.png" width="80%">


