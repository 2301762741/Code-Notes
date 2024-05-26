/*创建数据库*/
-- create database if not exists teacher;
/*删除数据库*/
-- drop database teacher;

-- /*创建表*/
-- use student;
-- create table stu2(
-- 	id int(10) auto_increment primary key,  -- 自增主键
-- 	name char(7) not null,
-- 	sex char(10) default '男'	-- 默认性别男
-- )charset=utf8;

/*显示表数据*/
-- use student;
-- show TABLEs;  -- 显示所有表
-- DESCRIBE stu2; -- 显示表的结构
-- DESC student; -- 显示表结构

/*插入表数据*/
-- 	use student;
-- 	insert into stu2(name,sex)
-- 	values('小陈','男');

/*查询表数据*/
-- use student;
-- select *from stu2;

/*修改表数据*/
-- update stu2 set sex='女' where id=9;  -- 将id=9的sex修改为'女'

/*删除表数据*/
-- DELETE FROM stu2 where sname='小陈';


/***********下面是利用主键实现多表查询代码***********/


use student;
-- CREATE table score (
-- 	sid int(10) not null,
-- 	coure char(5) not null,
-- 	grade int(10) not null,
-- 	PRIMARY KEY(sid), -- 设置主键（唯一定位标识）
-- 	FOREIGN KEY(sid) REFERENCES student(sid) -- 设置副键（另一个表的主键）
-- );

-- desc score;查看表的结构

-- use student;
-- insert into score
-- values(1,'c',90),(2,'java',80),(3,'c++',70);

-- SELECT student.sname FROM student,score where ssex='男' and grade>80

