 drop table if exists clients;
 create table clients
  (
    clientId INT(11) primary key auto_increment,
    clientName varchar(32),
    clientPW varchar(64),
    activeSession varchar(128),
    firstLogin datetime,
    lastLogin datetime,
    clientRating INT(11) 
    
  );
  
 drop table if exists parties;
 create table parties
  (
    partyId INT(11) primary key auto_increment,
    clientName varchar(32),
    partyName varchar(32),    
    partyLocation varchar(50),
    `lat` FLOAT( 10, 6 ) NOT NULL ,
    `lng` FLOAT( 10, 6 ) NOT NULL,
    partyTime dateTime,
    partyComments varchar(128),
    partyRating INT(11)
  
  );
  
 drop tables if exists comments;
 CREATE TABLE comments 
  (
    commentId INT(11) primary key auto_increment,
    comments varchar (128), 
    commenterId varchar(32),
    partyID varchar(32),
    upVotes INT(11),
    enabled INT(2),
    commentTime dateTime
  
  );
  
  CREATE TABLE `markers` (
  `id` INT NOT NULL AUTO_INCREMENT PRIMARY KEY ,
  `name` VARCHAR( 60 ) NOT NULL ,
  `address` VARCHAR( 80 ) NOT NULL ,
  `lat` FLOAT( 10, 6 ) NOT NULL ,
  `lng` FLOAT( 10, 6 ) NOT NULL
) ENGINE = MYISAM ;
  