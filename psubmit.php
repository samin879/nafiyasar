<?php

require_once ('process/dbh.php');

$pid = $_GET['pid'];
$id = $_GET['id'];
$date = date('Y-m-d');

$sql = "UPDATE `project` SET `subdate`='$date',`status`='Submitted' WHERE pid = '$pid';";
$result = mysqli_query($conn , $sql);
header("Location: empproject.php?id=$id");
?>