# Log4j配置文件书写规则

## 示例：

```properties
# Global logging configuration
log4j.rootLogger=INFO, stdout, file ,E
# MyBatis logging configuration...
log4j.logger.com.bank.system=DEBUG
# Console output...
log4j.appender.stdout=org.apache.log4j.ConsoleAppender
log4j.appender.stdout.layout=org.apache.log4j.PatternLayout
log4j.appender.stdout.layout.ConversionPattern=%5p [%t] - %m%n

# root日志输出到文件
log4j.appender.file=org.apache.log4j.DailyRollingFileAppender
log4j.appender.file.File=logs/springboot-log4j-all.log
log4j.appender.file.DatePattern='.'yyyy-MM-dd
log4j.appender.file.layout=org.apache.log4j.PatternLayout
log4j.appender.file.layout.ConversionPattern=%d{yyyy-MM-dd HH:mm:ss,SSS} %5p %c{1}:%L - %m%n

# error日志输出到文件
log4j.appender.E=org.apache.log4j.DailyRollingFileAppender
log4j.appender.E.file=logs/springboot-log4j-error.log
log4j.appender.E.DatePattern='.'yyyy-MM-dd
log4j.appender.E.Threshold = ERROR
log4j.appender.E.layout=org.apache.log4j.PatternLayout
log4j.appender.E.layout.ConversionPattern=%d{yyyy-MM-dd HH:mm:ss,SSS} %5p %c{1}:%L - %m%n
```

## 规则

## rootLogger

```properties
log4j.rootLogger = level,appenderName1,appenderName2, .....
```

- level:

  - 这里的level是指输出的日志的级别。log4建议只使用四个级别优先级从高到低分别是ERROR、WARN、INFO、DEBUG。

    如果我们这样写

  ```properties
  log4j.rootLogger=INFO, stdout, file ,E
  ```

  **就指的最低输出INFO信息。而DEBUG就被我们放弃了。** 

- appenderName  是我们自定义的日志输出目的地。

  比如我们想在控制台输出   又想把所有error信息存在某个文件中。  那么我们可以自定义两个appenderName 。这个名字随意，但是最好见名知意。

  ```properties
  #第一行配置目的地   ConsoleAppender将信息输出到控制台
  log4j.appender.stdout=org.apache.log4j.ConsoleAppender 
  #日志信息格式
  log4j.appender.stdout.layout=org.apache.log4j.PatternLayout
  #指定怎样格式化指定的消息。 ConversionPattern是以C语言的print函数的输出格式格式化的
  # 所有下面的意思是 
  # %5p   以5个字符的宽度输出日子级别信息  
  # [%t]  线程名
  # %m  然后输出代码中指定的消息,产生的日志具体信息 
  # %n  还有换一行
  log4j.appender.stdout.layout.ConversionPattern=%5p [%t] - %m%n
  ```

## 目的地 appender

1. ```properties
   org.apache.log4j.ConsoleAppender（控制台）
   org.apache.log4j.FileAppender（文件）
   org.apache.log4j.DailyRollingFileAppender（每天产生一个日志文件）
   org.apache.log4j.RollingFileAppender（文件大小到达指定尺寸的时候产生一个新的文件）
   org.apache.log4j.WriterAppender（将日志信息以流格式发送到任意指定的地方）
   ```

2. ##### ConsoleAppender (输出到控制台)

   - Threshold=WARN：指定日志消息的输出最低层次。 
   - ImmediateFlush=true：默认值是true,意谓着所有的消息都会被立即输出。 
   - Target=System.err：默认情况下是：System.out,指定输出控制台

3. ##### FileAppender

   - Threshold=WARN：指定日志消息的输出最低层次。 
   - ImmediateFlush=true：默认值是true,意谓着所有的消息都会被立即输出。 
   - File=mylog.txt：指定消息输出到mylog.txt文件。 

4. ##### DailyRollingFileAppender

   - Threshold=WARN：指定日志消息的输出最低层次。 

   - ImmediateFlush=true：默认值是true,意谓着所有的消息都会被立即输出。 

   - File=mylog.txt：指定消息输出到mylog.txt文件。 

   - Append=false：默认值是true,即将消息增加到指定文件中，false指将消息覆盖指定的文件内容。 

   - DatePattern=”.”yyyy-ww:每周滚动一次文件，即每周产生一个新的文件。 
     当然也可以指定按月、周、天、时和分。即对应的格式如下： 
     1)”.”yyyy-MM: 每月 
     2)”.”yyyy-ww: 每周 
     3)”.”yyyy-MM-dd: 每天 
     4)”.”yyyy-MM-dd-a: 每天两次 
     5)”.”yyyy-MM-dd-HH: 每小时 

     6)”.”yyyy-MM-dd-HH-mm: 每分钟

5. ##### RollingFileAppender

   - Threshold=WARN：指定日志消息的输出最低层次。 

   - ImmediateFlush=true：默认值是true,意谓着所有的消息都会被立即输出。 

   - File=mylog.txt：指定消息输出到mylog.txt文件。 

   - Append=false：默认值是true,即将消息增加到指定文件中，false指将消息覆盖指定的文件内容。 

   - MaxFileSize=100KB：后缀可以是KB, MB 或者是 GB. 在日志文件到达该大小时，将会自动滚动，即

     将原来的内容移到mylog.log.1文件。 

   - MaxBackupIndex=2：指定可以产生的滚动文件的最大数。

## 日志信息格式中几个符号所代表的含义

-X号: X信息输出时左对齐； 
%p: 输出日志信息优先级，即DEBUG，INFO，WARN，ERROR，FATAL, 
%d: 输出日志时间点的日期或时间，默认格式为ISO8601，也可以在其后指定格式， 
比如：%d{yyy MMM dd HH:mm:ss,SSS}，输出类似：2002年10月18日 22：10：28，921 
%r: 输出自应用启动到输出该log信息耗费的毫秒数 
%c: 输出日志信息所属的类目，通常就是所在类的全名 
%t: 输出产生该日志事件的线程名 
%l: 输出日志事件的发生位置，相当于%C.%M(%F:%L)的组合,包括类目名、发生的线程，以及行数。 
举例：Testlog4.main(TestLog4.java:10) 
%x: 输出和当前线程相关联的NDC(嵌套诊断环境)，尤其用到像java servlets这样的多客户多线程的应用中。 
%%: 输出一个”%”字符 
%F: 输出日志消息产生时所在的文件名称 
%L: 输出代码中的行号 
%m: 输出代码中指定的消息,产生的日志具体信息 

%n: 输出一个回车换行符，Windows平台为”\r\n”，Unix平台为”\n”输出日志信息换行