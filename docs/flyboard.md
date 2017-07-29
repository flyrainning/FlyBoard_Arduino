# FlyBoard_Arduino



<!-- TOC depthFrom:1 depthTo:6 withLinks:1 updateOnSave:1 orderedList:0 -->

- [FlyBoard_Arduino](#flyboardarduino)
	- [主要功能](#主要功能)
	- [内置模块](#内置模块)
		- [System](#system)
			- [STL](#stl)
			- [ArduinoJson](#arduinojson)
			- [Timer](#timer)
			- [[FBSettings](System/FBSettings.md)](#fbsettingssystemfbsettingsmd)
			- [Debug](#debug)
			- [algorithm](#algorithm)
		- [FBSerial](#fbserial)
		- [FBCmd](#fbcmd)
		- [Device](#device)
			- [GPIO](#gpio)
		- [FBCloud](#fbcloud)

<!-- /TOC -->



## 主要功能



## 内置模块


### System

系统基本功能

#### STL

提供c++标准STL的部分功能支持，例如vector,map


#### ArduinoJson

直接引入ArduinoJson库，用于处理json

#### Timer

对定时功能的再次封装，提供更方便的计数，计时执行的功能

#### [FBSettings](System/FBSettings.md)

提供统一的配置管理功能，通过结构体封装配置功能，支持插件扩展

#### Debug

Debug辅助功能

#### algorithm

常用算法相关类，例如CRC16，CRC32等

### FBSerial

提供统一串口类，支持HardwareSerial，SoftwareSerial，AltSoftSerial

### FBCmd

提供一个命令行交互和通讯工具，可扩展命令和回调功能，支持插件扩展

### Device

基本设备功能的抽象

#### GPIO

提供IO基本操作

### FBCloud

提供云连接基本功能
