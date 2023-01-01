<?php

include('include/header.php');
include('include/navbar.php');

$sql = "SELECT * FROM `dht11`;";
$result = mysqli_query($db_test, $sql);
$files = mysqli_fetch_all($result, MYSQLI_ASSOC);

?>

<div style="padding-left:360px;text-align: center;">
    <form>
        <div class="main-area">
            <div class="question" id="response" style="width: 70%">
                <div class="row uniform" style="padding-top: 20px; padding-bottom: 50px;">
                    <center>
                        <h3>Data Table</h3>
                    </center>
                    <table>
                        <thead>
                            <th style="padding-left:30px;padding-top:10px;">ID</th>
                            <th>Humidity</th>
                            <th>Temperature</th>
                            <th>Body Temperature</th>

                        </thead>
                        <tbody>
                            <?php foreach ($files as $file) : ?>
                                <td style="padding-left:30px;"><?php echo $file['serial']; ?></td>

                                <td><?php echo $file['humidity']; ?></td>

                                <td><?php echo $file['temperature']; ?></td>
                                <td><?php echo $file['lm35']; ?></td>
                            </tr>
                            <?php endforeach; ?>
                        </tbody>
                    </table>
                </div>

            </div>
    </form>
</div>
</div>
<span class="hr-line"></span>
<?php
include('include/footer.php');
header("refresh: 3");

?>