<?php


class searchParty {
    
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
    public function searchByLocation($partyLocation)
    {
	$query = "select partyName, partyLocation, partyTime, partyComments from parties where partyLocation like '%{$partyLocation}%';";
	$results = $this->db->query($query);
	//$partyInfo = $results->fetch_assoc();
	$num = $results->num_rows;
	$partyString;
	if(!$results)
	{
	  $this->logger->log("error with results: ".$this->db->error);
	  return 0;
	}
	if($num >= 1)
	{
	    $partyString = "Succesful We found ".$num." Parties in your Area!<p> <br>";
	    if($results->num_rows){
		while($partyInfo = $results->fetch_object()){
		    $partyString= $partyString.
				  "Party Name: ".$partyInfo->partyName."<p>".
				  "Party Location: ".$partyInfo->partyLocation."<p>".
				  "Party Time: ".$partyInfo->partyTime."<p>".
				  "Party Comments: ".$partyInfo->partyComments."<p> <br>";
		}
	    }
	}else{
		$partyString = "Sorry we found $num Parties near $partyLocation. <p> <br>";
	    }
	return $partyString;
	
	return array("success"=>true,
		     "partyName"=>$partyInfo['partyName'],
		     "partyLocation"=>$partyInfo['partyLocation'],
		     "partyTime"=>$partyInfo['partyTime'],
		     "partyComments"=>$partyInfo['partyComments'],
		     "partyResults"=>$num
		     
	);
	return "The number of result(s) is $num  <p>" ;
    }
    
    public function browseParties()
    {
      $query = "SELECT * FROM parties WHERE partyTime >= curdate() order by partyTime Limit 10;";
      $results = $this->db->query($query);
      //$partyInfo = $results->fetch_assoc();
      $num = $results->num_rows;
      $partyString;
      if(!$results)
	{
	  $this->logger->log("error with results: ".$this->db->error);
	  return "Doesn't work<p>";
	}
	if($num >= 1){
	    $partyString = "Here are ".$num." of the upcoming Parties right now!<p> <br>";
	    if($results->num_rows){
		while($partyInfo = $results->fetch_object()){
		    $partyString = $partyString.
				  "Party Name: ".$partyInfo->partyName."<p>".
				  "Party Location: ".$partyInfo->partyLocation."<p>".
				  "Party Time: ".$partyInfo->partyTime."<p>".
				  "Party Comments: ".$partyInfo->partyComments."<p> <br>";
		}
	    }
	}else{
		$partyString = "Sorry we found $num Parties around $partyTime <p> <br>";
	    }
	return $partyString;
    
    }
    
    
    public function searchByTime($partyTime)
    {
      $query = "SELECT * FROM parties WHERE CAST( partyTime AS DATE ) = '$partyTime';";
      $results = $this->db->query($query);
      //$partyInfo = $results->fetch_assoc();
      $num = $results->num_rows;
      $partyString;
      if(!$results)
	{
	  $this->logger->log("error with results: ".$this->db->error);
	  return "Doesn't work<p>";
	}
	if($num >= 1){
	    $partyString = "Succesful We found ".$num." Parties around $partyTime !<p> <br>";
	    if($results->num_rows){
		while($partyInfo = $results->fetch_object()){
		    $partyString = $partyString.
				  "Party Name: ".$partyInfo->partyName."<p>".
				  "Party Location: ".$partyInfo->partyLocation."<p>".
				  "Party Time: ".$partyInfo->partyTime."<p>".
				  "Party Comments: ".$partyInfo->partyComments."<p> <br>";
		}
	    }
	}else{
		$partyString = "Sorry we found $num Parties around $partyTime <p> <br>";
	    }
	return $partyString;
      
      
    }
    
    public function searchByLocationAndTime($partyTime, $partyLocation)
    {
	$query = "SELECT * FROM parties WHERE CAST( partyTime AS DATE ) = '$partyTime' and partyLocation like '%{$partyLocation}%';";
	  $results = $this->db->query($query);
	  //$partyInfo = $results->fetch_assoc();
	  $num = $results->num_rows;
	  $partyString;
	  if(!$results)
	    {
	      $this->logger->log("error with results: ".$this->db->error);
	      return "Doesn't work<p>";
	    }
	    if($num >= 1){
		$partyString = "Succesful We found ".$num." Parties near $partyLocation and around $partyTime !<p> <br>";
		  if($results->num_rows){
		      while($partyInfo = $results->fetch_object()){
			  $partyString = $partyString.
					"Party Name: ".$partyInfo->partyName."<p>".
					"Party Location: ".$partyInfo->partyLocation."<p>".
					"Party Time: ".$partyInfo->partyTime."<p>".
					"Party Comments: ".$partyInfo->partyComments."<p> <br>";
		      }
		  }
	    }else{
		$partyString = "Sorry we found $num Parties near $partyLocation and around $partyTime <p> <br>";
	    }
	    return $partyString;
    }



  public function googlePartyMarkers(){
  
        
    // Get parameters from URL
    $center_lat = $_GET["lat"];
    $center_lng = $_GET["lng"];
    $radius = $_GET["radius"];

    // Start XML file, create parent node
    $dom = new DOMDocument("1.0");
    $node = $dom->createElement("markers");
    $parnode = $dom->appendChild($node);


    // Search the rows in the markers table
    $query = sprintf("SELECT address, name, lat, lng, ( 3959 * acos( cos( radians('%s') ) * cos( radians( lat ) ) * cos( radians( lng ) - radians('%s') ) + sin( radians('%s') ) * sin( radians( lat ) ) ) ) AS distance FROM markers HAVING distance < '%s' ORDER BY distance LIMIT 0 , 20",
      mysql_real_escape_string($center_lat),
      mysql_real_escape_string($center_lng),
      mysql_real_escape_string($center_lat),
      mysql_real_escape_string($radius));
    $result = mysql_query($query);

    $result = mysql_query($query);
    if (!$result) {
      die("Invalid query: " . mysql_error());
    }

    header("Content-type: text/xml");

    // Iterate through the rows, adding XML nodes for each
    while ($row = @mysql_fetch_assoc($result)){
      $node = $dom->createElement("marker");
      $newnode = $parnode->appendChild($node);
      $newnode->setAttribute("name", $row['name']);
      $newnode->setAttribute("address", $row['address']);
      $newnode->setAttribute("lat", $row['lat']);
      $newnode->setAttribute("lng", $row['lng']);
      $newnode->setAttribute("distance", $row['distance']);
    }

    echo $dom->saveXML();

  
  }


    


}



?>