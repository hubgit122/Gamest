create table players (
    pid integer primary key autoincrement,
    name varchar(20) not null,
    pass varchar(16),
    registerTime date,
    sex char(1) check(sex in(‘M’,‘F’)),
    played integer,
    winned integer,
    tied integer,
    money integer,
    experience integer
);

create table undone (
    pid integer,
    gid integer,
    constraint primary key(pid,gid)
);

create table games(
    gid integer primary key autoincrement,
    history varchar(9999),
    info varchar(9999)
);