<?php
include_once 'db_connection.php';  
include_once 'functions.php';
$num_rows = 0;
        if(isset($_POST['add_capital_and_time'])){
            $offers_array = array();
            $less_value_offers_array = array();
            find_sum($db_connect, filter_input(INPUT_POST, "days"));
            $query = "select * from almaz_kyrsov order by offer_sum Desc";
            $result2 = mysqli_query($db_connect, $query);
            $num_rows = mysqli_num_rows($result2);
            $i = 1;
            $j = 1;
            $offers_id = array();
            $sum = filter_input(INPUT_POST,"sum"); 
            while ($result = mysqli_fetch_assoc($result2)){
                $offers_id[] = $result['offer_id'];
                if($sum - $result['offer_cost'] >= 0){
                    $offers_array[$i] = array($result['offer_id'],$result['offer_cost'],$result['offer_novalue_time'],$result['offer_value'],$result['offer_sum']);  
                    $sum -= $result['offer_cost'];
                    $i++;
                }else{
                    $less_value_offers_array[$j] = array($result['offer_id'],$result['offer_cost'],$result['offer_novalue_time'],$result['offer_value'],$result['offer_sum']);  
                    $j++;
                }                               
            }
            for($i = 1; $i < sizeof($offers_array); $i++){
                if($offers_array[$i][0] > $offers_array[$i+1][0]){
                    $pointer = $offers_array[$i];
                    $offers_array[$i] = $offers_array[$i+1];
                    $offers_array[$i+1] = $pointer;
                    $i = 1;
                }
            }
            $n = 1;
            $sum2 = filter_input(INPUT_POST,"sum") - $sum;
            $table = '<table class="main_table"><tr>';
            $table .= '<td><table>';
            $table .= '<tr><td></td></tr>';
            sort($offers_id);
            for($l = 0;$l < $num_rows; $l++){
                $table .= '<tr><td></td></tr>';
            }
            $table .= '<tr><td class="invest">Инвестирование:</td></tr>';
            $table .= '<tr><td class="result">Сумма:</td></tr>';
            $table .= '</table></td>';
            $table .= '<td><table>';
            $table .= '<tr><td></td></tr>';
            sort($offers_id);
            for($l = 0;$l < $num_rows; $l++){
                $table .= '<tr><td class="numbers">'.$offers_id[$l].'</td></tr>';
            }
            $table .= '<tr><td class="invest"></td></tr>';
            $table .= '<tr><td class="result">'.filter_input(INPUT_POST,"sum").'</td></tr>';
            $table .= '</table></td>';
            for($i = 1;$i <= filter_input(INPUT_POST, "days"); $i++){
                $k = 1;
                $table .= '<td><table>';
                $table .= '<tr><td class="numbers">'.$i.'</td></tr>';
               // до вывода таблицы посчитали сумму и добавили массив 
                for($j = 1;$j <= $num_rows; $j++){
                    if($j == $offers_array[$k][0]){
                        if($offers_array[$k][2] <= 0){
                            $sum += $offers_array[$k][3];      
                        }
                        $k++;
                    }   
                }
                if($sum > 0){
                    for($l = 1; $l <= sizeof($less_value_offers_array); $l++){
                        if($less_value_offers_array[$l][1] <= $sum){
                            $less_value_offers_array[$l][4] = (filter_input(INPUT_POST, "days") - $i - $less_value_offers_array[$l][2])*$less_value_offers_array[$l][3]-$less_value_offers_array[$l][1];
                        }
                        else{
                            $less_value_offers_array[$l][4] = 0;
                        }
                    }
                    $l =1 ;
                    while($l < sizeof($less_value_offers_array)){
                        if($less_value_offers_array[$l][4] < $less_value_offers_array[$l+1][4]){
                            $pointer = $less_value_offers_array[$l];
                            $less_value_offers_array[$l] = $less_value_offers_array[$l+1];
                            $less_value_offers_array[$l+1] = $pointer;
                            $l = 1;
                        }else{
                            $l += 1;
                        }
                    }
                }
                $k = 1;
                if($sum >= $less_value_offers_array[$n][1]){
                    if(((filter_input(INPUT_POST, "days") - $i + 1 - $less_value_offers_array[$n][2])*$less_value_offers_array[$n][3]-$less_value_offers_array[$n][1]) > 0){
                        $offers_array[] = $less_value_offers_array[$n];
                        $m = 1;
                        while($m < sizeof($offers_array)){
                            if($offers_array[$m][0] > $offers_array[$m+1][0]){
                                $pointer = $offers_array[$m];
                                $offers_array[$m] = $offers_array[$m+1];
                                $offers_array[$m+1] = $pointer;
                                $m = 0;
                            }
                            $m++;
                        }
                    }
                }
               // сам вывод таблицы собственно
                for($j = 1;$j <= $num_rows; $j++){
                    if($j != $offers_array[$k][0]){
                        $table .= '<tr><td class= "data"></td></tr>';
                    }
                    if($j == $offers_array[$k][0]){
                        if($offers_array[$k][2] > 0){
                            $table .= '<tr><td class= "no_value_time"></td></tr>';
                            $offers_array[$k][2] -= 1;
                        }else if($offers_array[$k][2] == 0){
                            $table .= '<tr><td class= "data">'.$offers_array[$k][3].'</td></tr>';
                        }
                        $k++;
                    }
                }
                if($sum >= $less_value_offers_array[$n][1] && $n <= sizeof($less_value_offers_array)){
                    if(((filter_input(INPUT_POST, "days") - $i + 1 - $less_value_offers_array[$n][2])*$less_value_offers_array[$n][3]-$less_value_offers_array[$n][1]) > 0){
                        $sum -= $less_value_offers_array[$n][1];
                        $table .= '<tr><td class="invest">-'.$less_value_offers_array[$n][1].'</td></tr>';
                        //$n++;
                        $m = 1;
                        while($m < sizeof($less_value_offers_array)){
                            if($less_value_offers_array[$m][4] > $less_value_offers_array[$m+1][4]){
                                $pointer = $less_value_offers_array[$m];
                                $less_value_offers_array[$m] = $less_value_offers_array[$m+1];
                                $less_value_offers_array[$m+1] = $pointer;
                                $m = 0;
                            }
                            $m++;
                        }
                        array_pop($less_value_offers_array);

                    }else{
                       $table .= '<tr><td class= "invest"></td></tr>';
                    }
                }
                else{
                    if($i == 1){
                       $table .= '<tr><td class="invest">-'.$sum2.'</td></tr>';
                    }else{
                       $table .= '<tr class="invest"><td></td></tr>';
                    }
                }

                $table .= '<tr><td class="result">'.$sum.'</td></tr>';
                $table .= '</table></td>';
            }
            $table .= '</tr></table>';
        echo $table;            
        }