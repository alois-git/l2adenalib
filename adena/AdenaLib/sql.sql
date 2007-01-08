-- SQLite Maestro 6.12.0.3
-- ----------------------------------------
-- Host     : localhost
-- Database : C:\Programing\Visual Studio Projects\Adena\bin\l2adena.sqlite


CREATE TABLE accounts (
  id        integer PRIMARY KEY NOT NULL,
  username  varchar(32),
  password  varchar(14)
);

CREATE TABLE characters (
  id            int PRIMARY KEY NOT NULL,
  account_name  varchar(14) NOT NULL,
  name          varchar(16) NOT NULL,
  race_id       int NOT NULL,
  class_id      int NOT NULL,
  sex           int NOT NULL,
  hair_type     int NOT NULL,
  hair_color    int NOT NULL,
  face          int
);