<?php

require_once "partyPost.php.inc";
require_once "clientDB.php.inc";
require_once "searchParty.php.inc";




// odd php code
/*
$request = $_POST['request'];
$response = "FUCK<p>";
switch($request)
*/

///new javascript JSON code
$request = json_decode(file_get_contents("php://input"), true);
$response = "error unrecongnized request<p>";

switch($request["request"])
{
    case "login":
	$username = $request['username'];
	$password = $request['password'];
	$login = new clientDB("connect.ini");
	$response = $login->validateClient($username,$password);
	if ($response['success']===true)
	{
		$response = "Login Successful!<p>";
	}
	else
	{
		$response = "Login Failed:".$response['message']."<p>";
	}
	break;
	
    case "register":
	$username = $request['username'];
	$password = $request['password'];
	//echo $password;
	$register = new clientDB("connect.ini");
	$register->addNewClient($username, $password);
	$response = $register->validateClient($username,$password);
	if ($response['success']===true)
	{
		$response = "Register Successful!<p>";
	}
	else
	{
		$response = "Register Failed:".$response['message']."<p>";
	}
	break;
    
    case "Post Comment":
	$response= "It works";
	$partyName = $_POST['PartyName'];
	$partyComment = $_POST['PartyComment'];
	$post = new partyPost("connect.ini");
	$response = $post->postPartyComment($partyName, $partyComment);

	
	break;
	
    case "Browse Parties":
	 $search = new searchParty("connect.ini");
	 $response = $search->browseParties();
	 
	 break;
	  
	
    
    case "Find a Party by Time":
	//$search = new searchParty("connect.ini");
	//$response= $search->searchByTime($partyRequest);
	
	$day = $_POST['day'];
	$month = $_POST['month'];
	$year = $_POST['year'];
	$minute = $_POST['minute'];
	$hour = $_POST['hour'];
	$ampm = $_POST['ampm'];
	//$date = date('Y-m-d H:i:s',strtotime($year."-".$month."-".$day." ".$hour.":".$minute." ".$ampm));
	$date = date('Y-m-d H:i:s',strtotime($year."-".$month."-".$day));
	//echo $date;
	
	$search = new searchParty("connect.ini");
	$response= $search->searchByTime($date);
	break;
	
    case "Find a Party by Time and Location":
    
	  $day = $_POST['day'];
	  $month = $_POST['month'];
	  $year = $_POST['year'];
	  $minute = $_POST['minute'];
	  $hour = $_POST['hour'];
	  $ampm = $_POST['ampm'];
	  //$date = date('Y-m-d H:i:s',strtotime($year."-".$month."-".$day." ".$hour.":".$minute." ".$ampm));
	  $date = date('Y-m-d H:i:s',strtotime($year."-".$month."-".$day));
	  $partyLocation = $_POST["findByLocationAndTime"];
	
	  $search = new searchParty("connect.ini");
	  $response = $search->searchByLocationAndTime($date, $partyLocation);
	  break;
	
    case "Find Party":
	$partyRequest = $_POST["findByLocation"];
	//echo $partyRequest;
	$search = new searchParty("connect.ini");
	$response= $search->searchByLocation($partyRequest);
	
	/*
	if ($response['success']===true)
	{	echo "Succesful We found ".$response['partyResults']." Parties in your Area!<p>";
		
		$response =   "Party Name: ".$response['partyName']."<p>".
			      "Party Location: ".$response['partyLocation']."<p>".
			      "Party Time: ".$response['partyTime']."<p>".
			      "Party Comments: ".$response['partyComments']."<p>";
		//"Succesful We found Parties in your Area!<p>";
	}
	else
	{
		$response = "Register Failed:".$response['message']."<p>";
	}
	*/
	break;
    
	

    case "Post Party":
	$username = $_POST["username"];
	$password = $_POST["password"];
	$partyName= $_POST["partyName"];
	$partyLocation = $_POST["partyLocation"];
	
	$address = $_POST["address"];
	$city = $_POST["city"];
	$state = $_POST["state"];
	$zip = $_POST["zip"];
	$partyLocation = $address.' '. $city.' '. $state.' '.$zip;
	//echo $partyLocation;
	
	$partyTime = $_POST["partyTime"];
	$comment = $_POST["comment"];
	
	$day = $_POST['day'];
	$month = $_POST['month'];
	$year = $_POST['year'];
	$minute = $_POST['minute'];
	$hour = $_POST['hour'];
	$ampm = $_POST['ampm'];
	$date = date('Y-m-d H:i:s',strtotime($year."-".$month."-".$day." ".$hour.":".$minute." ".$ampm));
	//$date = date('Y-m-d H:i:s',strtotime($month.' '.$day.','.$year.' '.$hour.':'.$minute.' '.$ampm)); 
	//$date = date('Y-m-d H:i:s',strtotime($hour.':'.$minute.$ampm.' '.$month.' '.$day.' '.$year)); 
	
	


	$login = new clientDB("connect.ini");
	$response = $login->validateClient($username,$password);
	if ($response['success']===true)
	{
		$response = "Login Successful!<p>";
		$post = new partyPost("connect.ini");
		$response = $post->addNewParty($username, $partyName, $partyLocation, $date, $comment);
		if ($response['success']===true)
		{
			$response = "Party Positng Successful!<p>";
		}
		else
		{
			$response = "Party Posting Failed:".$response['message']."<p>";
		}
		}
	else
	{
		$response = "Login Failed:".$response['message']."<p>";
	}
	//$response = "Post Party Success!". $partyName. " " .$username. " " . $password. " ". $partyLocation. " ". $partyTime. "<p>";
	break;
	
}

echo $response;
?>





