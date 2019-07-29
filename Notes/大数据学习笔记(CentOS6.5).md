# 大数据学习笔记(CentOS6.5)

## 静态IP设置

1. vi /etc/sysconfig/network-scripts/ifcfg-eth0 

```shell
#驱动名称
DEVICE=eth0
#MAC地址
HWADDR=00:0C:29:60:68:4B
TYPE=Ethernet
UUID=70982bd8-d9d9-471e-8476-ce8e9cd0861a
#是否开机自启
ONBOOT=yes
NM_CONTROLLED=yes
#静态ip设置
BOOTPROTO=static
#配置静态ip地址
IPADDR=192.168.141.103
#配置网关地址
GATEWAY=192.168.141.2
#配置DNS
DNS1=192.168.141.2

```

2. service network restart

### 遇到的问题

在克隆虚拟机后，照这样设置完静态ip报错:

```shell
弹出界面 eth0： 错误：没有找到合适的设备：没有找到可用于连接 'eth0' 的设备。
```

解决办法：

​	通过ifconfig命令得以下信息

```shell
eth1      Link encap:Ethernet  HWaddr 00:0C:29:A3:12:5E  
          inet addr:192.168.141.168  Bcast:192.168.141.255  Mask:255.255.255.0
          inet6 addr: fe80::20c:29ff:fea3:125e/64 Scope:Link
          UP BROADCAST RUNNING MULTICAST  MTU:1500  Metric:1
          RX packets:70 errors:0 dropped:0 overruns:0 frame:0
          TX packets:62 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:9190 (8.9 KiB)  TX bytes:8894 (8.6 KiB)
          Interrupt:19 Base address:0x2000 
```

从中获取驱动名称（eth1）和HWaddr（MAC地址）

修改配置文件 vi /etc/sysconfig/network-scripts/ifcfg-eth0 以下部分

```shell
DEVICE=eth1
HWADDR=00:0C:29:A3:12:5E
```

再重启network服务即可