<?php
$userLogin=$_POST['ULogin'];
$userPass=$_POST['Upass'];
$db = new mysqli("localhost", "root", "", "test");
if(!$db)
	echo "no connection";
else{
	session_start();
	$query = mysqli_query($db, "SELECT id FROM users WHERE login='".$_POST['ULogin']."' and pass='".$_POST['Upass']."'");
	while ($row = mysqli_fetch_assoc($query)){
		$_SESSION["user"]=$row['id'];
	}
	header("location: ../index.php");
	$db->close();
	}
	?>