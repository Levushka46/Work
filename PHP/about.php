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
	<a href="about.php" class="butt">О нашей программе</a>
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
<div class="abouttext">
<h1><font face = "Times New Roman" color="#FFFFFF">
Целью разработки приложения является создание интеллектуальной системы, способной определить эмоциональный окрас текстового сообщения.<br/>
Задачи проекта:<br/>
1.	Выбрать наиболее подходящую для выполнения поставленной задачи модель обучения системы.<br/>
2.	Реализовать механизм рационального хранения текстов для обучения модели.<br/>
3.	Предоставить пользователю возможность вводить текстовое сообщение.<br/>
4.	Реализовать пользовательский интерфейс, предоставляющий результат обработки сообщения.<br/>
Для разработки программного продукта применяется среда визуального объектно-ориентированного программирования Microsoft Visual Studio 2019.<br/> 
Для создания информационной системы используются CASE-средства Drow IO, The Createlu Blog.<br/>
</h1>
</div>
</body>
</html>