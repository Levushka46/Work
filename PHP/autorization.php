<?php 
  session_start(); 
?>
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
<form method="post" action="/php/checkus.php">
<div class="logintext">Логин</div>
<div><input type="text" name="ULogin" id="ULogin"/></div>
<div class="result"></div>
<div class="logintext">Пароль</div>
<div><input type="password" name="Upass" id="Upass"/></div>
<div class="result1"></div>
<div><input class="knopkaotpr" type="submit" name="send"/></div>
<div><input class="knopkaotpr" type="reset" name="clear"/></div>
</form>
</body>
</html>