<?php
//require_once("error.php.inc");

class partyPost 
{
  
    private $db;	
    private $logger;
    public function __construct($iniFile)
    {
	$ini = parse_ini_file($iniFile,true);
        $this->logger = new errorLogger("/var/log/it202.log");
	$this->db = new mysqli(
		$ini['loginDB']['host'],
		$ini['loginDB']["user"],
		$ini['loginDB']["password"],
		$ini['loginDB']["db"]);
	if ($this->db->connect_errno > 0 )
	{
		$this->logger->log(__FILE__.__LINE__."failed to connect to database re: ".$this->db->connect_error);
		exit(0);
	}
	$this->logger->log("testing");
    }
    public function __destruct()
    {
	$this->db->close();
    }

    public function getPartyID($partyName)
    {
	$query = "select partyId from parties where partyName = '$partyName';";
	$results = $this->db->query($query);
	if(!$results)
	{
	  $this->logger->log("error with results: ".$this->db->error);
	  return 0;
	}
	$party = $results->fetch_assoc();
	if(isset($party['partyId']))
	{
	  return $party['partyId'];
	}
	return 0;	
    }
    public function addNewParty($clientName, $partyName, $partyLocation, $partyTime, $comment)
    {
      if($this->getPartyID($partyName) != 0)
      {
	$this->logger->log("user $partyName already exists!!!");
	$response = array(
	      "message"=>"party $partyName already exists!",
	      "success"=>false
	      );
	return $response;
      }
      $clientName =$this->db->real_escape_string($clientName);
      $partyName = $this->db->real_escape_string($partyName);
      $partyLocation = $this->db->real_escape_string($partyLocation);
      //2016-12-20 08:00
      //$partyTime = date("Y-m-d H:i:s", $partyTime);
      $comment = $this->db->real_escape_string($comment);
      $addQuery = "insert into parties (clientName, partyName, partyLocation, partyTime, partyComments) 
			values ('$clientName','$partyName', '$partyLocation', '$partyTime', '$comment');";
      $results = $this->db->query($addQuery);
      if(!$results)
      {
	$this->logger->log("error: ".$this->db->error);
      }
      return array("success"=>true);
      
	
    }
    
    public function postPartyComment($partyName, $partyComment)
    {
	$partyResponse;
	$partyName = $this->db->real_escape_string($partyName);
	$partyComment = $this->db->real_escape_string($partyComment);
	$partyComments = " .". $partyComment;
	if($this->getPartyID($partyName) != 0)
	{
	    $commentQuery ="UPDATE parties SET partyComments = concat( partyComments, ' $partyComments' ) WHERE partyName = '$partyName';";
	    $results = $this->db->query($commentQuery);
	    
	    if($results){
	      $partyResponse = " \"$partyComment\" Comment was posted";
	    }else{
	      $partyResponse = "Comment was not posted";
	    }
	    
	}
	else
	{
	    $partyResponse = "$partyName does not exist";
	}
	
	return $partyResponse;
      
    
    
    }



}
?>





