<?php
$userName=$_POST['UName'];
$userAge=$_POST['UAge'];
$userLogin=$_POST['ULogin'];
$userPass=$_POST['Upass'];
$db = new mysqli("localhost", "root", "", "test");
if(!$db)
	echo "no connection";
else{
	$sqlAddUser = "insert into users(name, age, login, pass)values(\"".$userName."\",\"".$userAge."\",\"".$userLogin."\",\"".$userPass."\")";
	$addUserRef = $db->query($sqlAddUser);
	header("location: ../index.php");
	//echo $sqlAddUser;
	$db->close();
	}
?>