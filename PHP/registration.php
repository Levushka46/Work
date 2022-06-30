<?php 
  session_start(); 
?>
<html>
<head>
<meta charset="UTF-8">
<title>Интеллектуальная система отношений</title>
<link rel="stylesheet" href="/css/style.css"/>
</head>
<body bgcolor='#5151b8''>
<div class="indexmain">
	<a href="index.php" class="butt">Главная</a>
	<a href="about.php" class="butt">О нашем сайте</a>
	<?php
	if (!isset($_SESSION['user']))
	{
		echo '<a href="registration.php" class="butt">Регистрация</a>';
		echo '<a href="autorization.php" class="butt">Авторизация</a>';
	}
	?>
	<?php
	if (isset($_SESSION['user']))
	{
		echo '<a href="zagruzka.php" class="butt">Загрузка файла</a>';
		echo '<a href="exit.php" class="butt">Выйти</a>';
	}
	?>	
</div>
<form method="post" action="/php/reg.php">
<div class="logintext">ФИО</div>
<div><input type="text" name="UName" id="UName"/></div>
<div class="result1"></div>
<div class="logintext">Возраст</div>
<div><input type="text" name="UAge" id="UAge"/></div>
<div class="result2"></div>
<div class="logintext">Логин</div>
<div><input type="text" name="ULogin" id="ULogin"/></div>
<div class="result3"></div>
<div class="logintext">Пароль</div>
<div><input type="password" name="Upass" id="Upass"/></div>
<div class="result4"></div>
<div><input class="knopkaotpr" type="submit" name="send"/></div>
<div><input class="knopkaotpr" type="reset" name="clear"/></div>
</form>
</body>
<script src="/js/jquery.js"> </script>
<script src="/js/checkloginpas.js"> </script>
</html>