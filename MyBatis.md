# MyBatis

### #{}和${}区别

- #{} 底层解析为**占位符**
  - 获取参数的内容支持索引获取，param1获取指定位置的参数,也可以用数字索引  #{0}
  - 如果参数是对象 #{属性名}
  - 如果参数是Map 写成#{key}
- ${} 底层解析为**字符串拼接**
  - 默认找${Object} Object的get\set方法 
  - 如果参数是默认数据类型 如 ${0} 那么就是0 和传来的参数无关

### MySql分页

- 框架分页——PageHelper

  - 太简单不介绍了

- 源码分页

  - ```Xml
    <select id="" parameterType="">
    	select * from table limit #{pageStart},#{pageSize}
    </select>
    ```

    - Sql源码意思举例

      - ```sql
        #limit 1,2 意思是从people表中第二行开始查两个元素
        select * from people limit 1,2
        ```

  - **注意!**

    - 一般前端只会请求**PageNumber**(第几页),**PageSize**(一页多少个)。意思是以**PageSize**为单位分页，取第**PageNumber**页的数据。而我们要的是**==PageStart==**。则需要做相应的运算。
    - PageStart=PageSize*(PageNumber-1)

### 别名机制

- MyBatis resultType类型标准为**全类名**但是并不方便，所以有了别名机制

  - 在MyBatis全局配置文件中，可以配置typeAliases

    - 为单个类配置  type为类的全路径，alias为别名，别名可以任意取，但注意命名规范

      - ```xml
        <typeAliases>
        	<typeAlias type="cn.cafuc.cs.model.People" alias="peo"/>
        </typeAliases>
        ```

    - 为某个包下的所有类配置别名，所生成的别名为对应类名

      - ```xml
        <typeAliases>
        	<package name="cn.cafuc.cs.model" />
        </typeAliases>
        ```

### 实现新增

1. 概念
   1. 功能
      - 从应用程序角度出发，软件具有哪些功能
   2. 业务
      - 完成功能时的逻辑
   3. 事务
      - 从数据库角度出发，完成业务时需要<u>执行的SQL的集合</u>，统称为一个**事务**
2. MyBatis底层是对JDBC的封装
   1. JDBC中executeUpdate()执行新增、修改、删除的SQL返回值是int,表示受影响的行数。
   2. MyBatis中<insert><delete><update>标签就没有resultType属性，自动认为返回值是int。
3. 在openSession()时，MyBatis会创建SqlSession时，同时创建一个Transaction对象，同时autoCommit为false
4. **增删改的时候一定要提交事务** 即session.commit()(暂时我不懂，好像不commit数据没法更新数据库)
5. 事务回滚
   - 如果一个事务中的某个SQL执行错误，希望回归到事务的原点，保证数据库数据的完整性。即session.rollbacn()。