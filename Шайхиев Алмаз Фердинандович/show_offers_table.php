<?php
    include_once 'db_connection.php';  
    include_once 'functions.php'; 
        if(isset($_GET["cost"],$_GET["value"],$_GET["time"])){
            mysqli_query($db_connect, "insert into almaz_kyrsov (offer_cost, offer_novalue_time, offer_value) "
                    . "values (". filter_input(INPUT_GET,"cost").",".filter_input(INPUT_GET,"time").",".filter_input(INPUT_GET,"value").")");
        }else{
            echo "Не все поля заполнены";
        }
        show_offers($db_connect);
       
        
