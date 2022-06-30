<?php
$tmp_name = $_FILES["file"]["tmp_name"];
        $name = $_FILES["file"]["name"];
	if (move_uploaded_file($tmp_name, "../load/$name")) {
    echo "Файл корректен и был успешно загружен.\n";
} else {
    echo "Файл не был загружен!\n";	
}
echo "Вы будете перенаправлены на главную страницу через 5 секунд\n";	
header("refresh:5;url=../index.php");
?>