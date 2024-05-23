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
-- delete from stu2 where sname='小陈';
