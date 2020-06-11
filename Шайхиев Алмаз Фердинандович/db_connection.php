<?php
$db_connect=mysqli_connect("localhost", "root","" ,"kyrsov_sh");
if($db_connect->connect_error){
    printf("Соединение не удалось:%s\n", $db_connect->connect_error);
    exit();
}