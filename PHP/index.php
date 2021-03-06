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

<div class="maintext">
<h1>Сайт посвященный работе ВКР на тему:<br/>
ИНФОРМАЦИОННАЯ СИСТЕМА ДЛЯ ИНТЕЛЛЕКТУАЛЬНОЙ СИСТЕМЫ ОПРЕДЕЛЕНИЯ ОТНОШЕНИЙ МЕЖДУ ПОЛЬЗОВАТЕЛЯМИ<br/> 
СОЦИАНЫХ СЕТЕЙ НА ОСНОВЕ АНАЛИЗА КОРОТКИХ ТЕКСТОВЫХ СООБЩЕНИЙ<br/> 
</h1>
</div>

<div class="pictures">
<img class="img uxod" src="/pictures/2.png">
</div>
<div class="pictures">
<img class="img uxod" src="/pictures/1.png">
</div>
<div class="secondtext">
<font face = "Times New Roman" color="#FFFFFF">
<h2>Социальные сети пользуются большим успехом у огромного количества людей.<br/>
Ими пользуются как для поддержания связи с лично знакомыми людьми, так и для заведения новых знакомств.<br/>
Но социальные сети не могут передать всю полноту живых отношений,<br/>
и зачастую из-за этого возникает проблема недопонимая участников по поводу того,<br/>
в каких отношениях они состоят друг с другом. Взглянув под другим углом можно отметить,<br/> 
что социальные сети позволяют то, чего нельзя делать вживую, а именно общаться одновременно лично с большим количеством людей.<br/>
В свою очередь этот фактор создает колоссальный пласт информации, который можно изучить.<br/>
В связи с этим встает вопрос об исследовании отношений между людьми с помощью интеллектуальных систем,<br/> 
для решения проблемы недопонимая пользователей социальных сетей между собой и их (отношений) классификации,<br/>
а так же в не меньшей степени мотивирует исследовательский интерес этого аспекта социальных сетей.<br/>
</h2>
</div>
</body>
</html>
