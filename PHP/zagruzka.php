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
<form action="/php/loadfiles.php" method="post" enctype="multipart/form-data">
<p><font face = "Times New Roman" color="#FFFFFF">
Выберите файл:
<input class="zagr" type="file" name="file"/>
<input class="zagr" type="submit" value="Отправить"/>
</p>
</form>
</body>
</html>