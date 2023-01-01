<?php
include 'config.php';
session_start();


if (isset($_GET['temperature'], $_GET['humidity'], $_GET['lm35'])){
    $humidity = $_GET['humidity'];
    $temperature = $_GET['temperature'];
    $tmp = $_GET['lm35'];
    $query = "INSERT INTO `dht11`(`humidity`, `temperature`,`lm35`) VALUES ('$humidity','$temperature','$tmp');";
    $resutl = mysqli_query($db_test, $query);
    if ($resutl) {
        echo "Done";
    } else {
        echo "Error : " . mysqli_error($db_test, $query);
    }
}
