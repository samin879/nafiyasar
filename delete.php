<?php

include("process/dbh.php");


$id = $_GET['id'];


$result = mysqli_query($conn, "DELETE FROM employee WHERE id=$id");


header("Location:viewemp.php");
?>

