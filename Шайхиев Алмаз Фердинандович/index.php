<?php
    include_once 'db_connection.php';  
    include_once 'functions.php';
?>
<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8">
        <title>qq</title>
        <link rel="stylesheet" href="css/main.css">
        <script src="js/jquery-3.0.0.min.js"></script>
        <script src="js/main.js"></script>
        
    </head>
    <body>
        <h1>Инвестиционные предложения на рынке:</h1>
        <div class="add_offer">
            <form action="" method="get" class="offers">
                <h3>Добавить предложение:</h3>
                <p>Стоимость вложений:</h1><br>
                <input type="text" name="cost"><br>
                <p>Период бездохода в месяцах:</h1><br>
                <input type="text" name="time"><br>
                <p>d i – доход инвестора (млн. руб.) в месяц после периода:</h1><br>
                <input type="text" name="value"><br>
                <input type="submit" value="Добавить" name="add_offer" class="add_offer" style="margin-top: 10px;">
            </form>
            <div class="show_offers_table" style="width: 500px;"><?php show_offers($db_connect);?></div>  
        </div>
        <h1>Введите ваш капитал, равный S млн. рублей и интереусющий период времени:</h1>
        <form action="" method="POST">
            <p>Стоимость капитала:</h1><br>
            <input type="text" name="sum"><br>
            <p>Период времени:</h1><br>
            <input type="text" name="days"><br>
            <input type="submit" value="Рассчитать" name="add_capital_and_time" style="margin-top: 10px;">
        </form>
        <div class="table">
        <?php
        include "main.php";        
        ?>
        </div>
    </body>
</html>
