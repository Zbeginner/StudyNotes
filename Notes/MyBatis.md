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

### 事务

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

### 关联映射

经常我们一个实体类中经常包含其它实体类的对象

```java
@Data
class Stduent{
    private Integer studentId;
    private String name;
    private String studentNumber;
    private Integer teacherId;
    //需要装配的对象
    private Teacher teacher;
}
```

#### 业务装配

ResultMap Mapping映射

```xml
<resultMap id="BaseResultMap" type="cn.cafuc.cs.zzy.model.Student">
    <id column="student_id" jdbcType="INTEGER" property="studentId" />
    <result column="name" jdbcType="VARCHAR" property="name" />
    <result column="student_number" jdbcType="VARCHAR" property="studentNumber" />
    <result column="teacher_id" jdbcType="INTEGER" property="teacherId" />
</resultMap>
<select id="getAll" resultMap="BaseResultMap">
    select * from student
</select>
```

 对应Service

```java
public void showStudent(){
    //先获得基础的学生对象
    List<Student> students=studentMapper.getAll();
    for(Student tem:students){
        //业务(手动)装配对应的teacher对象到对应属性
        tem.teacher=teacherMapper.selectById(tem.teacherId);
    }
}
```

#### < association />标签(一对一关系映射)

实体类

```java
@Data
class Stduent{
    private Integer studentId;
    private String name;
    private String studentNumber;
    //需要装配的对象
    private Teacher teacher;
}
```



```xml
<mapper namespace="cn.cafuc.cs.zzy.mapper.StudentMapper">
<resultMap id="BaseResultMap" type="cn.cafuc.cs.zzy.model.Student">
    <id column="student_id" jdbcType="INTEGER" property="studentId" />
    <result column="name" jdbcType="VARCHAR" property="name" />
    <result column="student_number" jdbcType="VARCHAR" property="studentNumber" />
    <!-- property 映射到实体类的对象的属性-->
    <!-- javaType 指定映射到实体对象的属性-->
    <!-- column 指定表中的属性-->
    <!-- select 指定引入嵌套查询的子SQL语句-->
    <!-- 四个属性的位置是没有顺序的-->
    <association property="teacher"
                 javaType="cn.cafuc.cs.zzy.model.Teacher" 
                 column="teacherId"
                 select="cn.cafuc.cs.zzy.mapper.TeacherMapper.selectById">
    </association>
</resultMap>
<select id="getAll" resultMap="BaseResultMap">
    select * from student
</select>
</mapper>
```

- Mybatis 属于懒装配，每个属性只装配一次，也就是如果用了< association />标签，提前使用了teacherId这个属性，那么在getAll里面，将不会给对象装配teacherId这个属性（如果对象有这个属性的话）。

- 用**< association />**标签和**业务装配** 所达到的效果和效率是一样的。因为用**< association />** 实际上也是运行了两个SQL语句

  ```sql	
  #第一条
  select * from student
  #第二条
  select * from teacher where id=#{teacherId}
  #然后再把第二条的结果赋值给实体对象的teacher对象。
  #所以效率其实是一样的
  ```


### 一些小应用

1. get/set的应用

   有的时候我们存入数据库中的数据并不是原始值。

   ```java
   public class Cart {
       //订餐时间范围  前端设计的值是[中餐、晚餐、明日中餐、明日晚餐]
       //数据库中设定的值是[1、2、3、4]分别对应
       private Integer spec;
   }
   ```

   。麻瓜的手动判断修改，每次都会浪费很多时间精力。有的时候可以这样处理一下。

   ```java
   public class Cart {
       //订餐时间范围
       private Integer spec;
       //我们预先可以判断给spec赋值的只会有前端传给我们的String和mybatis装配的Integer
       public void setSpec(Object spec) {
          if(spec.getClass()==String.class){
              switch ((String)spec){
                  case "中餐":this.spec=1;break;
                  case "晚餐":this.spec=2;break;
                  case "明日中餐":this.spec=3;break;
                  case "明日晚餐":this.spec=4;break;
                  default:;
              }
          }else{
              this.spec=(Integer)spec;
          }
       }
   }
   ```

   

   