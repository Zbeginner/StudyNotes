# 杂(Java)

1. 关于Java中替换字符串中'\\'的问题

   ```java
   //下面字符串实际显示的是a\b\c\d这个大家都知道
   String s="a\\b\\c\\d";
   //但是我们想把它处理成abcd
   //String 有好几个带替换功能的方法了
   //下面这两个都是全局替换
   //String.replace()
   //String.replaceAll()
   //1.public String replace(CharSequence target, CharSequence replacement)
   String s="a\\b\\c\\d";
   s=s.replace("\\","");
   //java \\表示‘\’
   
   //2.public String replaceAll(String regex, String replacement)
   //传入的第一个参数是正则表达式
   String s="a\\b\\c\\d";
   //java\\表示一个'\'   正则\\表示一个'\'  两个\\才能表示一个'\'
   //所以这里要4个'\'
   s=s.replaceAll("\\\\","");
   ```

   