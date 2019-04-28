#### Docker安装(CentOS7、 root权限下)

1. Docker要求CentOS内核需要高于3.10

   - 所以先查看内核版本

     ```shell
     $ uname -r
     ```

   - 如果内核版本不足

     [1]: https://blog.csdn.net/kikajack/article/details/79396793	"CentOS7内核更新"

2. 使用 `root` 权限登录 Centos。确保 yum 包更新到最新。

   ```shell
   $ yum update
   ```

3. 卸载旧版本(如果安装过旧版本的话)

   ```shell
   $ yum remove docker  docker-common docker-selinux docker-engine
   ```

4. 设置yum源

   ```shell
   $ yum-config-manager --add-repo https://download.docker.com/linux/centos/docker-ce.repo
   ```

5. 可以查看所有仓库中所有docker版本，并选择特定版本安装

   ```shell
   $ yum list docker-ce --showduplicates | sort -r
   ```

6. 安装docker

   ```shell
   $ sudo yum install docker-ce  #由于repo中默认只开启stable仓库，故这里安装的是最新稳定版17.12.0
   $ sudo yum install <FQPN>  # 例如：sudo yum install docker-ce-17.12.0.ce
   ```

7. 验证安装是否成功（Client和Server都启动才算成功）

   ```shell
   $ docker version
   Client:
    Version:           18.09.5
    API version:       1.39
    Go version:        go1.10.8
    Git commit:        e8ff056
    Built:             Thu Apr 11 04:43:34 2019
    OS/Arch:           linux/amd64
    Experimental:      false
   
   Server: Docker Engine - Community
    Engine:
     Version:          18.09.5
     API version:      1.39 (minimum version 1.12)
     Go version:       go1.10.8
     Git commit:       e8ff056
     Built:            Thu Apr 11 04:13:40 2019
     OS/Arch:          linux/amd64
     Experimental:     false
   ```

   

#### Docker使用

```shell

# 搜索镜像
docker search tomcat
# 拉取镜像
docker pull tomcat
# docker pull tomcat:tag 可以下载指定版本的镜像
# 删除一个镜像
docker rmi 镜像id
# 根据镜像启动容器
docker run --name mytomcat -d tomcat:latest
# docker ps  
查看运行中的容器
# 停止运行中的容器
docker stop  容器的id
# 查看所有的容器
docker ps -a
# 启动容器
docker start 容器id
# 删除一个容器
docker rm 容器id
# 启动一个做了端口映射的tomcat
[root@localhost ~]# docker run -d -p 8888:8080 tomcat
# -d：后台运行
# -p: 将主机的端口映射到容器的一个端口    主机端口:容器内部的端口
docker exec -it 38637ee72fc5 /bin/bash
# 管理docker内的mysql


```

