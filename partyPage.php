<?php
$db_conx = mysqli_connect("localhost", "root", "jman23", "it202");


$notification_list = "";
$sql = "SELECT * FROM parties WHERE partyTime > NOW() ORDER BY partyTime ASC";
$query = mysqli_query($db_conx, $sql);
$numrows = mysqli_num_rows($query);
if($numrows < 1){
	$notification_list = "No Parties Right now Sorry";
} else {
	while ($row = mysqli_fetch_array($query, MYSQLI_ASSOC)) {
		$partyId = $row["partyId"];
		$host = $row["clientName"];
		$partyName = $row["partyName"];
		$partyLocation = $row["partyLocation"];
		$date_time = $row["partyTime"];
		$commet = $row["partyComments"];
		$date_time = strftime("%b %d, %Y", strtotime($date_time));
		$notification_list .= "<p>$partyName is being hosted by the Plug: $host. The address is $partyLocation 
		at $date_time. Details: $commet.		
		</p>";
	}
}

?>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Parties</title>
<link rel="icon" href="favicon.ico" type="image/x-icon">
<link rel="stylesheet" href="style/style.css">
<style type="text/css">
div#notesBox{float:left; width:430px; border:#F0F 1px dashed; margin-right:60px; padding:10px;}
div#friendReqBox{float:left; width:430px; border:#F0F 1px dashed; padding:10px;}
div.friendrequests{height:74px; border-bottom:#CCC 1px solid; margin-bottom:8px;}
img.user_pic{float:left; width:68px; height:68px; margin-right:8px;}
div.user_info{float:left; font-size:14px;}
</style>
<script src="main.js"></script>
<script src="ajax.js"></script>

</head>
<body>

<div id="pageMiddle">
  <!-- START Page Content -->
  <div id="notesBox"><h2>Parties</h2><?php echo $notification_list; ?></div>
  
  <div style="clear:left;"></div>
  <!-- END Page Content -->
</div>

</body>
</html>