<?php
include_once 'db_connection.php'; 
function show_offers($db_connect){
    $query = "select * from almaz_kyrsov";
    $result2 =mysqli_query($db_connect, $query);
    $table = '<table border="1">';
    $table .= '<tr style="background-color: #6767fb;"><td>N</td><td>Стоимость вложений</td><td>Период бездохода</td><td>Доход инветсора(млн.руб.)</td></tr>';
    while ($result = mysqli_fetch_assoc($result2)){
        $table .= '<tr style="background-color: #e8e8ff">';
        $table.= '<td>'. $result['offer_id'].'</td>';
        $table.= '<td>'. $result['offer_cost'].'</td>';
        $table.= '<td>'. $result['offer_novalue_time'].'</td>';
        $table.= '<td>'. $result['offer_value'].'</td>';
        $table .= '<tr>';              
    }       
        $table .= '</table>';
    echo $table;
}

function find_sum($db_connect,$days){
    $query= "select * from almaz_kyrsov";
    $result2 = mysqli_query($db_connect, $query);
    while ($result = mysqli_fetch_assoc($result2)){
        $sum = ($days - $result['offer_novalue_time']) * $result['offer_value'] - $result['offer_cost'];
       mysqli_query($db_connect, "update almaz_kyrsov set offer_sum =".$sum." where offer_id = ".$result['offer_id']."" );
    } 
}
