## 基础

### 修改MySql登陆密码

1. set password for root@localhost = password('新密码');  

2. update user set password=password('新密码') where user='root' and host='localhost';  

3. **在忘记root密码的时候，可以这样**   

   1. 关闭正在运行的MySQL服务。  

   2. 打开DOS窗口，转到mysql\bin目录。  

   3. 输入mysqld --skip-grant-tables 回车。--skip-grant-tables 的意思是启动MySQL服务的时候跳过权限表认证。  

   4. 再开一个DOS窗口（因为刚才那个DOS窗口已经不能动了），转到mysql\bin目录。  

   5. 输入mysql回车，如果成功，将出现MySQL提示符 >。  

   6. 连接权限[数据库](http://lib.csdn.net/base/mysql)： use mysql; 。  
   7. 改密码：update user set password=password("123") where user="root";（别忘了最后加分号） 。  
   8. 刷新权限（必须步骤）：flush privileges;　。  
   9. 退出 quit。  
   10. 注销系统，再进入，使用用户名root和刚才设置的新密码123登录。

## 触发器

### 查询触发器

```cmd
#第一种（要到对应数据库）
show triggers;
#效果
+---------+--------+-------+------------------------------------------------------------------------------+--------+------------------------+-----------------------------------------------------------------------------------------------------------------------+----------------+----------------------+----------------------+--------------------+
| Trigger | Event  | Table | Statement                                                                    | Timing | Created                | sql_mode                                                                                                              | Definer        | character_set_client | collation_connection | Database Collation |
+---------+--------+-------+------------------------------------------------------------------------------+--------+------------------------+-----------------------------------------------------------------------------------------------------------------------+----------------+----------------------+----------------------+--------------------+
| tt      | DELETE | cart  | INSERT INTO orders VALUES(DEFAULT,old.user_id,old.good_id,old.num,SYSDATE()) | BEFORE | 2019-04-28 13:12:08.99 | ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION | root@localhost | utf8mb4              | utf8mb4_0900_ai_ci   | utf8_general_ci    |
+---------+--------+-------+------------------------------------------------------------------------------+--------+------------------------+---------------------------------

#第二种
show triggers \G;
#效果
*************************** 1. row ***************************
             Trigger: tt
               Event: DELETE
               Table: cart
           Statement: INSERT INTO orders VALUES(DEFAULT,old.user_id,old.good_id,old.num,SYSDATE())
              Timing: BEFORE
             Created: 2019-04-28 13:12:08.99
            sql_mode: ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION
             Definer: root@localhost
character_set_client: utf8mb4
collation_connection: utf8mb4_0900_ai_ci
  Database Collation: utf8_general_ci
  
#第三种(触发器都会存在information_schema数据库中)
select * from information_schema.triggers;
#效果	
```

![](D:\求学路\StudyNotes\image\触发器.png)