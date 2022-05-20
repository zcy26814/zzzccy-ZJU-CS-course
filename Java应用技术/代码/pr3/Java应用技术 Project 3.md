# Java应用技术 Project 3

## Web   周承扬_3190102371    *Date: 2021-12-1*4

### 第一节: 简介

本工程目的实现一个多客户端的纯文本聊天服务器，能同时接受多个客户端的连接，并将任意一个客户端发送的文本向所有客户端（包括发送方）转发。

### 第二节: 核心程序介绍

程序分为WebClient和WebServer两部分，分别处理客户端与共享服务器的内容。

WebClient.java主要由

```java
class ClientSendThread extends Thread
class ClientReceiveThread extends Thread
```

两个内部类组成，分别用来处理客户端关于信息的传输与接收；

WebServer.java主要负责起到服务器接收客户端发送信息并将其发送给所有客户端的作用。

### 第三节: 成果展示

以下图为例进行介绍：

![img](file:///C:\Users\clearlove-champion7\Documents\Tencent Files\1352982417\Image\C2C\NE1ERHHVUFQ10A27BJ]HMUG.png)

首先运行WebServer来开启服务器；

接着我们分别打开三个客户端Client 1~3；

接着我们分别从Client 1中输入“1234:”， Client 2中输入“5678”，Client 3中输入“91011”；

然后可以发现所有客户端1-3都收到了发出的信息；

接着关掉Client 3；

接着再在Client 1中输入“QAQ”，Client 2中输入“QWQ”；

于是只有客户端1-2接收到了。
